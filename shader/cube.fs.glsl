#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;
flat in int vAlpha;
flat in int vType;
flat in int vFace;

uniform vec3 uCamera;
uniform vec3 uLightColor;
uniform vec3 uLightPosition;
uniform int uVerticalOffset;
uniform sampler2D uTexture;

out vec4 fFragColor;


/**
 * Compute the color of the fragment according to uTexture.
 *
 * @param fragTexPosition Texture's coordinate of the fragment.
 * @param fragType Type of the block, at most only the first 4 bits must be present.
 * @param verticalOffset Current vertical offset, use by certain animated texture.
 *
 * @return The computed color.
 */
vec4 computeTextureColor(vec2 fragTexPosition, int fragType, int verticalOffset) {
    vec2 textureCoordinates = vec2((fragTexPosition.x + float(fragType)) / 13., 0);

    if (vAlpha != 0) {
        textureCoordinates.y = (fragTexPosition.y + float(verticalOffset)) / 64.;
    } else {
        textureCoordinates.y = (fragTexPosition.y + float(vFace)) / 32.;
    }

    return texture(uTexture, textureCoordinates);
}

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
    vec3 lightPosition = vec3(1000, 1000, 1000);
    vec3 lightDirection = normalize(lightPosition - vPosition);

    vec4 textureColor = computeTextureColor(vTexture, vType, uVerticalOffset);
    vec3 diffuse = vec3(computeDiffuseLighting(vNormal, lightDirection, lightColor));
    vec3 ambient = vec3(0.4);

    fFragColor = vec4(diffuse + ambient, 1) * textureColor;
}
