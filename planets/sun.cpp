#include <GL/glew.h>

#include "sun.h"

#include <glm/gtx/transform.hpp>
#include "glbase/gltool.hpp"

Sun::Sun(std::string name, float radius, float distance, float hoursPerDay, float daysPerYear, std::string textureLocation):
    Planet(name, radius, distance, hoursPerDay, daysPerYear, textureLocation)
{

}

glm::vec3 Sun::getPosition() const
{
    /// TODO: return the position of the sun in model view coordinates
    float x = _center.x + (_distance * glm::cos(glm::radians(_globalRotation)));
    float y = _center.z + (_distance * glm::sin(glm::radians(_globalRotation)));
    // Hint: the model view matrix is part of the super class
    
    return glm::vec3(x, 0, y);
}

