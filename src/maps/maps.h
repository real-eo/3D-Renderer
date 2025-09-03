// MapLibrary.h - Contains various maps- & map information
#pragma once

/* DLL export
#ifdef MAPSLIBRARY_EXPORTS
#define MAPSLIBRARY_API __declspec(dllexport)
#else
#define MAPSLIBRARY_API __declspec(dllimport)
#endif
*/

#ifndef MAPSLIB_H
#define MAPSLIB_H

#include "src/objectEngine/objectEngine.h"

struct Map {
    std::vector<Shape3d> shapes;
    std::vector<Shape3d> entities;
    std::vector<Shape3d> lights;
};


// Initialize a map to be loaded
/* DLL export
extern "C" MAPSLIBRARY_API void setMap(const char* mapName);
*/

extern "C" MAPSLIB_H {
    void setMap(std::string mapName);
    Map getMap();
}

#endif
