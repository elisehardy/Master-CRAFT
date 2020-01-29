#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;

out vec3 fFragColor;

uniform sampler2D uTexture;


vec3 ambientLight() {
    float ambientStrength = 0.33;
    return ambientStrength * vec3(1);;
}

vec3 diffuseLight(vec3 normal, vec3 lightDir) {
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), .3);
    return diff * vec3(1);
}

void main() {
    vec3 objectColor = texture(uTexture, vec2(vTexture.x, vTexture.y)).xyz;
    vec3 result = ambientLight() + diffuseLight(vNormal, vec3(1, 1, -1));
    fFragColor = result * objectColor;
}
