#ifndef CONFIG_H
#define CONFIG_H

#include "glm/vec3.hpp"

/**
 * @brief The global configuration
 *
 * This class contains global configuration parameters
 * that are used all over the program.
 *
 * Hint: Add as many parameters as you need.
 */
class Config{
public:

    static float camZoom;
    static bool localRotationEnable;
    static bool globalRotationEnable;
    static bool gridEnable;
    static bool coordSysEnable;
    static bool lightingEnable;
    static bool orbitEnable;

    static float animationSpeed;

    static bool deathStarActive;
    static bool deathStarPreviewEnable;
    static float deathStarLaserLen;
    static float deathStarLaserRad;

    static bool planetPathEnable[12];

    static std::string currentPathPlanet;

    static int resolutionU;
    static int resolutionV;
    static int resolutionRing;

    // saving viewpoint for the camera in config, so that it
    // can be accessed by main window
    static glm::vec3 viewPoint;
    static glm::vec3 viewPointCenter;

    static glm::vec2 windowResolution;
};

#endif // CONFIG_H

