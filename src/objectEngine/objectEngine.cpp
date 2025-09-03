#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
// #include <string>
#include <vector>

#include "src/logging/logging.h"
#include "src/objectEngine/objectEngine.h"
#include <algorithm>


std::vector<std::string> __readFile(const char path[]) {
    std::vector<std::string> __fileData = {};
    std::ifstream __file(path);

    if (!__file) {
        std::cerr << "[!] Unable to open file" << path << std::endl;

        return __fileData;
    }
    
    std::string line;

    logMessage("Reading file", __LOGGING_DEBUG, __OE_LOGID);

    while (std::getline(__file, line)) {
        logMessage("\"" + line + "\"", __LOGGING_TRACE, __OE_LOGID);
        
        __fileData.push_back(line);
    }
    
    __file.close();
    return __fileData;
}

std::vector<std::string> __parseFile(std::vector<std::string> &fileData) {
    std::vector<std::string> __parsedFileData = {};

    logMessage("Parsing file", __LOGGING_DEBUG, __OE_LOGID);    

    for (std::string line : fileData) {
        if (line.size() == 0) {
            continue;
        } else if (line[0] == '#') {
            continue;
        } 

        __parsedFileData.push_back(line);

        logMessage("\"" + line + "\"", __LOGGING_TRACE, __OE_LOGID);
    }

    return __parsedFileData;
}


Shape3d __loadObjectOBJ(const char path[]) {
    std::vector<std::string> __fileData = __readFile(path);
    __fileData = __parseFile(__fileData);

    Shape3d __shape = {};
    int __objectScalar = 1;

    for (std::string line : __fileData) {
        std::istringstream __iss(line);
        std::string __discard;

        // Skip the first token
        __iss >> __discard;

        std::string __token;

        if (line.find("v ") != std::string::npos) {
            std::vector<float> __vertex = {};
            
            while (__iss >> __token) {
                logMessage("\"" + __token + "\"", __LOGGING_TRACE, __OE_LOGID);
                __vertex.push_back(std::stof(__token) * __objectScalar);
            }

            __shape.verticeGeometry.push_back({__vertex[0], __vertex[1], __vertex[2]});

            logMessage("Vertex:", __LOGGING_TRACE, __OE_LOGID);

            std::ostringstream messageStream;
            messageStream << "x: " << __shape.verticeGeometry.back().x << ", " << "y: " << __shape.verticeGeometry.back().y << ", " << "z: " << __shape.verticeGeometry.back().z;

            logMessage(messageStream.str(), __LOGGING_TRACE, __OE_LOGID);
        } else if (line.find("f ") != std::string::npos) {
            std::vector<int> __face;

            while (__iss >> __token) {
                std::replace(__token.begin(), __token.end(), '/', ' ');
                std::istringstream __issInt(__token);
                int index;

                __issInt >> index;
                __face.push_back(index - 1);  // .obj indices start at 1
            }

            for (size_t iteration = 0; iteration < __face.size() - 1; ++iteration) {
                logMessage("Edge: " + std::to_string(__face[iteration]) + ", " + std::to_string(__face[iteration + 1]), __LOGGING_TRACE, __OE_LOGID);
                __shape.edges.push_back({__face[iteration], __face[iteration + 1]});
            }
            __shape.edges.push_back({__face.back(), __face.front()});
        } else {
            continue;
        }

        if (__shape.verticeGeometry.size() == 0) {
            continue;
        }
    }

    __shape.position = {0.0f, 0.0f, 0.0f};
    __shape.rotation = {0.0f, 0.0f, 0.0f};
    __shape.vertices = __shape.verticeGeometry;

    return __shape;
}


// * Object loading
Shape3d loadObject(const char path[], const char fileType[]) {
    Shape3d __OE_loadedShape;

    if (strcmp(fileType, "OBJ") == 0) {
        __OE_loadedShape = __loadObjectOBJ(path);
    } else {
        __OE_loadedShape = {};
    }
    
    
    return __OE_loadedShape;
}



// ! ### [REMOVE IF AIDS] ############################################

// Quaternion eulerToQuaternion(float pitch, float yaw, float roll) {
//     const float halfpitch = pitch * 0.5f;
//     float cp = cosf(halfpitch);
//     float sp = sinf(halfpitch);

//     const float halfyaw = yaw * 0.5f;
//     float cy = cosf(halfyaw);
//     float sy = sinf(halfyaw);

//     const float halfroll = roll * 0.5f;
//     float cr = cosf(halfroll);
//     float sr = sinf(halfroll);

//     Quaternion q;

//     q.w = cr * cp * cy + sr * sp * sy;
//     q.x = sr * cp * cy - cr * sp * sy;
//     q.y = cr * sp * cy + sr * cp * sy;
//     q.z = cr * cp * sy - sr * sp * cy;
    
//     return q;
// }

// ! #################################################################
