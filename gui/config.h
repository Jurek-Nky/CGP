#ifndef CONFIG_H
#define CONFIG_H

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
    static bool lightingEnable;
    static bool orbitEnable;

    static float animationSpeed;

    static bool deathStarActive;
    static bool deathStarPreviewEnable;
    static float deathStarLaserLen;
    static float deathStarLaserRad;

    static bool planetPathEnable[12];

    static float resolutionU;
    static float resolutionV;
    static float resolutionRing;
};

#endif // CONFIG_H

