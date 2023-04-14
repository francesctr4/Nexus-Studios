#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "PQueue.h"
#include "DynArray.h"

#include "PugiXml\src\pugixml.hpp"

#define COST_MAP_SIZE 25

// Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;
	int columns;
	int tilecount;

	SDL_Texture* texture;

	// Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int gid) const;
};

//  We create an enum for map type, just for convenience,
// NOTE: Platformer game will be of type ORTHOGONAL
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// Create a generic structure to hold properties
struct Properties
{
	struct Property
	{
		SString name;
		bool value;
	};

	~Properties()
	{
		//...
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.Clear();
	}

	// Method to ask for the value of a custom property
	Property* GetProperty(const char* name);

	List<Property*> list;
};

// Create a struct for the map layer
struct MapLayer
{
	SString	name;
	int id; 
	int width;
	int height;
	uint* data;
	

	// Store custom properties
	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	// Short function to get the gid value of x,y
	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

// Create a struct needed to hold the information to Map node
struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	List<TileSet*> tilesets;
	MapTypes type;

	// Add a list/array of layers to the map
	List<MapLayer*> maplayers;
	List<MapLayer*> objectlayers;
};

class Map : public Module
{
public:

    Map(bool startEnabled);

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

	bool Init();

    // Called each loop iteration
    void Draw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load();

	// Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

	// Add method WorldToMap to obtain  
	iPoint Map::WorldToMap(int x, int y);

	// L12: Create walkability map for pathfinding
	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;

private:

	bool LoadMap(pugi::xml_node mapFile);

	// Create and call a private function to load a tileset
	bool LoadTileSet(pugi::xml_node mapFile);

	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadAllLayers(pugi::xml_node mapNode);

	TileSet* GetTilesetFromTileId(int gid) const;

	// Load a group of properties 
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	
	// Load object layers (which are the ones that store the colliders)

	bool LoadAllObjectLayers(pugi::xml_node mapNode);
	bool LoadObjectLayer(pugi::xml_node& node, MapLayer* objectLayer);

	// Auxiliar functions to automate collider creation

	int FindVertices(std::string string, char c);
	int* ConvertPolygonVerticesToArray(std::string vertices, int length);

public: 

	// Declare a variable data of the struct MapData
	MapData mapData;
	pugi::xml_node config;

public:

	SString mapFileName[4];
	int actualmap = 0;
	SString mapFolder;
    bool mapLoaded;
};

#endif // __MAP_H__