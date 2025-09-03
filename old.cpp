#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
// #include <cmath>     // DEFINED IN: objectEngine.h

#include <maps/maps.h>


// * Constants
// Window
#define WIDTH 800
#define HEIGHT 600

// Game
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

// Pre-processing constants
constexpr float F_HPI = M_PI * 0.5f;    // Half PI
constexpr float F_2PI = M_PI * 2.0f;    // 2 PI

// Rendering
const float MIN_RENDER_DEPTH = 2.0f;    // Minimum depth for perspective projection, near clipping plane

// Colors
#define WHITE SDL_Color{255, 255, 255, 255}
#define BLACK SDL_Color{0, 0, 0, 255}
#define GRAY SDL_Color{128, 128, 128, 255}

#define RED SDL_Color{255, 0, 0, 255}
#define GREEN SDL_Color{0, 255, 0, 255}
#define BLUE SDL_Color{0, 0, 255, 255}

#define YELLOW SDL_Color{255, 255, 0, 255}
#define CYAN SDL_Color{0, 255, 255, 255}
#define MAGENTA SDL_Color{255, 0, 255, 255}

// Font
#define FONT_PATH "res/fonts/ebrima.ttf"





int fastSqrtInt(const int &number) {
    static_assert(sizeof(int) == sizeof(uint32_t), "int and uint32_t must have the same size");

    uint32_t i = static_cast<uint32_t>(number);

    i = 0x1fbd1df5 + (i >> 1);
    i >>= 1;

    return static_cast<int>(i);
}

float fastInvSqrtFloat(float &number) {
    static_assert(sizeof(float) == sizeof(uint32_t), "float and uint32_t must have the same size");

    uint32_t i;
    std::memcpy(&i, &number, sizeof(float));

    const float x2 = number * 0.5f;
    const uint32_t threehalfs = 0x5f3759df;

    i = threehalfs - (i >> 1);
    std::memcpy(&number, &i, sizeof(float));

    number *= (1.5f - (x2 * number * number));

    return number;
}

float fastInvSqrtInt(const int &number) {
    static_assert(sizeof(int) == sizeof(uint32_t), "int and uint32_t must have the same size");

    uint32_t i = static_cast<uint32_t>(number);

    const uint32_t x2 = i >> 1;
    const uint32_t threehalfs = 0x5f3759df;

    i = threehalfs - (i >> 1);
    i *= (3U - (x2 * i * i));

    float result;
    std::memcpy(&result, &i, sizeof(float));

    return result;
}

inline int distanceSquared2D(const Point2D &point, const Point2D &origin = {0, 0}) {
    Point2D translatedPoint = {point.x - origin.x, point.y - origin.y};

    return (translatedPoint.x * translatedPoint.x) + (translatedPoint.y * translatedPoint.y);
}

float const cotf(const float &angle) {
    return 1.0f / tan(angle);
}


// * Define operators for Point2D structure
Point2D operator+(const Point2D& a, const Point2D& b) {
    Point2D result = {a.x + b.x, a.y + b.y};
    return result;
}

Point2D operator-(const Point2D& a, const Point2D& b) {
    Point2D result = {a.x - b.x, a.y - b.y};
    return result;
}

Point2D operator*(const Point2D& a, const Point2D& b) {
    Point2D result = {a.x * b.x, a.y * b.y};
    return result;
}

Point2D operator*(const Point2D& a, const float& scalar) {
    Point2D result = {static_cast<int>(a.x * scalar), static_cast<int>(a.y * scalar)};
    return result;
}

Point2D operator<(const Point2D& a, const Point2D& b) {
    Point2D result = distanceSquared2D(a) < distanceSquared2D(b) ? a : b;
    return result;
}

Point2D operator>(const Point2D& a, const Point2D& b) {
    Point2D result = distanceSquared2D(a) > distanceSquared2D(b) ? a : b;
    return result;
}

Point2D& operator+=(Point2D& a, const Point2D& b) {a = a + b; return a;}
Point2D& operator-=(Point2D& a, const Point2D& b) {a = a - b; return a;}


// * Define operators for Point3D structure
Point3D operator+(const Point3D& a, const Point3D& b) {
    Point3D result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

Point3D operator+(const Point3D& point, const int& scalar) {
    Point3D result = {point.x + scalar, point.y + scalar, point.z + scalar};
    return result;
}

Point3D operator-(const Point3D& a, const Point3D& b) {
    Point3D result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Point3D operator*(const Point3D& a, const Point3D& b) {
    Point3D result = {a.x * b.x, a.y * b.y, a.z * b.z};
    return result;
}

Point3D operator*(const Point3D& point, const float& scalar) {
    Point3D result = {point.x * scalar, point.y * scalar, point.z * scalar}; 
    return result;
}

Point3D& operator+=(Point3D& a, const Point3D& b) {a = a + b; return a;}
Point3D& operator-=(Point3D& a, const Point3D& b) {a = a - b; return a;}
Point3D& operator*=(Point3D& a, const Point3D& b) {a = a * b; return a;}


/* // ! Fy faen i helvete som denne Octree driten er noe piss, jeg har ikke peiling på hva jeg driver med
// * Define the Octree class
class Octree {
public:
    Octree(float centerX, float centerY, float centerZ, float halfWidth, int maxDepth)
        : centerX(centerX), centerY(centerY), centerZ(centerZ),
          halfWidth(halfWidth), maxDepth(maxDepth) {
        // Initialize this node
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
    }

    ~Octree() {
        // Delete child nodes
        for (int i = 0; i < 8; ++i) {
            delete children[i];
        }
    }

    void insert(Shape3D& shape) {
        // If this node is not a leaf node
        if (maxDepth > 0) {
            // Create child nodes if they don't exist
            if (children[0] == nullptr) {
                float newHalfWidth = halfWidth / 2;
                int newMaxDepth = maxDepth - 1;
                for (int i = 0; i < 8; ++i) {
                    float newCenterX = centerX + newHalfWidth * ((i & 1) ? 1 : -1);
                    float newCenterY = centerY + newHalfWidth * ((i & 2) ? 1 : -1);
                    float newCenterZ = centerZ + newHalfWidth * ((i & 4) ? 1 : -1);
                    children[i] = new Octree(newCenterX, newCenterY, newCenterZ, newHalfWidth, newMaxDepth);
                }
            }

            // Insert the shape into the appropriate child node
            int index = ((shape.position.x > centerX) ? 1 : 0) |
                        ((shape.position.y > centerY) ? 2 : 0) |
                        ((shape.position.z > centerZ) ? 4 : 0);
            children[index]->insert(shape);
        }
        // If this node is a leaf node
        else {
            shapes.push_back(&shape);
        }
    }

    std::vector<Shape3D*> query(const Shape3D& viewFrustum) {
        std::vector<Shape3D*> result;

        // If this node is not a leaf node
        if (maxDepth > 0) {
            // Query child nodes
            for (int i = 0; i < 8; ++i) {
                if (children[i] != nullptr && intersects(viewFrustum, children[i])) {
                    std::vector<Shape3D*> childResult = children[i]->query(viewFrustum);
                    result.insert(result.end(), childResult.begin(), childResult.end());
                }
            }
        }
        // If this node is a leaf node
        else {
            // Return shapes in this node
            result = shapes;
        }

        return result;
    }

    bool intersects(const Shape3DClass& shape, const Octree* node) {
        // Check if the shape's AABB intersects with the node's region
        return !(shape.minX > node->centerX + node->halfWidth ||
                shape.maxX < node->centerX - node->halfWidth ||
                shape.minY > node->centerY + node->halfWidth ||
                shape.maxY < node->centerY - node->halfWidth ||
                shape.minZ > node->centerZ + node->halfWidth ||
                shape.maxZ < node->centerZ - node->halfWidth);
    }

private:
    float centerX, centerY, centerZ;  // The center of the region covered by this node
    float halfWidth;  // Half the width of the region covered by this node
    int maxDepth;  // The maximum depth of the tree
    Octree* children[8];  // The eight children of this node
    std::vector<Shape3D*> shapes;  // The shapes contained in this node
};
*/


// * Rendering functions
bool isPointInScreenBounds(const Point2D &point, int &screenWidth, int &screenHeight) {
    return (point.x >= 0 && point.x < screenWidth && point.y >= 0 && point.y < screenHeight);
}

void drawLine(SDL_Renderer *renderer, Point2D E, Point2D F, Point2D center, Point2D screenSizeMinusCenter) {
    // If the bounding box of both points are outside the screen, then don't draw the line
    if (std::max(E.x, F.x) < -center.x || std::min(E.x, F.x) >= screenSizeMinusCenter.x ||
        std::max(E.y, F.y) < -center.y || std::min(E.y, F.y) >= screenSizeMinusCenter.y) {

        return;
    }

    // If both points are inside the screen, then draw the line
    if ((E.x >= -center.x && E.x < screenSizeMinusCenter.x && E.y >= -center.y && E.y < screenSizeMinusCenter.y) && 
        (F.x >= -center.x && F.x < screenSizeMinusCenter.x && F.y >= -center.y && F.y < screenSizeMinusCenter.y)) {
        
        SDL_RenderDrawLine(renderer, E.x + center.x, E.y + center.y, F.x + center.x, F.y + center.y);
        
        return;
    }

    // * Bresenham line algorithm
    bool steep = std::abs(F.y - E.y) > std::abs(F.x - E.x);

    if (steep) {
        std::swap(E.x, E.y);
        std::swap(F.x, F.y);
    }

    if (E.x > F.x) {
        std::swap(E, F);
    }

    int dx = F.x - E.x;
    int dy = std::abs(F.y - E.y);
    int error = dx >> 1;
    int ystep = (E.y < F.y) ? 1 : -1;
    int y = E.y;

    std::vector<SDL_Point> points;

    for (int x = E.x; x <= F.x; x++) {
        if (steep) {
            if (y >= -center.x && y < screenSizeMinusCenter.x && x >= -center.y && x < screenSizeMinusCenter.y) {
                points.push_back({y + center.x, x + center.y});
            }
            if (x < -center.y) {
                break;
            }
        } else {
            if (x >= -center.x && x < screenSizeMinusCenter.x && y >= -center.y && y < screenSizeMinusCenter.y) {
                points.push_back({x + center.x, y + center.y});
            }
            if (x >= screenSizeMinusCenter.x) {
                break;
            }
        }
        
        error -= dy;

        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }   

    if (!points.empty()) {
        SDL_RenderDrawPoints(renderer, &points[0], points.size());
    }
}

void drawShape(SDL_Renderer *renderer, const Shape2D& shape, const SDL_Color& color, const Point2D& center, const Point2D& screenSize) {
    // Set the renderer's draw color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Calculate screenSizeMinusCenter once
    Point2D screenSizeMinusCenter = screenSize - center;

    // * Draw the shape
    for (int i = 0; i < shape.edges.size(); i++) {
        drawLine(renderer, shape.points[shape.edges[i][0]], shape.points[shape.edges[i][1]], center, screenSizeMinusCenter);
    }
}


inline const Point3D rotateX3D(const Point3D &point, const float &sinAngle, const float &cosAngle) {
    Point3D rotatedPoint;

    rotatedPoint.x = point.x;
    rotatedPoint.y = (point.y * cosAngle) - (point.z * sinAngle);
    rotatedPoint.z = (point.y * sinAngle) + (point.z * cosAngle);

    return rotatedPoint;
}


inline const Point3D rotateY3D(const Point3D &point, const float &sinAngle, const float &cosAngle) {
    Point3D rotatedPoint;

    rotatedPoint.x = (point.x * cosAngle) + (point.z * sinAngle);
    rotatedPoint.y = point.y;
    rotatedPoint.z = (-point.x * sinAngle) + (point.z * cosAngle);
    
    return rotatedPoint;
}


inline const Point3D rotateZ3D(const Point3D &point, const float &sinAngle, const float &cosAngle) {
    Point3D rotatedPoint;

    rotatedPoint.x = (point.x * cosAngle) - (point.y * sinAngle);
    rotatedPoint.y = (point.x * sinAngle) + (point.y * cosAngle);
    rotatedPoint.z = point.z;

    return rotatedPoint;
}


Point3D rotatePoint3D(Camera &camera, const Point3D& point) {
    // Create a quaternion from the point (w=0)
    Quaternion p(0.0f, point.x, point.y, point.z);
    
    // Rotate the point using: q * p * q^-1
    Quaternion qp = camera.quaternion * p;
    Quaternion rotatedP = qp * camera.quaternion.conjugate();
    
    // Extract the rotated coordinates
    return Point3D(rotatedP.x, rotatedP.y, rotatedP.z);
}


void updatePostition3D(const Camera &camera, Shape3D &shape) {
    Point3D offset = camera.position;

    offset.x += camera.focalLength * camera.rotationMatrix.yAxis.pitch;
    // offset.y += camera.focalLength * camera.rotationMatrix.yAxis.yaw;
    offset.z += camera.focalLength * camera.rotationMatrix.yAxis.roll;

    for (int i = 0; i < shape.vertices.size(); i++) {
        shape.vertices[i] = shape.position + shape.verticeGeometry[i] - (offset);
    }
}


Shape2D perspectiveProjection(Camera &camera, Shape3D &shape) {
    Shape2D projectedShape;
    Point3D point;
    
    // ! OLD
    // int denominator;
    // float reciprocal;

    // ! NEW
    float pixelsPerWorldUnit;
    float depth;

    projectedShape.edges = shape.edges;

    updatePostition3D(camera, shape);

    projectedShape.points.reserve(shape.vertices.size());

    for (int i = 0; i < shape.vertices.size(); i++) {
        point = rotatePoint3D(camera, shape.vertices[i]);

        // ! TESTING: backup
        // if ((denominator = ((point.z) + camera.focalLength)) <= 0) {
        //     denominator = 1;
        // }

        // //// reciprocal = fastInvSqrt(denomenator);  // ! Potential memory leak
        // reciprocal = 1.0f / denominator;

        // Point2D projectedPoint = {
        //     static_cast<int>(((point.x) * camera.focalLength) * reciprocal),
        //     static_cast<int>((-point.y * camera.focalLength) * reciprocal)
        // };

        // ! TESTING: New projection method
        // Clamp depth to minimum value
        if ((depth = point.z) < MIN_RENDER_DEPTH) {
            depth = MIN_RENDER_DEPTH;
        }

        pixelsPerWorldUnit = camera.perspectiveProjectionConstant / depth;

        Point2D projectedPoint = {
            static_cast<int>( point.x * pixelsPerWorldUnit),
            static_cast<int>(-point.y * pixelsPerWorldUnit)
        };

        projectedShape.points.push_back(projectedPoint);
    }

    return projectedShape;
}



class Game {
private:
// * Window variables
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Font
    TTF_Font* font;
    
// * Variables for the window loop
    // Window loop
    SDL_Event windowEvent;
    SDL_Color windowColor = BLACK;
    bool windowRunning;


    // Display mode
    SDL_DisplayMode currentDisplayMode;
    bool fullscreenMode = false;

    // FPS
    float fps;
    bool showFPS = true;

    // Set the center of the coordinate system
    Point2D center = {WIDTH / 2, HEIGHT / 2};
    Point2D screenSize = {WIDTH, HEIGHT};

    // Text
    // ! NOTE: When i first tried to create 2 text objects, the program crashed. 
    // !       Turns out it was because I had used up all the memory on the stack, 
    // !       and therefore have to allocate future objects to the heap instead
    Text *fpsText;

    Text *cameraPositionDebugText;
    Text *cameraRotationDebugText;

// * Camera
    Camera camera = Camera(screenSize);

// * Map
    Map map;
    // "testMapVoid": 0, "testMapGround": 1, "testMapObjectLoader": N/A
    int mapID = 0;
    

// * Input
    // Get keyboard
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    // Get mouse
    Point2D mousePosition;
    Uint32 mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    
// * Game loop
    // Set variables for game ticker
    Uint32 currentTime;
    Uint32 elapsedTime;

    // Set variables for FPS counter
    Uint32 lastTime = SDL_GetTicks();
    Uint32 frameCount = 0;



// * Methods
    void handleEvents() {
        // * Movement
        // I have to handle movement events separately because the keyboardState is not necessarily only updated when an SDL_PollEvent is triggered
        camera.move(keyboardState);

        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                windowRunning = false;
            }

            // * Keyboard
            if (SDL_KEYDOWN == windowEvent.type) {
                switch (windowEvent.key.keysym.sym) {
                    case SDLK_F11:
                        if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                            SDL_SetWindowFullscreen(window, 0);
                            SDL_ShowCursor(SDL_ENABLE);
                            
                            center = {WIDTH >> 1, HEIGHT >> 1};
                            screenSize = {WIDTH, HEIGHT};

                            fullscreenMode = false;
                        } else {
                            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
                            SDL_ShowCursor(SDL_DISABLE);

                            center = {currentDisplayMode.w >> 1, currentDisplayMode.h >> 1};
                            screenSize = {currentDisplayMode.w, currentDisplayMode.h};

                            // Set mouse position to center of screen 
                            SDL_WarpMouseInWindow(window, center.x, center.y);

                            fullscreenMode = true;
                        }

                        // Update the perspective projection constant
                        camera.perspectiveProjectionConstant = screenSize.y / camera.screenHeight_world;

                        break;
                    case SDLK_m:
                        std::cout << "Map ID: " << mapID << "\n";

                        switch (mapID % 2) {
                        case 0:
                            setMap("testMapVoid");
                            break;
                        case 1:
                            setMap("testMapGround");

                            mapID = -1; // ! Reset mapID on last map
                            break;
                        }

                        map = getMap();
                        mapID++;

                        break;
                        
                    default:
                        // logMessage("Key pressed: " + std::to_string(windowEvent.key.keysym.sym), __LOGGING_TRACE, __MAIN_LOGID);
                        //
                        // cameraMovementSpeed = (cameraMovementSpeedConstant / (static_cast<int>(fps) + 1));
                        // cameraMovementSpeed = cameraMovementSpeedConstant;
                        // cameraMovementSpeed = elapsedTime / 10.0f;
                        //
                        // logMessage("Camera movement speed: " + std::to_string(cameraMovementSpeed), __LOGGING_DEBUG, __MAIN_LOGID);
                        break;
                };
            }

            // * Mouse
            // If window is focused
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) {
                // Get mouse position
                mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
                mousePosition -= center;
                
                // If mouse is moved
                if (0 != (abs(mousePosition.x) + abs(mousePosition.y)) && fullscreenMode) {
                    // Rotate Camera
                    camera.rotate({
                        -(mousePosition.y) * 0.001f,
                        -(mousePosition.x) * 0.001f,
                        0.0f
                    }, {false, false, false});
                    // */

                    // Set mouse position to center of screen 
                    SDL_WarpMouseInWindow(window, center.x, center.y);

                    // Update cache- and rotation matrix
                }
            }
        }
    }

    void renderFrame() {
        // * Clear the renderer
        SDL_RenderClear(renderer);

        // * Draw new frame
        // FPS
        if (showFPS) {
            // -- Uint32 currentTime = SDL_GetTicks();
            // -- Uint32 elapsedTime = currentTime - lastTime;

            currentTime = SDL_GetTicks();
            elapsedTime = currentTime - lastTime;

            frameCount++;
            
            if (elapsedTime >= 1000) {
                fps = static_cast<float>(frameCount) / (elapsedTime / 1000.0f);
                
                //// std::cout << "FPS: " << fps << std::endl;
                //// logMessage("FPS: " + std::to_string(static_cast<int>(fps)), __LOGGING_INFO, __MAIN_LOGID);
                fpsText->updateText("FPS: " + std::to_string(static_cast<int>(fps)));
                // cameraDebugText->updateText("FPS: " + std::to_string(static_cast<int>(fps)));
                       
                lastTime = currentTime;
                frameCount = 0;
            }

            fpsText->renderText();
        }

        if (elapsedTime % 100 == 0) {
            cameraPositionDebugText->updateText("Position: " + camera.getPositionDebug());
            cameraRotationDebugText->updateText("Rotation: " + camera.getRotationDebug());
        }
        
        // Draw map
        for (Shape3D &shape : map.shapes) {
            drawShape(renderer, perspectiveProjection(camera, shape), WHITE, center, screenSize);
        };

        // Draw text
        cameraPositionDebugText->renderText();
        cameraRotationDebugText->renderText();

    }


public:
    Game(/* args */);
    ~Game();

    void run() {
        windowRunning = true;

        while (windowRunning) {
            // * Handle events
            handleEvents();

            // * Render frame
            renderFrame();

            // * Update the screen
            SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
            SDL_RenderPresent(renderer);
        }
    }

};

Game::Game(/* args */) {
// * Initialize Libaries
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return; 
    }

// * Window
    // Create a window
    window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        // // ! return EXIT_FAILURE;
        return;
    }
    
    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == renderer) {
        std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        // // ! return EXIT_FAILURE;
        return;
    }

    std::cout << "Window and renderer created successfully" << std::endl;

    // Load font
    font = TTF_OpenFont(FONT_PATH, 16);

    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

// * Text
    //// std::cout << "Text contructor call " << std::endl;
    fpsText = new Text({0,  0}, font, renderer);

    cameraPositionDebugText = new Text({0, 30}, font, renderer);
    cameraRotationDebugText = new Text({0, 50}, font, renderer);

// * Map
    // Set map
    // ? setMap("testMapObjectLoader");
    setMap("testMapGround");

    // Load map
    map = getMap();
}

Game::~Game() {
    // * Free all text
    delete fpsText;

    delete cameraPositionDebugText;
    delete cameraRotationDebugText;

    // * Close the font
    TTF_CloseFont(font);

    // * Destroy the window and renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Window and renderer destroyed successfully" << std::endl;
}



int main(int argc, char *argv[]) {
    Game game;

    game.run();

    return 0;
}
