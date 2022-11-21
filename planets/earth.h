#ifndef EARTH_H
#define EARTH_H


#include "planet.h"

class Earth : public Planet{
public:
    Earth(std::string name = "Erde", float radius = 1.f, float distance = 1.f, float hoursPerDay = 1.f,
          float daysPerYear = 1.f, std::string textureLocation = ":/res/images/earth.bmp");

    void init() override;

    virtual void draw(glm::mat4 projection_matrix);

    void update(float elapsedTimeMs, glm::mat4 modelViewMatrix) override;

    void recreate() override;

};


#endif
