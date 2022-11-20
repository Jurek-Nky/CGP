#include <GL/glew.h>
#include "path.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glbase/gltool.hpp"

#include "gui/config.h"
#include "glm/gtc/matrix_transform.hpp"

Path::Path(std::string name) :
        Drawable(name) {

}

void Path::draw(glm::mat4 projection_matrix) const {
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

    // disable depth test so that path is drawn over the coordinate system
    glDisable(GL_DEPTH_TEST);
    // call draw
    glDrawElements(GL_LINE_STRIP, _indices.size(), GL_UNSIGNED_INT, 0);
    // enable depth test again
    glEnable(GL_DEPTH_TEST);

    // unbin vertex array object
    glBindVertexArray(0);

    // check for errors
    VERIFY(CG::checkError());
}

void Path::createObject() {
    // Set up a vertex array object for the geometry
    if (_vertexArrayObject == 0)
        glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);

    // fill vertex array object with data
    GLuint position_buffer;
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, _positions.size() * 3 * sizeof(float), _positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Hint: the texture coordinates buffer is missing

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

    // unbind vertex array object
    glBindVertexArray(0);
    // delete buffers (the data is stored in the vertex array object)
    glDeleteBuffers(1, &position_buffer);
    glDeleteBuffers(1, &index_buffer);

    // check for errors
    VERIFY(CG::checkError());

}

void Path::update(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    _modelViewMatrix = glm::lookAt(
            glm::vec3(
                    Config::viewPoint[0] * Config::camZoom,
                    Config::viewPoint[1] * Config::camZoom,
                    Config::viewPoint[2] * Config::camZoom),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));
}

void Path::addPosition(glm::vec3 position) {
    _positions.push_back(position);
    _indices.push_back(_positions.size() - 1);
}

std::string Path::getVertexShader() const {
    return Drawable::loadShaderFile(":/shader/path.vs.glsl");
}

std::string Path::getFragmentShader() const {
    return Drawable::loadShaderFile(":/shader/path.fs.glsl");
}
