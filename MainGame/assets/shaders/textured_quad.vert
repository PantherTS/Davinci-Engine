#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

layout (location = 0) uniform mat4 u_VP;
layout (location = 1) uniform mat4 u_Model;
layout (location = 2) uniform vec2 u_UVOffset;
layout (location = 3) uniform vec2 u_UVScale;

out vec2 v_UV; // This goes to the Fragment Shader

void main() {
    // Apply UV scrolling/scaling (useful for animations or tiling)
    v_UV = (aUV * u_UVScale) + u_UVOffset;
    
    // Standard MVP transformation
    gl_Position = u_VP * u_Model * vec4(aPos, 0.0, 1.0);
}
