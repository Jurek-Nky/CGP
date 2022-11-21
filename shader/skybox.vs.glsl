#version 400

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

layout(location = 0) in vec3 position;

out vec3 TexCoords;

void main(){
    vec4 pos = projection_matrix * modelview_matrix * vec4(position, 1);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    TexCoords = position;
}
