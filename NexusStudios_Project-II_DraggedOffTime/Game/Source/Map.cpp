#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "Physics.h"
#include "SceneManager.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>
#include "SDL_image/include/SDL_image.h"

#include "External/Optick/include/optick.h"

Map::Map(bool startEnabled) : Module(startEnabled), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    mapFileName[0] = config.child("mapfile_1").attribute("path").as_string();
    mapFileName[1] = config.child("mapfile_2").attribute("path").as_string();
    mapFileName[2] = config.child("mapfile_3").attribute("path").as_string();
    mapFileName[3] = config.child("mapfile_4").attribute("path").as_string();
    mapFolder = config.child("mapfolder").attribute("path").as_string();
    this->config = config;
    return ret;
}

// Called before render is available
bool Map::Init()
{
    LOG("Loading Map Parser");
    bool ret = true;

    mapFileName[0] = config.child("mapfile_1").attribute("path").as_string();
    mapFileName[1] = config.child("mapfile_2").attribute("path").as_string();
    mapFileName[2] = config.child("mapfile_3").attribute("path").as_string();
    mapFileName[3] = config.child("mapfile_4").attribute("path").as_string();
    mapFolder = config.child("mapfolder").attribute("path").as_string();

    return ret;
}

// L12: Create walkability map for pathfinding
bool Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const
{
    OPTICK_EVENT();
    bool ret = false;
    ListItem<MapLayer*>* item;
    item = mapData.maplayers.start;

    for (item = mapData.maplayers.start; item != NULL; item = item->next)
    {
        MapLayer* layer = item->data;

        if (layer->properties.GetProperty("Navigation") != NULL && !layer->properties.GetProperty("Navigation")->value)
            continue;

        uchar* map = new uchar[layer->width * layer->height];
        memset(map, 1, layer->width * layer->height);

        for (int y = 0; y < mapData.height; ++y)
        {
            for (int x = 0; x < mapData.width; ++x)
            {
                int i = (y * layer->width) + x;

                int tileId = layer->Get(x, y);
                TileSet* tileset = (tileId > 0) ? GetTilesetFromTileId(tileId) : NULL;

                if (tileset != NULL)
                {
                    //According to the mapType use the ID of the tile to set the walkability value
                    //if (mapData.type == MapTypes::MAPTYPE_ISOMETRIC && tileId == 25) map[i] = 1;
                    if (mapData.type == MapTypes::MAPTYPE_ORTHOGONAL && tileId == 1514) map[i] = 1;
                    else map[i] = 0;
                }
                else {
                    //LOG("CreateWalkabilityMap: Invalid tileset found");
                    map[i] = 0;
                }
            }
        }

        *buffer = map;
        width = mapData.width;
        height = mapData.height;
        ret = true;

        break;
    }

    return ret;
}

void Map::Draw()
{
    OPTICK_EVENT();

    if(mapLoaded == false)
        return;

    /*
    // Iterate all tilesets and draw all their 
    // images in 0,0 (you should have only one tileset for now)

    ListItem<TileSet*>* tileset;
    tileset = mapData.tilesets.start;

    while (tileset != NULL) {
        app->render->DrawTexture(tileset->data->texture,0,0);
        tileset = tileset->next;
    }
    */

    // Prepare the loop to draw all tiles in a layer + DrawTexture()

    ListItem<MapLayer*>* mapLayerItem;
    mapLayerItem = mapData.maplayers.start;

    while (mapLayerItem != NULL) {

        // use GetProperty method to ask each layer if your “Draw” property is true.
        if (mapLayerItem->data->properties.GetProperty("Draw") != NULL && mapLayerItem->data->properties.GetProperty("Draw")->value) {

            for (int x = 0; x < mapLayerItem->data->width; x++)
            {
                for (int y = 0; y < mapLayerItem->data->height; y++)
                {
                    // Complete the draw function
                    int gid = mapLayerItem->data->Get(x, y);

                    // Obtain the tile set using GetTilesetFromTileId
                    TileSet* tileset = GetTilesetFromTileId(gid);

                    SDL_Rect r = tileset->GetTileRect(gid);
                    iPoint pos = MapToWorld(x, y);

                    app->render->DrawTexture(tileset->texture,
                        pos.x,
                        pos.y,
                        &r);
                }
            }
        }
        mapLayerItem = mapLayerItem->next;

    }
}

// Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
    iPoint ret;

    // Add isometric map to world coordinates
    if (mapData.type == MAPTYPE_ORTHOGONAL)
    {
        ret.x = x * mapData.tileWidth;
        ret.y = y * mapData.tileHeight;
    }
    else if (mapData.type == MAPTYPE_ISOMETRIC)
    {
        ret.x = (x - y) * (mapData.tileWidth / 2);
        ret.y = (x + y) * (mapData.tileHeight / 2);
    }

    return ret;
}

// Add method WorldToMap to obtain  map coordinates from screen coordinates
iPoint Map::WorldToMap(int x, int y)
{
    iPoint ret(0, 0);

    if (mapData.type == MAPTYPE_ORTHOGONAL)
    {
        ret.x = x / mapData.tileWidth;
        ret.y = y / mapData.tileHeight;
    }
    else if (mapData.type == MAPTYPE_ISOMETRIC)
    {
        float halfWidth = mapData.tileWidth * 0.5f;
        float halfHeight = mapData.tileHeight * 0.5f;
        ret.x = int((x / halfWidth + y / halfHeight) / 2);
        ret.y = int((y / halfHeight - x / halfWidth) / 2);
    }
    else
    {
        LOG("Unknown map type");
        ret.x = x; ret.y = y;
    }

    return ret;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int gid) const
{
    SDL_Rect rect = { 0 };
    int relativeIndex = gid - firstgid;

    // Get relative Tile rectangle
    rect.w = tileWidth;
    rect.h = tileHeight;
    rect.x = margin + (tileWidth + spacing) * (relativeIndex % columns);
    rect.y = margin + (tileWidth + spacing) * (relativeIndex / columns);

    return rect;
}


// Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int gid) const
{
    ListItem<TileSet*>* item = mapData.tilesets.start;
    TileSet* set = NULL;

    while (item)
    {
        set = item->data;
        if (gid < (item->data->firstgid + item->data->tilecount))
        {
            break;
        }
        item = item->next;
    }

    return set;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

   

    mapFileName[0].Clear();

    
    // Make sure you clean up any memory allocated from tilesets/map
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.Clear();

    // clean up all layer data
    // Remove all layers
    ListItem<MapLayer*>* layerItem;
    layerItem = mapData.maplayers.start;

    while (layerItem != NULL)
    {
        RELEASE(layerItem->data);
        layerItem = layerItem->next;
    }
    mapData.maplayers.Clear();
    

    return true;
}

// Load new mapa
bool Map::Load()
{
    OPTICK_EVENT();
    bool ret = true;

    pugi::xml_document mapFileXML;
   
    //No encuentra ek mapa por segunda vez
    pugi::xml_parse_result result = mapFileXML.load_file(mapFileName[actualmap].GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", mapFileName[actualmap], result.description());
        ret = false;
    }

    if(ret == true)
    {
        ret = LoadMap(mapFileXML);
    }

    if (ret == true)
    {
        ret = LoadTileSet(mapFileXML);
    }

    // Iterate all layers and load each of them
    if (ret == true)
    {
        ret = LoadAllLayers(mapFileXML.child("map"));
    }

    if (ret == true)
    {
        ret = LoadAllObjectLayers(mapFileXML.child("map"));
    }
    
    // Later you can create a function here to load and create the colliders from the map

    if (ret == true)
    {
        // LOG all the data loaded iterate all tilesets and LOG everything
       
        LOG("Successfully parsed map XML file :%s", mapFileName[actualmap].GetString());
        LOG("width : %d height : %d",mapData.width,mapData.height);
        LOG("tile_width : %d tile_height : %d",mapData.tileWidth, mapData.tileHeight);
        
        LOG("Tilesets----");

        ListItem<TileSet*>* tileset;
        tileset = mapData.tilesets.start;

        while (tileset != NULL) {
            LOG("name : %s firstgid : %d",tileset->data->name.GetString(), tileset->data->firstgid);
            LOG("tile width : %d tile height : %d", tileset->data->tileWidth, tileset->data->tileHeight);
            LOG("spacing : %d margin : %d", tileset->data->spacing, tileset->data->margin);
            tileset = tileset->next;
        }

        // LOG the info for each loaded layer
        ListItem<MapLayer*>* mapLayer;
        mapLayer = mapData.maplayers.start;

        while (mapLayer != NULL) {
            LOG("id : %d name : %s", mapLayer->data->id, mapLayer->data->name.GetString());
            LOG("Layer width : %d Layer height : %d", mapLayer->data->width, mapLayer->data->height);
            mapLayer = mapLayer->next;
        }
    }

    if(mapFileXML) mapFileXML.reset();

    mapLoaded = ret;

    return ret;
}

// Implement LoadMap to load the map properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
    bool ret = true;
    pugi::xml_node map = mapFile.child("map");

    if (map == NULL)
    {
        LOG("Error parsing map xml file: Cannot find 'map' tag.");
        ret = false;
    }
    else
    {
        //Load map general properties
        mapData.height = map.attribute("height").as_int();
        mapData.width = map.attribute("width").as_int();
        mapData.tileHeight = map.attribute("tileheight").as_int();
        mapData.tileWidth = map.attribute("tilewidth").as_int();
        mapData.type = MAPTYPE_UNKNOWN;

        // Read the prientation of the map
        mapData.type = MAPTYPE_UNKNOWN;
        if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
        {
            mapData.type = MAPTYPE_ISOMETRIC;
        }
        if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
        {
            mapData.type = MAPTYPE_ORTHOGONAL;
        }
    }

    return ret;
}

// Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSet(pugi::xml_node mapFile){

    bool ret = true; 

    pugi::xml_node tileset;
    for (tileset = mapFile.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
    {
        TileSet* set = new TileSet();

        // Load Tileset attributes
        set->name = tileset.attribute("name").as_string();
        set->firstgid = tileset.attribute("firstgid").as_int();
        set->margin = tileset.attribute("margin").as_int();
        set->spacing = tileset.attribute("spacing").as_int();
        set->tileWidth = tileset.attribute("tilewidth").as_int();
        set->tileHeight = tileset.attribute("tileheight").as_int();
        set->columns = tileset.attribute("columns").as_int();
        set->tilecount = tileset.attribute("tilecount").as_int();

        // Load Tileset image
        SString tmp("%s%s", mapFolder.GetString(), tileset.child("image").attribute("source").as_string());
        set->texture = app->tex->Load(tmp.GetString());

        mapData.tilesets.Add(set);
    }

    return ret;
}

// Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
    bool ret = true;

    //Load the attributes
    layer->id = node.attribute("id").as_int();
    layer->name = node.attribute("name").as_string();
    layer->width = node.attribute("width").as_int();
    layer->height = node.attribute("height").as_int();

    // Call Load Propoerties
    LoadProperties(node, layer->properties);

    //Reserve the memory for the data 
    layer->data = new uint[layer->width * layer->height];
    memset(layer->data, 0, layer->width * layer->height);

    //Iterate over all the tiles and assign the values
    pugi::xml_node tile;
    int i = 0;
    for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
    {
        layer->data[i] = tile.attribute("gid").as_int();
        i++;
    }

    return ret;
}

// Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {

    bool ret = true;

    for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
    {
        //Load the layer
        MapLayer* mapLayer = new MapLayer();
        ret = LoadLayer(layerNode, mapLayer);

        //add the layer to the map
        mapData.maplayers.Add(mapLayer);
    }

    return ret;
}

// Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
    bool ret = false;

    for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
    {
        Properties::Property* p = new Properties::Property();
        p->name = propertieNode.attribute("name").as_string();
        p->value = propertieNode.attribute("value").as_bool(); // (!!) I'm assuming that all values are bool !!

        properties.list.Add(p);
    }

    return ret;
}


// Ask for the value of a custom property
Properties::Property* Properties::GetProperty(const char* name)
{
    ListItem<Property*>* item = list.start;
    Property* p = NULL;

    while (item)
    {
        if (item->data->name == name) {
            p = item->data;
            break;
        }
        item = item->next;
    }

    return p;
}

bool Map::LoadObjectLayer(pugi::xml_node& node, MapLayer* objectLayer) {

    bool ret = true;

    //Load the attributes

    objectLayer->id = node.attribute("id").as_int();
    objectLayer->name = node.attribute("name").as_string();

    // Call Load Propoerties
    LoadProperties(node, objectLayer->properties);

    //Iterate over all the tiles and assign the values
    pugi::xml_node objectNode;

    for (objectNode = node.child("object"); objectNode && ret; objectNode = objectNode.next_sibling("object"))
    {
       
        pugi::xml_node poly = objectNode.child("polygon");

        if (poly) {

            int x = objectNode.attribute("x").as_int();
            int y = objectNode.attribute("y").as_int();

            std::string points = poly.attribute("points").as_string();

            int length = FindVertices(points, ',') * 2;

            int* converted_points = ConvertPolygonVerticesToArray(points, length);

            if (objectLayer->properties.GetProperty("Platform") != NULL && objectLayer->properties.GetProperty("Platform")->value) {

                app->physics->CreateChain(x, y, converted_points, length, bodyType::STATIC, ColliderType::PLATFORM);

            }

            delete[] converted_points;

        }
        else {

            int x = objectNode.attribute("x").as_int();
            int y = objectNode.attribute("y").as_int();
            int width = objectNode.attribute("width").as_float();
            int height = objectNode.attribute("height").as_float();

            app->physics->CreateRectangleSensor(x + width / 2, y + height / 2, width, height, bodyType::STATIC, ColliderType::SPIKES);

        }

    }

    return ret;

}

bool Map::LoadAllObjectLayers(pugi::xml_node mapNode) {

    bool ret = true;

    for (pugi::xml_node objectLayerNode = mapNode.child("objectgroup"); objectLayerNode && ret; objectLayerNode = objectLayerNode.next_sibling("objectgroup"))
    {
        //Load the layer

        MapLayer* mapLayer = new MapLayer();
        ret = LoadObjectLayer(objectLayerNode, mapLayer);

        //add the layer to the map

        mapData.maplayers.Add(mapLayer);

    }

    return ret;
}

int* Map::ConvertPolygonVerticesToArray(std::string vertices, int length) {

    vertices += ',';

    std::string* substrings = new std::string[length];

    int* array = new int[length];

    int j = 0;
    int k = 0;

    for (int i = 0; vertices[i]; i++) {

        if (vertices[i] == ' ' || vertices[i] == ',') {

            std::string aux;

            while (j < i) {

                aux = aux + vertices[j];
                substrings[k] = aux;

                j++;

            }

            j++;
            k++;

        }

    }

    for (int i = 0; i < length; i++) {

        array[i] = atoi(substrings[i].c_str());

    }

    return array;

}

int Map::FindVertices(std::string string, char c) {

    int instances = 0;

    for (int i = 0; string[i]; i++) {

        if (string[i] == c) {

            instances++;

        }

    }

    return instances;

}


