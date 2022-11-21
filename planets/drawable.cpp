#include <GL/glew.h>

#include "drawable.h"

#include <iostream>

#include <QFile>
#include <QTextStream>

#include "glbase/gltool.hpp"

#include "image/image.h"

Drawable::Drawable(std::string name):
    _name(name), _vertexArrayObject(0), _modelViewMatrix(1.0f)
{

}

void Drawable::init()
{
    initShader();
    createObject();
}

void Drawable::recreate()
{
    createObject();
}

void Drawable::initShader()
{
    GLuint vs = CG::createCompileShader(GL_VERTEX_SHADER, getVertexShader()); VERIFY(vs);
    GLuint fs = CG::createCompileShader(GL_FRAGMENT_SHADER, getFragmentShader()); VERIFY(fs);

    _program = glCreateProgram();
    glAttachShader(_program, vs);
    glAttachShader(_program, fs);
    _program = CG::linkProgram(_program);

    VERIFY(_program);
}


std::string Drawable::loadShaderFile(std::string path) const
{
    QFile f(path.c_str());
    if (!f.open(QFile::ReadOnly | QFile::Text))
        std::cout << "Could not open file " << path << std::endl;
    QTextStream in(&f);
    return in.readAll().toStdString();
}

GLuint Drawable::loadTexture(std::string path){

    Image image(path);
    
    GLuint texture;
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
        // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (image.getData())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    /// TODO your code here

    // Hint: you can use image.width(), image.height() and image.data()

    return texture;
}
