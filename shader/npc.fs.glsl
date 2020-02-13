#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;

out vec4 fFragColor;


uniform sampler2D uTexture;
uniform vec3 uLightPosition;
uniform int uDay;

/**
 * Compute the diffuse lighting of the fragment.
 *
 * @return The computed diffuse lighting.
 */
vec3 computeDiffuseLighting(vec3 lightDirection, vec3 lightColor) {
    vec3 diffuse = vec3(max(dot(vNormal, lightDirection), 0.0f));
    return diffuse * lightColor;
}



void main() {
    vec4 textureColor = texture(uTexture, vec2(vTexture.x, vTexture.y));

    vec3 light;
    if (uDay == 1) {
        vec3 lightColor = vec3(1);
        vec3 lightPosition = vec3(1000, 1000, 1000);
        vec3 lightDirection = normalize(lightPosition - vPosition);

        vec3 diffuse = vec3(computeDiffuseLighting(lightDirection, lightColor));
        vec3 ambient = vec3(.4);
        light = diffuse + ambient;
    }
    else {
        light = vec3(.1);
    }

    fFragColor = vec4(
        min(1.f, light.x),
        min(1.f, light.y),
        min(1.f, light.z),
        1
    ) * textureColor;
}
