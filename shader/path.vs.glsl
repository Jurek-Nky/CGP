#version 400

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

// get position from vertex array object
layout(location = 0) in vec3 pos;

void main(void)
{
    // calculate position in model view projection space
    gl_Position = projection_matrix * modelview_matrix * vec4(pos, 1);
}
