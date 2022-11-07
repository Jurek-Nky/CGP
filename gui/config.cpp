#include "config.h"

/*
 *  Default values. Change them as needed.
 */

float Config::animationSpeed = 1.0f;

float Config::camZoom = 5.0f;

bool Config::localRotationEnable = true;
bool Config::globalRotationEnable = true;
bool Config::gridEnable = true;
bool Config::coordSysEnable = true;
bool Config::lightingEnable = true;
bool Config::orbitEnable = true;

bool Config::deathStarActive = true;
bool Config::deathStarPreviewEnable = true;
float Config::deathStarLaserLen = 1.0;
float Config::deathStarLaserRad = 1.0;

bool Config::planetPathEnable[] = {false,       // earth
                                   false,       // moon
                                   false,       // sun
                                   false,       // mercury
                                   false,       // venus
                                   false,       // mars
                                   false,       // jupiter
                                   false,       // saturn
                                   false,       // io
                                   false,       // europa
                                   false,       // ganymede
                                   false        // callisto
};


float Config::resolutionU = 1.0;
float Config::resolutionV = 1.0;
float Config::resolutionRing = 1.0;
