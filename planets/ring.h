#ifndef RING_H
#define RING_H

#include "planets/drawable.h"
#include "glm/vec3.hpp"

class Ring : public Drawable {
public:
    Ring(std::string name = "UNKNOWN RING", float radius = 1.f);

public:
    virtual void draw(glm::mat4 projection_matrix) const override;

    virtual void update(float elapsedTimeMs, glm::mat4 modelViewMatrix) override;

protected:
    virtual std::string getVertexShader() const override;

    virtual std::string getFragmentShader() const override;

    virtual void createObject() override;

    float _radius;       /**< The radius of the orbit */

    int _oldResolutionRing;
};

#endif // RING_H
