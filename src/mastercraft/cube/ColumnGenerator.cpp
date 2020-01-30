#include <mastercraft/cube/ColumnGenerator.hpp>


namespace mastercraft::cube {
    
    std::array<cube::CubeType, cube::SuperChunk::Y> ColumnGenerator::waterColumn(GLubyte height) {
        std::array<cube::CubeType, cube::SuperChunk::Y> column = {};
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
    
    
    std::array<cube::CubeType, cube::SuperChunk::Y> ColumnGenerator::sandColumn(GLubyte height) {
        std::array<cube::CubeType, cube::SuperChunk::Y> column = {};
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
    
    
    std::array<cube::CubeType, cube::SuperChunk::Y> ColumnGenerator::dirtColumn(GLubyte height) {
        std::array<cube::CubeType, cube::SuperChunk::Y> column = {};
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
    
    
    std::array<cube::CubeType, cube::SuperChunk::Y> ColumnGenerator::stoneColumn(GLubyte height) {
        std::array<cube::CubeType, cube::SuperChunk::Y> column = {};
        column.fill(cube::CubeType::AIR);
        
        for (GLuint y = 0; y <= height; y++) {
            column[y] = cube::CubeType::STONE;
        }
        
        return column;
    }
    
    
    std::array<cube::CubeType, cube::SuperChunk::Y> ColumnGenerator::snowColumn(GLubyte height) {
        std::array<cube::CubeType, cube::SuperChunk::Y> column = {};
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
    
    
    std::array<cube::CubeType, cube::SuperChunk::Y> ColumnGenerator::generateColumn(GLubyte height,
                                                                                    cube::CubeType type) {
        std::array<cube::CubeType, cube::SuperChunk::Y> column {};
        
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
            case cube::CubeType::LEAVE:
                column.fill(cube::CubeType::AIR);
        }
        
        return column;
    }
}
