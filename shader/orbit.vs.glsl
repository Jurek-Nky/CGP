#version 400

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

layout(location = 0) in vec3 position;

out vec3 vcolor;
void main(){
    gl_Position = projection_matrix * modelview_matrix * vec4(position, 1);

}