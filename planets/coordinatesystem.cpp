#include <GL/glew.h>
#include "coordinatesystem.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "glbase/gltool.hpp"

CoordinateSystem::CoordinateSystem(std::string name) : Drawable(name) {

}

void CoordinateSystem::draw(glm::mat4 projection_matrix) const {
    if (_program == 0) {
        std::cerr << _name << "not initialized. Call init() first." << std::endl;
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
    glDrawElements(GL_LINES, 2000, GL_UNSIGNED_INT, 0);

    // unbin vertex array object
    glBindVertexArray(0);

    // check for errors
    VERIFY(CG::checkError());
}

void CoordinateSystem::update(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    _modelViewMatrix = modelViewMatrix;
}

std::string CoordinateSystem::getVertexShader() const {
    return Drawable::loadShaderFile(":/shader/coordSys.vs.glsl");
}

std::string CoordinateSystem::getFragmentShader() const {
    return Drawable::loadShaderFile(":/shader/coordSys.fs.glsl");
}

void CoordinateSystem::createObject() {
    std::vector<glm::vec3> positions;
    std::vector<unsigned int> indices;

    // fill vectors with data

    for (int i = -50; i < 50; ++i) {
        positions.emplace_back(i * 2, 0, 100);
        positions.emplace_back(i * 2, 0, -100);
        indices.push_back(positions.size() - 2);
        indices.push_back(positions.size() - 1);
    }
    for (int i = -50; i < 50; ++i) {
        positions.emplace_back(100, 0, i * 2);
        positions.emplace_back(-100, 0, i * 2);
        indices.push_back(positions.size() - 2);
        indices.push_back(positions.size() - 1);
    }

    // Set up a vertex array object for the geometry
    if (_vertexArrayObject == 0)
        glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

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
    glDrawArrays(GL_POINTS, 0, 4);


}
