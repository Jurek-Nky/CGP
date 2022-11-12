#version 400

// get color from vertex shader
in vec3 vcolor;

// color parameter
uniform int colorEnable;

// send color to screen
layout (location = 0) out vec4 fcolor;

void main(void)
{
    if (colorEnable == 1) {
        fcolor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else {
        // set fragment color
        fcolor = vec4(normalize(vcolor), 1);
    }
}
