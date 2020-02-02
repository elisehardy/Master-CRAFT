#include <mastercraft/cube/ColumnGenerator.hpp>


namespace mastercraft::cube {
    
    ColumnGenerator::Column ColumnGenerator::waterColumn(GLubyte height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= game::ConfigManager::GEN_WATER_LEVEL + 1; y++) {
            if (y < height - 3) {
                column[y] = cube::CubeType::STONE;
            }
            else if (y < height) {
                column[y] = cube::CubeType::SAND;
            }
            else {
                column[y] = cube::CubeType::WATER;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::sandColumn(GLubyte height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 2) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::SAND;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::dirtColumn(GLubyte height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 2) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::DIRT;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::stoneColumn(GLubyte height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            column[y] = cube::CubeType::STONE;
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::snowColumn(GLubyte height) {
        Column column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            if (y < height - 1) {
                column[y] = cube::CubeType::STONE;
            }
            else {
                column[y] = cube::CubeType::SNOW;
            }
        }
        
        return column;
    }
    
    
    ColumnGenerator::Column ColumnGenerator::generate(GLubyte height, cube::CubeType type) {
        Column column {};
        
        switch (type) {
            case cube::CubeType::AIR:
                column.fill(cube::CubeType::AIR);
                break;
            case cube::CubeType::WATER:
                column = waterColumn(height);
                break;
            case cube::CubeType::SAND:
                column = sandColumn(height);
                break;
            case cube::CubeType::DIRT:
                column = dirtColumn(height);
                break;
            case cube::CubeType::STONE:
                column = stoneColumn(height);
                break;
            case cube::CubeType::SNOW:
                column = snowColumn(height);
                break;
            case cube::CubeType::WOOD:
            case cube::CubeType::LEAF:
                throw std::runtime_error("Cannot generate column for biome of type '" + std::to_string(type) + "'.");
        }
        
        return column;
    }
}
