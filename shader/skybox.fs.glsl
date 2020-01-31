#{{ HEADER }}

in vec3 vTexture;

uniform samplerCube uCubemap;

out vec4 fFragColor;


void main() {
    fFragColor = texture(uCubemap, vTexture);
}
