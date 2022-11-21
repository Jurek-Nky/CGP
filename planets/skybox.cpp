#include <GL/glew.h>

#include "skybox.h"

#include <glm/gtc/type_ptr.hpp>

#include "glbase/gltool.hpp"

#include "glbase/geometries.hpp"

#include <iostream>
#include "gui/config.h"

#include "glm/gtc/matrix_transform.hpp"
#include "image/image.h"
Skybox::Skybox(std::string name): Drawable(name)
{
}

void Skybox::init()
{
    Drawable::init();
    cubemap_texture = Skybox::loadTexture(":/res/images/stars.bmp");
    /// TODO: your code here
}

void Skybox::draw(glm::mat4 projection_matrix) const
{
    /// TODO: your code here
    if (_program == 0) {
        std::cerr << "Skybox" << _name << "not initialized. Call init() first." << std::endl;
        return;
    }
    // Load program
    glUseProgram(_program);
    
    glDepthFunc(GL_LEQUAL);
    
    // set parameter
    glUniformMatrix4fv(glGetUniformLocation(_program, "projection_matrix"), 1, GL_FALSE,
                       glm::value_ptr(projection_matrix));
    glUniformMatrix4fv(glGetUniformLocation(_program, "modelview_matrix"), 1, GL_FALSE,
                       glm::value_ptr(_modelViewMatrix));
    
    
    glBindVertexArray(_vertexArrayObject);
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);

    // bind vertex array object
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    
    glDepthFunc(GL_LESS);
}

void Skybox::update(float elapsedTimeMs, glm::mat4 modelViewMatrix)
{
    /// TODO: your code here
    _modelViewMatrix = glm::lookAt(
            glm::vec3(
                    Config::viewPoint[0] * Config::camZoom,
                    Config::viewPoint[1] * Config::camZoom,
                    Config::viewPoint[2] * Config::camZoom),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 1.f, 0.f));
}

std::string Skybox::getVertexShader() const
{
    /// TODO: your code here
    return Drawable::loadShaderFile(":/shader/skybox.vs.glsl");
}

std::string Skybox::getFragmentShader() const
{
    /// TODO: your code here
    return Drawable::loadShaderFile(":/shader/skybox.fs.glsl");
}

GLuint Skybox::loadTexture(std::string path)
{
    /// TODO: your code here
    // Hint: you can use GL_TEXTURE_CUBE_MAP instead of default textures
    
    Image image(path);
    
    GLuint texture;
    
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    
    
    for (unsigned int i = 0; i < 6; i++)
    {
        if (image.getData())
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
        }
        else
        {
            std::cout << "Failed to load cubemap texture" << std::endl;
        }
    }
    /// TODO your code here
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // set texture wrapping GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
        // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Hint: you can use image.width(), image.height() and image.data()

    return texture;
}

void Skybox::createObject()
{
    ///TODO: your code here
    ///
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    std::vector<unsigned int> indices;
    
    geom_cube(positions, normals, texcoords, indices);
    for (auto &position: positions) {
        position = position * 100000.0f;
    };
    if (_vertexArrayObject == 0)
        glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);
    
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
    glEnableVertexAttribArray(1);
    
    GLuint texcoords_buffer;
    glGenBuffers(1, &texcoords_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, texcoords_buffer);
    glBufferData(GL_ARRAY_BUFFER, texcoords.size() * 2 * sizeof(float), texcoords.data(), GL_STATIC_DRAW);
    GLintptr texcoordsOffset = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) texcoordsOffset);
    glEnableVertexAttribArray(2);

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
    glDeleteBuffers(1, &texcoords_buffer);

    // check for errors
    VERIFY(CG::checkError());
}

