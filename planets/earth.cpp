#include <GL/glew.h>
#include "earth.h"

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "gui/config.h"
#include "gltool.hpp"

Earth::Earth(std::string name, float radius, float distance, float hoursPerDay, float daysPerYear,
             std::string textureLocation) : Planet(name, radius, distance, hoursPerDay, daysPerYear, textureLocation) {
    _localRotationSpeed = 1.0f / hoursPerDay;
    _globalRotationSpeed = 1.0f / daysPerYear;
}

void Earth::init() {
    Drawable::init();
    for (auto &i: _children) {
        i->init();
    }
    Planet::calculatePath(_modelViewMatrix);
}

void Earth::recreate() {
    Drawable::recreate();
    for (auto &i: _children) {
        i->recreate();
    }
}

void Earth::draw(glm::mat4 projection_matrix) {
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
    // adding parameter to shader
    GLuint colorEnable = 0;
    glUniform1i(glGetUniformLocation(_program, "colorEnable"), colorEnable);
    // call draw
    glDrawElements(GL_TRIANGLES, Config::resolutionV * Config::resolutionU * 6, GL_UNSIGNED_INT, 0);


    // if grid is enabled draw a grid around all triangles of the sphere
    if (Config::gridEnable) {
        glDisable(GL_DEPTH_TEST);
        colorEnable = 1;
        glUniform1i(glGetUniformLocation(_program, "colorEnable"), colorEnable);

        glDrawElements(GL_LINES, Config::resolutionU * Config::resolutionV * 6, GL_UNSIGNED_INT, 0);
        glEnable(GL_DEPTH_TEST);
    }

    //draw all children
    for (const auto &i: _children) {
        i->draw(projection_matrix);
    }

    // unbin vertex array object
    glBindVertexArray(0);

    // check for errors
    VERIFY(CG::checkError());
}

void Earth::update(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    // check if resolution changed and recreate object
    if (_oldResolutionV != Config::resolutionV || _oldResolutionU != Config::resolutionU) {
        recreate();
    }

    // calculate new local rotation
    if (Config::localRotationEnable) {
        _localRotation += elapsedTimeMs * _localRotationSpeed * Config::animationSpeed;
    }

    // calculate new global rotation
    if (Config::globalRotationEnable) {
        _globalRotation += elapsedTimeMs * _globalRotationSpeed * Config::animationSpeed;
    }
    // keeping rotations in range of 0-360
    _localRotation = std::fmod(_localRotation, 360.0f);
    _globalRotation = std::fmod(_globalRotation, 360.f);

    // calculating new x and y for the translation
    float x = _center.x + (_distance * glm::cos(glm::radians(_globalRotation)));
    float y = _center.z + (_distance * glm::sin(glm::radians(_globalRotation)));
    _modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(x, 0, y));

    // updating center of all children and call update
    for (const auto &i: _children) {
        // updating center point for all children
        i->_center = glm::vec3(x, 0, y);
        // calling update for all children
        i->update(elapsedTimeMs, modelViewMatrix);
    }
    // rotate around y-axis
    _modelViewMatrix = glm::rotate(_modelViewMatrix, glm::radians(_localRotation), glm::vec3(0, 1, 0));
}