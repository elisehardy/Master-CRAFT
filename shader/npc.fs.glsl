#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;

out vec4 fFragColor;


uniform sampler2D uTexture;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform float uLightDirIntensity;
uniform float uLightAmbIntensity;


/**
 * Compute the diffuse lighting of the fragment.
 *
 * @return The computed diffuse lighting.
 */
vec3 computeDiffuseLighting() {
    vec3 lightDirection = normalize(uLightPosition - vPosition);
    vec3 diffuse = vec3(max(dot(vNormal, lightDirection), 0.0f));
    return diffuse * uLightDirIntensity;
}


void main() {
    vec4 textureColor = texture(uTexture, vec2(vTexture.x, vTexture.y));

    vec3 diffuse = computeDiffuseLighting();
    vec3 ambient = vec3(uLightAmbIntensity);
    vec3 light =  (diffuse + ambient) * uLightColor;

    fFragColor = vec4(
    min(1.f, light.x),
    min(1.f, light.y),
    min(1.f, light.z),
    1
    ) * textureColor;
}
