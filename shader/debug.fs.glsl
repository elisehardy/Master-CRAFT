#{{ HEADER }}

in vec2 vTexture;

uniform sampler2D uTexture;
uniform vec3 uTextColor;

out vec4 fFragColor;


void main() {
    fFragColor = vec4(uTextColor, 1.0) * vec4(1.0, 1.0, 1.0, texture(uTexture, vTexture).r);
}  
