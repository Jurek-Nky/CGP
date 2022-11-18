#include <GL/glew.h>

#include "orbit.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

#include "glbase/gltool.hpp"

#include "gui/config.h"
#include "glbase/geometries.hpp"

Orbit::Orbit(std::string name, float radius) : Drawable(name), _radius(radius) {

}

void Orbit::draw(glm::mat4 projection_matrix) const {
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
    glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0);
    // enable depth test again
    glEnable(GL_DEPTH_TEST);

    // unbin vertex array object
    glBindVertexArray(0);

    // check for errors
    VERIFY(CG::checkError());
}

void Orbit::update(float elapsedTimeMs, glm::mat4 modelViewMatrix) {
    _modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(_center.x, 0, _center.z));
}

std::string Orbit::getVertexShader() const {
    return Drawable::loadShaderFile(":/shader/orbit.vs.glsl");
}

std::string Orbit::getFragmentShader() const {
    return Drawable::loadShaderFile(":/shader/orbit.fs.glsl");
}

void Orbit::createObject() {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<unsigned int> indices;

    geom_disk(positions, normals, texcoords, indices, _radius / (_radius + 0.02), 100);

    glm::vec3 axis = glm::vec3(1, 0, 0);
    for (auto &position: positions) {
        position = position * _radius * 1.5f;
        position = glm::mat3(glm::rotate(glm::half_pi<float>(), axis)) * position;
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

    GLuint normals_buffer;
    glGenBuffers(1, &normals_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normals_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * 3 * sizeof(float), normals.data(), GL_STATIC_DRAW);
    GLintptr normalsOffset = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) normalsOffset);
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
    glDeleteBuffers(1, &normals_buffer);

    // check for errors
    VERIFY(CG::checkError());
}
