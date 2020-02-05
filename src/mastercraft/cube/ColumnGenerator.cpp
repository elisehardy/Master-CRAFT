#include <mastercraft/cube/ColumnGenerator.hpp>


namespace mastercraft::cube {
    
    ColumnGenerator::Column ColumnGenerator::waterColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= game::ConfigManager::GEN_WATER_LEVEL + 1; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else if (y < height) {
                column[y] = cube::CubeType::SAND_BEACH;
            }
            else {
                column[y] = cube::CubeType::WATER;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::iceColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
    
        for (GLuint y = 0; y <= game::ConfigManager::GEN_WATER_LEVEL + 1; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else if (y < height) {
                column[y] = cube::CubeType::SNOW;
            }
            else if (y == game::ConfigManager::GEN_WATER_LEVEL + 1) {
                column[y] = cube::CubeType::ICE;
            }
            else {
                column[y] = cube::CubeType::WATER;
            }
        }
    
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::sandBeachColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 2) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::SAND_BEACH;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::sandDesertColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
    
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 5) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::SAND_DESERT;
            }
        }
    
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::snowColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::SNOW;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::stoneColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            column[y] = cube::CubeType::STONE;
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::stoneSnowColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
    
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 2) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::STONE_SNOW;
            }
        }
    
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::dirtPlainColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::DIRT_PLAIN;
            }
        }
        
        return column;
    }
    
    ColumnGenerator::Column ColumnGenerator::dirtJungleColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::DIRT_JUNGLE;
            }
        }
        
        return column;
    }
    
    ColumnGenerator::Column ColumnGenerator::dirtSnowColumn(GLuint height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::DIRT_SNOW;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::generate(GLuint height, cube::CubeType type) {
        switch (type) {
            case WATER:
                return waterColumn(height);
            case ICE:
                return iceColumn(height);
            case SAND_BEACH:
                return sandBeachColumn(height);
            case SAND_DESERT:
                return sandDesertColumn(height);
            case SNOW:
                return snowColumn(height);
            case STONE:
                return stoneColumn(height);
            case STONE_SNOW:
                return stoneSnowColumn(height);
            case DIRT_PLAIN:
                return dirtPlainColumn(height);
            case DIRT_JUNGLE:
                return dirtJungleColumn(height);
            case DIRT_SNOW:
                return dirtSnowColumn(height);
            case AIR:
            case WOOD_PLAIN:
            case FLOWERS:
            case WOOD_JUNGLE:
            case WOOD_SNOW:
            case CACTUS:
            case LEAVES_PLAIN:
            case LEAVES_JUNGLE:
            case LEAVES_SNOW:
                throw std::runtime_error("Cannot generate column for biome of type '" + std::to_string(type) + "'.");
        }
    }
}
