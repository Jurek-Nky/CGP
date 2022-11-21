#version 400

out vec4 fcolor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
    fcolor = texture(skybox, TexCoords);
}
