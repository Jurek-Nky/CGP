#include <GL/glew.h>
#include "planet.h"


#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <stack>

#include "glbase/gltool.hpp"

#include "gui/config.h"

#include "planets/cone.h"
#include "planets/sun.h"
#include "planets/orbit.h"
#include "planets/path.h"
#include "glbase/geometries.hpp"

Planet::Planet(std::string name,
               float radius,
               float distance,
               float hoursPerDay,
               unsigned int daysPerYear,
               std::string textureLocation) :
        Drawable(name),
        _radius(radius),
        _distance(distance),
        _localRotation(0),
        _localRotationSpeed(0),
        _daysPerYear(daysPerYear),
        _center(glm::vec3(0, 0, 0)),
        _globalRotationAngle(0) {
    _localRotationSpeed = 1.0f / hoursPerDay; // for local rotation:one step equals one hour

    _orbit = std::make_shared<Orbit>(name + " Orbit", _distance);
    _path = std::make_shared<Path>(name + " Pfad");

    /// TODO: init global rotation parameters
}

void Planet::init() {
    Drawable::init();

    /// TODO: load texture

    /// TODO: init children, orbit and path
    for (auto &i: _children) {
        i->init();
    }
}

void Planet::recreate() {
    Drawable::recreate();
    /// TODO: recreate all drawables that belong to this planet
    // Hint: not all drawables need to be recreated
}


void Planet::draw(glm::mat4 projection_matrix) const {

    /// TODO: replace this with your code

    /// TODO: call draw on all drawables that belong to the planet

    if (_program == 0) {
        std::cerr << "Planet" << _name << "not initialized. Call init() first." << std::endl;
        return;
    }

    // Load program
    glUseProgram(_program);

    // bin vertex array object
    glBindVertexArray(_vertexArrayObject);

    // set parameter
    glUniformMatrix4fv(glGetUniformLocation(_program, "projection_matrix"), 1, GL_FALSE,
                       glm::value_ptr(projection_matrix));
    glUniformMatrix4fv(glGetUniformLocation(_program, "modelview_matrix"), 1, GL_FALSE,
                       glm::value_ptr(_modelViewMatrix));

    // call draw
    int vertices = Config::resolutionV * Config::resolutionU * 6;
    glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
    for (const auto &i: _children) {
        i->draw(projection_matrix);
    }

    // unbin vertex array object
    glBindVertexArray(0);

    // check for errors
    VERIFY(CG::checkError());
}

void Planet::update(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    ///TODO: calculate global rotation

    ///TODO: update all drawables that belong to the planet
    if (_oldResolutionV != Config::resolutionV || _oldResolutionU != Config::resolutionU){
        createObject();
    }

    // calculate new local rotation
    if (Config::localRotationEnable)
        _localRotation += elapsedTimeMs * _localRotationSpeed * Config::animationSpeed;
    _localRotation = std::fmod(_localRotation, 360.0f);

    // apply local rotation to model view matrix
    // Hint: The stack is currently useless, but could be useful for you
    std::stack<glm::mat4> modelview_stack;

    modelview_stack.push(modelViewMatrix);

    //global rotation
    if (Config::globalRotationEnable) {
        float rotationFactor = 2 * glm::pi<float>() / float(_daysPerYear) * _localRotationSpeed / 60;
        _globalRotationAngle = std::fmod(
                (_globalRotationAngle + elapsedTimeMs * Config::animationSpeed * rotationFactor),
                (2 * glm::pi<float>()));
    }

    float x = _center[0] + (_distance * glm::cos(_globalRotationAngle));
    float y = _center[2] + (_distance * glm::sin(_globalRotationAngle));
    modelview_stack.top() = glm::translate(modelview_stack.top(), glm::vec3(x, 0, y));

    //update center for all children
    for (auto &i: _children) {
        i->_center = glm::vec3(x, 0, y);
    }

    // rotate around y-axis
    modelview_stack.top() = glm::rotate(modelview_stack.top(), glm::radians(_localRotation), glm::vec3(0, 1, 0));
    _modelViewMatrix = glm::mat4(modelview_stack.top());

    modelview_stack.pop();


    for (const auto &i: _children) {
        i->update(elapsedTimeMs, modelViewMatrix);
    }
}

void Planet::setLights(std::shared_ptr<Sun> sun, std::shared_ptr<Cone> laser) {
    _sun = sun;
    _laser = laser;
    for (auto child: _children)
        child->setLights(sun, laser);
}

void Planet::addChild(std::shared_ptr<Planet> child) {
    _children.push_back(child);
}

void Planet::createObject() {

    /// TODO replace with your code

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<unsigned int> indices;

    geom_sphere(positions, normals, texcoords, indices, Config::resolutionU, Config::resolutionV);
    _oldResolutionU = Config::resolutionU;
    _oldResolutionV = Config::resolutionV;
    // Set up a vertex array object for the geometry
    if (_vertexArrayObject == 0)
        glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    for (auto &position: positions) {
        position = position * _radius;
    };
    // fill vertex array object with data
    GLuint position_buffer;
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * 3 * sizeof(float), positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Hint: the texture coordinates buffer is missing

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // unbind vertex array object
    glBindVertexArray(0);
    // delete buffers (the data is stored in the vertex array object)
    glDeleteBuffers(1, &position_buffer);
    glDeleteBuffers(1, &index_buffer);

    // check for errors
    VERIFY(CG::checkError());

    // Hint: save the number of vertices for drawing
}

std::string Planet::getVertexShader() const {
    return Drawable::loadShaderFile(":/shader/cube.vs.glsl");

}

std::string Planet::getFragmentShader() const {
    return Drawable::loadShaderFile(":/shader/cube.fs.glsl");
}

Planet::~Planet() {
}


/*************************************************
 * Hint: You don't need to change the code below *
 *************************************************/

void Planet::calculatePath(glm::mat4 modelViewMatrix) {
    // Hint: if you have some time left you can optimize this method
    for (auto child: _children) {
        unsigned int longestCommonMultiple = child->getCommonYears(_daysPerYear);
        for (unsigned int i = 0; i <= longestCommonMultiple; i++) {
            float step = 360.0f * _daysPerYear / Config::animationSpeed;
            child->updatePath(step, modelViewMatrix);
        }
    }
    createPath();
}


unsigned int Planet::getCommonYears(unsigned int other) {
    unsigned int tmp = other * _daysPerYear / greatestCommonDivisor(other, _daysPerYear);
    unsigned int result = tmp;
    for (auto child: _children) {
        result = std::max(result, child->getCommonYears(tmp));
    }
    return result;
}

unsigned int Planet::greatestCommonDivisor(unsigned int a, unsigned int b) {
    if (b == 0)
        return a;
    else
        return greatestCommonDivisor(b, a % b);
}

void Planet::updatePath(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    update(elapsedTimeMs, modelViewMatrix);
    addPathPoint();
}

void Planet::addPathPoint() {
    _path->addPosition(glm::vec3(_modelViewMatrix * glm::vec4(0, 0, 0, 1)));
    for (auto child: _children)
        child->addPathPoint();
}

void Planet::createPath() {
    _path->recreate();
    for (auto child: _children)
        child->createPath();
}