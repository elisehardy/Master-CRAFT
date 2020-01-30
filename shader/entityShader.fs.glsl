#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;

out vec3 fFragColor;

uniform sampler2D uTexture;


/**
 * Compute the diffuse lighting of the fragment.
 *
 * @param fragNormal Normal of the fragment.
 * @param lightDirection Direction of the light source.
 * @param lightColor Color of the light.
 *
 * @return The computed diffuse lighting.
 */
vec3 computeDiffuseLighting(vec3 fragNormal, vec3 lightDirection, vec3 lightColor) {
    vec3 diffuse = vec3(max(dot(fragNormal, lightDirection), 0.0));
    return diffuse * lightColor;
}



void main() {
    vec3 lightColor = vec3(1);
    vec3 lightPosition = vec3(0, 200, 0);
    vec3 lightDirection = normalize(lightPosition - vPosition);

    vec3 textureColor = texture(uTexture, vec2(vTexture.x, vTexture.y)).xyz;
    vec3 diffuse = computeDiffuseLighting(vNormal, lightDirection, lightColor);
    vec3 ambient = vec3(0.4);

    fFragColor = (diffuse + ambient) * textureColor;
}
