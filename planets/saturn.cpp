#include "saturn.h"
#include "planets/ring.h"

Saturn::Saturn(std::string name, float radius, float distance, float hoursPerDay, float daysPerYear,
               std::string textureLocation) : Planet(name, radius, distance, hoursPerDay, daysPerYear,
                                                     textureLocation) {
    // create ring object around the planet
    _ring = std::make_shared<Ring>(name + "Ring", _radius);
}

void Saturn::init() {
    Planet::init();
    _ring->init();
}

void Saturn::recreate() {
    Planet::recreate();
    _ring->recreate();
}


void Saturn::draw(glm::mat4 projection_matrix) const {
    Planet::draw(projection_matrix);
    _ring->draw(projection_matrix);
}

void Saturn::update(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    Planet::update(elapsedTimeMs, modelViewMatrix);
    _ring->update(elapsedTimeMs, _modelViewMatrix);
}



