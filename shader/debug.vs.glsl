#{{ HEADER }}

layout (location = 0) in vec4 aVertex;

uniform mat4 uProjection;

out vec2 vTexture;


void main() {
    vTexture = aVertex.zw;
    gl_Position = uProjection * vec4(aVertex.xy, 0.0, 1.0);
}
