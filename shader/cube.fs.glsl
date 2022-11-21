#version 400

// get color from vertex shader
// in vec3 vcolor;
in vec2 TexCoords;
in vec3 normal;
in vec3 fpos;

// color parameter
uniform int colorEnable;
uniform sampler2D ourTexture;
uniform vec3 lightpos;
uniform vec3 model;
// send color to screen
layout (location = 0) out vec4 fcolor;

void main(void) {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightpos - (fpos));
    float diff = max(dot(norm, lightDir), 0.0);
    
    if (colorEnable == 1) {
        // fcolor = vec4(0.0, 1.0, 0.0, 1.0);
        vec4 result = diff * texture(ourTexture, TexCoords);
        fcolor = vec4(result);
    } else {
        // set fragment color
        // fcolor = vec4(normalize(vcolor), 1);
        vec4 result = (diff+0.1) * texture(ourTexture, TexCoords);
        fcolor = result;//vec4(result.x, result.y, result.z, 1.0);
    }
}
