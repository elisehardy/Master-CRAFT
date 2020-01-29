#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;
flat in int vType;

out vec3 fFragColor;

uniform sampler2D uTexture;
uniform int uTextureVerticalOffset;

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
    vec2 texCoord = vec2((vTexture.x + float(vType)) / 6., 0);

    if (vType == 1) {
        texCoord.y = (vTexture.y + float(uTextureVerticalOffset)) / 64.;
    } else {
        texCoord.y = vTexture.y / 64.;
    }

    vec3 objectColor = texture(uTexture, vec2(texCoord.x, texCoord.y)).xyz;
    if (vType == 1) {
        objectColor += vec3(0, 0, 1);
    }

    vec3 result = ambientLight() + diffuseLight(vNormal, vec3(1, 1, -1));
    fFragColor = result * objectColor;
}
