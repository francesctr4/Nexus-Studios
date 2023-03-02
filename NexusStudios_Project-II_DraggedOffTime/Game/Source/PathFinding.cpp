#include "App.h"
#include "PathFinding.h"

#include "Defs.h"
#include "Log.h"

#include "External/Optick/include/optick.h"

PathFinding::PathFinding(bool startEnabled) : Module(startEnabled), map(NULL), lastPath(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.Create("pathfinding");
}

// Destructor
PathFinding::~PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	lastPath.Clear();
	RELEASE_ARRAY(map);

	return true;
}

// Sets up the walkability map
void PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width * height];
	memcpy(map, data, width * height);
}

// Utility: return true if pos is inside the map boundaries
bool PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y * width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const DynArray<iPoint>* PathFinding::GetLastPath() const
{
	return &lastPath;
}

// To request all tiles involved in the last generated path
void PathFinding::ClearLastPath()
{
	lastPath.Clear();
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
ListItem<PathNode>* PathList::Find(const iPoint& point) const
{
	ListItem<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return item;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
ListItem<PathNode>* PathList::GetNodeLowestScore() const
{
	ListItem<PathNode>* ret = NULL;
	int min = 65535;

	ListItem<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& listToFill) const
{
	iPoint cell;
	uint before = listToFill.list.Count();

	// north
	cell.Create(pos.x, pos.y + 1);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	// south
	cell.Create(pos.x, pos.y - 1);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	// east
	cell.Create(pos.x + 1, pos.y);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	// west
	cell.Create(pos.x - 1, pos.y);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	return listToFill.list.Count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	OPTICK_EVENT();

	int ret = -1;
	int iterations = 0;

	// if origin or destination are not walkable, return -1
	if (IsWalkable(origin) && IsWalkable(destination))
	{
		// Create two lists: open, close
		PathList open;
		PathList closed;

		// Add the origin tile to open
		open.list.Add(PathNode(0, 0, origin, nullptr));

		// Iterate while we have tile in the open list
		while (open.list.Count() > 0)
		{
			// Move the lowest score cell from open list to the closed list
			ListItem<PathNode>* lowest = open.GetNodeLowestScore();
			ListItem<PathNode>* node = closed.list.Add(lowest->data);
			open.list.Del(lowest);

			// If we just added the destination, we are done!
			if (node->data.pos == destination)
			{
				lastPath.Clear();

				// Backtrack to create the final path
				// Use the Pathnode::parent and Flip() the path when you are finish
				const PathNode* pathNode = &node->data;

				while (pathNode)
				{
					lastPath.PushBack(pathNode->pos);
					pathNode = pathNode->parent;
				}

				lastPath.Flip();
				ret = lastPath.Count();
				//LOG("Created path of %d steps in %d iterations", ret, iterations);
				break;
			}

			// Fill a list of all adjancent nodes
			PathList adjacent;
			node->data.FindWalkableAdjacents(adjacent);

			// Iterate adjancent nodes:
			// If it is a better path, Update the parent
			ListItem<PathNode>* item = adjacent.list.start;
			for (; item; item = item->next)
			{
				// ignore nodes in the closed list
				if (closed.Find(item->data.pos) != NULL)
					continue;

				// If it is NOT found, calculate its F and add it to the open list
				ListItem<PathNode>* adjacentInOpen = open.Find(item->data.pos);
				if (adjacentInOpen == NULL)
				{
					item->data.CalculateF(destination);
					open.list.Add(item->data);
				}
				else
				{
					// If it is already in the open list, check if it is a better path (compare G)
					if (adjacentInOpen->data.g > item->data.g + 1)
					{
						adjacentInOpen->data.parent = item->data.parent;
						adjacentInOpen->data.CalculateF(destination);
					}
				}
			}

			++iterations;
		}
	}

	return ret;
}