#version 400

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

// get position from vertex array object
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;

// send color to fragment shader
out vec3 vcolor;

void main(void)
{
    gl_Position = projection_matrix * modelview_matrix * vec4(pos, 1);
    vcolor = pos;
}
