#version 460 core

// Input from Vertex Shader
in vec2 v_UV;

// Output color to the framebuffer
layout (location = 0) out vec4 f_Color;

// Texture sampler - Location 4 matches glUniform1i(4, 0)
layout (location = 4) uniform sampler2D uTexture;

void main()
{
    // Sample the texture at the calculated UV coordinates
    vec4 texColor = texture(uTexture, v_UV);

    // Alpha Clipping (Optional but recommended for 2D)
    // Discards the pixel if it's fully transparent
    if(texColor.a < 0.1)
        discard;

    f_Color = texColor;
}