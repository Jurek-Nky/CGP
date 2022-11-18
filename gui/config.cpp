#include <string>
#include "config.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

float Config::animationSpeed = 1.0f;

float Config::camZoom = 5.0f;

bool Config::localRotationEnable = true;
bool Config::globalRotationEnable = true;
bool Config::gridEnable = false;
bool Config::coordSysEnable = false;
bool Config::lightingEnable = true;
bool Config::orbitEnable = false;

bool Config::deathStarActive = true;
bool Config::deathStarPreviewEnable = true;
float Config::deathStarLaserLen = 1.0;
float Config::deathStarLaserRad = 1.0;

std::string Config::currentPathPlanet = "";


int Config::resolutionU = 40;
int Config::resolutionV = 20;
int Config::resolutionRing = 50;

glm::vec3 Config::viewPoint = glm::vec3(0, 0, 5);
glm::vec3 Config::viewPointCenter = glm::vec3(0, 0, 0);

glm::vec2 Config::windowResolution = glm::vec2(0.f, 0.f);