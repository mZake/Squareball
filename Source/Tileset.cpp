#include "Tileset.h"

#include <yaml-cpp/yaml.h>

namespace YAML
{
    template<>
    struct convert<Squareball::Tile>
    {
        static bool decode(const Node& node, Squareball::Tile& tile)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;
            
            tile.TexCoords.x = node[0].as<float>();
            tile.TexCoords.y = node[1].as<float>();
            tile.Flags = node[2].as<Squareball::TileFlags>();
            
            return true;
        }
    };
}

namespace Squareball
{
    Tileset LoadTileset(std::string_view filepath)
    {
        YAML::Node node = YAML::LoadFile(filepath.data());
        
        std::string atlasPath = node["AtlasPath"].as<std::string>();
        
        Tileset tileset;
        tileset.Atlas = LoadTexture(atlasPath.c_str());
        tileset.TileWidth = node["TileWidth"].as<int>();
        tileset.TileHeight = node["TileHeight"].as<int>();
        tileset.Tiles = node["Tiles"].as<std::vector<Tile>>();
        
        return tileset;
    }
}
