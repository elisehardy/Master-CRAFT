#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;
in vec2 vTextureOffset;
flat in int vFace;
flat in int vAlpha;
flat in int vAnimated;

uniform vec3 uCamera;
uniform vec3 uLightColor;
uniform vec3 uLightPosition;
uniform int uVerticalOffset;
uniform sampler2D uTexture;

out vec4 fFragColor;


/**
 * Compute the color of the fragment according to uTexture.
 *
 * @return The computed color.
 */
vec4 computeTextureColor() {
    vec2 textureCoordinates = vec2((vTexture.x + vTextureOffset.x) / 8.f, 0);

    if (vAnimated != 0) {
        textureCoordinates.y = (vTexture.y + float(uVerticalOffset)) / 64.f;
    } else {
        textureCoordinates.y = (vTexture.y + (vTextureOffset.y * 6.f) + float(vFace)) / 32.f;
    }

    return texture(uTexture, textureCoordinates);
}

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
    vec3 lightColor = vec3(1);
    vec3 lightPosition = vec3(1000, 1000, 1000);
    vec3 lightDirection = normalize(lightPosition - vPosition);

    vec4 textureColor = computeTextureColor();
    vec3 diffuse = vec3(computeDiffuseLighting(lightDirection, lightColor));
    vec3 ambient = vec3(0.4);

    fFragColor = vec4(
        min(1.f, diffuse.x + ambient.x),
        min(1.f, diffuse.y + ambient.y),
        min(1.f, diffuse.z + ambient.z),
        1
    ) * textureColor;
}
