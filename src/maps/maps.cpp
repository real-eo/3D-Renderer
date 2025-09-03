// MapsLibrary.cpp : Defines the exported functions for the DLL.
#include <limits.h>
#include <iostream>
#include <utility>
#include <unordered_map>

#include "maps.h"

#include "objectEngine/objectEngine.h"


static int __MAP_mapID;
static std::unordered_map<std::string, const int> __MAP_mapIDsTable = {
    {"testMapVoid", 0},
    {"testMapGround", 1},
    {"testMapObjectLoader", 2}
};

// Initialize a map to be loaded
void setMap(std::string mapName) {
    __MAP_mapID = __MAP_mapIDsTable.at(mapName);
}

// * Maps
Map __testMapVoid() {
    // * Map
    // TMV = Test Map Void
    Map __TMV_map = {
        {},
        {},
        {}
    };

    std::vector<Vec3> __TMV_cubePositions = {
        {0.0f, 0.0f, 0.0f},
    };

    // Create cubes
    for (Vec3 __TMV_position : __TMV_cubePositions) {
        Shape3d __TMV_cube = {
            __TMV_position,
            {
                0.0f, 
                0.0f, 
                0.0f
            },
            {
                {-50.0f,  50.0f, -50.0f},
                {-50.0f, -50.0f, -50.0f},
                { 50.0f, -50.0f, -50.0f},
                { 50.0f,  50.0f, -50.0f},
                {-50.0f,  50.0f, 50.0f},
                {-50.0f, -50.0f, 50.0f},
                { 50.0f, -50.0f, 50.0f},
                { 50.0f,  50.0f, 50.0f},
            },
            {
                {}, {}, {}, {}, {}, {}, {}, {}
            },
            {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 0},
                {4, 5},
                {5, 6},
                {6, 7},
                {7, 4},
                {0, 4},
                {1, 5},
                {2, 6},
                {3, 7}
            }
        };

        __TMV_map.shapes.push_back(__TMV_cube);

    }

    // Ground
    Shape3d __TMV_ground = {
        {
            0.0f, 
            -1000.0f, 
            0.0f
        },
        {   // Rotation
            0.0f, 0.0f, 0.0f
        },
        {
            {-1000.0f, 32.0f, -1000.0f},
            {-1000.0f, -32.0f, -1000.0f},
            { 1000.0f, -32.0f, -1000.0f},
            { 1000.0f, 32.0f, -1000.0f},
            {-1000.0f, 32.0f, 1000.0f},
            {-1000.0f, -32.0f, 1000.0f},
            { 1000.0f, -32.0f, 1000.0f},
            { 1000.0f, 32.0f, 1000.0f},
        },
        {
            {}, {}, {}, {}, {}, {}, {}, {}
        },
        {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}
        }
    };

    // Add shapes to map
    __TMV_map.shapes.push_back(__TMV_ground);

    return __TMV_map;
}

Map __testMapGround() {
    // * Map
    // TMG = Test Map Ground
    Map __TMG_map = {
        {},
        {},
        {}
    };

    std::vector<Vec3> __TMG_cubePositions = {
        {0.0f, 0.0f, 0.0f},
        {300.0f, 0.0f, 0.0f},
        {-300.0f, 0.0f, 0.0f},
        {300.0f, 0.0f, 300.0f},
        {-300.0f, 0.0f, 300.0f},
    };

    // Create cubes
    for (Vec3 __TMG_position : __TMG_cubePositions) {
        Shape3d __TMG_cube = {
            __TMG_position,
            {
                0.0f, 
                0.0f, 
                0.0f
            },
            {
                {-50.0f,  50.0f, -50.0f},
                {-50.0f, -50.0f, -50.0f},
                { 50.0f, -50.0f, -50.0f},
                { 50.0f,  50.0f, -50.0f},
                {-50.0f,  50.0f, 50.0f},
                {-50.0f, -50.0f, 50.0f},
                { 50.0f, -50.0f, 50.0f},
                { 50.0f,  50.0f, 50.0f},
            },
            {
                {}, {}, {}, {}, {}, {}, {}, {}
            },
            {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 0},
                {4, 5},
                {5, 6},
                {6, 7},
                {7, 4},
                {0, 4},
                {1, 5},
                {2, 6},
                {3, 7}
            }
        };

        __TMG_map.shapes.push_back(__TMG_cube);

    }

    // Ground
    Shape3d __TMG_ground = {
        {
            0.0f, 
            -132.0f, 
            0.0f
        },
        {   // Rotation
            0.0f, 0.0f, 0.0f
        },
        {
            {-1000.0f, 32.0f, -1000.0f},
            {-1000.0f, -32.0f, -1000.0f},
            { 1000.0f, -32.0f, -1000.0f},
            { 1000.0f, 32.0f, -1000.0f},
            {-1000.0f, 32.0f, 1000.0f},
            {-1000.0f, -32.0f, 1000.0f},
            { 1000.0f, -32.0f, 1000.0f},
            { 1000.0f, 32.0f, 1000.0f},
        },
        {
            {}, {}, {}, {}, {}, {}, {}, {}
        },
        {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}
        }
    };

    // Add shapes to map
    __TMG_map.shapes.push_back(__TMG_ground);

    return __TMG_map;
}

Map __testMapObjectLoader() {
    // * Map
    // TMOL = Test Map Object Loader
    Map __TMOL_map = {
        {},
        {},
        {}
    };

    // | Load objects
    // Shape3d __TMOL_shape = loadObject("res/objects/cube/cube.obj", "OBJ");
    // Shape3d __TMOL_shape = loadObject("res/objects/fighter jet/F-16D.obj", "OBJ");
    // Shape3d __TMOL_shape = loadObject("res/objects/geirik hus/pepperkakehus_projekt_v2.obj", "OBJ");
    // Shape3d __TMOL_shape = loadObject("res/objects/tank/Ch_sherman.obj", "OBJ");
    Shape3d __TMOL_shape = loadObject("res/objects/interior/InteriorTest.obj", "OBJ");

    // Add shapes to map
    __TMOL_map.shapes.push_back(__TMOL_shape);
    //// __TMOL_map.shapes.push_back(__TMOL_ground);

    return __TMOL_map;
}

// * Get map
Map getMap() {
    Map __map;

    switch (__MAP_mapID) {
        case 0:
            __map = __testMapVoid();
            break;
        case 1:
            __map = __testMapGround();
            break;
        case 2:
            __map = __testMapObjectLoader();
            break;

        default:
            std::cout << "Map not found" << std::endl;
            
            break;
    }

    return __map;
}
