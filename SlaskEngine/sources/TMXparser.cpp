#include "TMXparser.h"


TMXparser::TMXparser()
{
}


TMXparser::~TMXparser()
{
}


TMXMap* LoadTMXMap(char *xml)
{
	rapidxml::xml_document<> doc;
	doc.parse<0>(xml);
	rapidxml::xml_node<> *mapnode = doc.first_node("map");
	TMXMap* map = new TMXMap();


	map->width = atoi(mapnode->first_attribute("width")->value());
	map->height = atoi(mapnode->first_attribute("height")->value());
	map->tileWidth = atoi(mapnode->first_attribute("tilewidth")->value());
	map->tileHeight = atoi(mapnode->first_attribute("tileheight")->value());

	rapidxml::xml_node<> *tilesetnode = mapnode->first_node("tileset");

	while (tilesetnode) {
		TMXMapTileSet* tileset = new TMXMapTileSet();

		tileset->firstGid = atoi(tilesetnode->first_attribute("firstgid")->value());
		tileset->name = tilesetnode->first_attribute("name")->value();
		tileset->tileWidth = atoi(tilesetnode->first_attribute("tilewidth")->value());
		tileset->tileHeight = atoi(tilesetnode->first_attribute("tileheight")->value());
		tileset->filename = tilesetnode->first_node("image")->first_attribute("source")->value();

		//cout << "Tileset " << tileset->name << " filename " << tileset->filename << endl;

		map->tilesets.push_back(tileset);

		tilesetnode = tilesetnode->next_sibling("tileset");
	}

	const char *separators = " \t,\n\r";

	rapidxml::xml_node<> *layernode = mapnode->first_node("layer");

	while (layernode) {
		TMXMapLayer* layer = new TMXMapLayer();

		layer->name = layernode->first_attribute("name")->value();

		// TODO assert that the "encoding" attribute is set to "CSV" here.

		const char* data = layernode->first_node("data")->value();

		layer->data = new int[layer->width * layer->height];

		char* copy = (char*)malloc(strlen(data) + 1);
		strcpy(copy, data);
		char* item = strtok(copy, separators);

		int index = 0;
		while (item) {
			layer->data[index] = atoi(item);
			index++;

			item = strtok(0, separators);
		}

		free(copy);

		map->layers.push_back(layer);

		layernode = layernode->next_sibling("layer");
	}

	rapidxml::xml_node<> *objectgroupnode = mapnode->first_node("objectgroup");

	while (objectgroupnode) {
		TMXMapObjectGroup* group = new TMXMapObjectGroup();

		group->name = objectgroupnode->first_attribute("name")->value();

		rapidxml::xml_attribute<> *visibleattr = objectgroupnode->first_attribute("visible");
		if (visibleattr) {
			group->visible = atoi(visibleattr->value())?1:0;
		}
		else {
			group->visible = true;
		}

		//cout << "group " << group->name << endl;

		rapidxml::xml_node<> *objectnode = objectgroupnode->first_node("object");

		while (objectnode) {
			TMXMapObject* object = new TMXMapObject();

			auto nameattr = objectnode->first_attribute("name");
			if (nameattr) {
				object->name = nameattr->value();
			}
			auto gidattr = objectnode->first_attribute("gid");
			if (gidattr) {
				object->gid = atoi(gidattr->value());
			}
			object->x = atoi(objectnode->first_attribute("x")->value());
			object->y = atoi(objectnode->first_attribute("y")->value());

			auto widthattr = objectnode->first_attribute("width");
			if (widthattr) {
				object->width = atoi(widthattr->value());
			}

			auto heightattr = objectnode->first_attribute("height");
			if (heightattr) {
				object->height = atoi(heightattr->value());
			}

			rapidxml::xml_node<> *propertiesnode = objectnode->first_node("properties");

			if (propertiesnode) {

				rapidxml::xml_node<> *propertynode = propertiesnode->first_node("property");

				while (propertynode) {
					TMXMapObjectProperty* property = new TMXMapObjectProperty();
					property->name = propertynode->first_attribute("name")->value();
					property->value = propertynode->first_attribute("value")->value();

					object->properties.push_back(property);

					propertynode = propertynode->next_sibling("property");
				}
			}

			group->objects.push_back(object);

			objectnode = objectnode->next_sibling("object");
		}

		map->groups.push_back(group);

		objectgroupnode = objectgroupnode->next_sibling("objectgroup");
	}

	free((void*)xml);

	return map;
}



TMXMapLayer::~TMXMapLayer()
{
	delete[] data;
}

TMXMapObject::~TMXMapObject()
{
	for (auto property : properties) 
	{
		delete property;
	}
}

TMXMapObjectGroup::~TMXMapObjectGroup()
{
	for (auto o : objects)
	{
		delete o;
	}
}

TMXMap::~TMXMap()
{
	for (auto g : groups)
	{
		delete g;
	}
	
	for (auto l : layers)
	{
		delete l;
	}
	
	for (auto ts : tilesets)
	{
		delete ts;
	}
}