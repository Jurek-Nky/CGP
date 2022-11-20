#ifndef GRAPRA_2015_TYCHO_BRAHE_SATURN_H
#define GRAPRA_2015_TYCHO_BRAHE_SATURN_H


#include <string>
#include "planet.h"

class Ring;

class Saturn : public Planet {
public:
    Saturn(std::string name = "Saturn",
           float radius = 1.f,
           float distance = 1.f,
           float hoursPerDay = 250.f,
           float daysPerYear = 365.f,
           std::string textureLocation = ":/res/images/saturn.bmp");

    virtual void init();

    virtual void recreate();

    virtual void draw(glm::mat4 projection_matrix) const;

    virtual void update(float elapsedTimeMs, glm::mat4 modelViewMatrix);

protected:
    std::shared_ptr<Ring> _ring;
};


#endif //GRAPRA_2015_TYCHO_BRAHE_SATURN_H
