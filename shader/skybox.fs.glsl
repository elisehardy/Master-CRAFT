#{ { HEADER } }

in vec3 vPosition;
in vec2 vTexture;
flat in int vFace;

uniform sampler2D uTexture;

out vec3 fFragColor;


/**
 * Compute the color of the fragment according to uTexture.
 *
 * @param fragTexPosition Texture's coordinate of the fragment.
 * @param fragType Type of the block, at most only the first 4 bits must be present.
 * @param verticalOffset Current vertical offset, use by certain animated texture.
 *
 * @return The computed color.
 */
vec3 computeTextureColor() {
    vec2 textureCoordinates = vec2(fragTexPosition.x, (fragTexPosition.y + float(vFace))/ 6.);
    return texture(uTexture, textureCoordinates).xyz;
}



void main() {
    vec3 lightColor = vec3(1);
    vec3 lightPosition = vec3(1000, 1000, 1000);
    vec3 lightDirection = normalize(lightPosition - vPosition);

    vec3 textureColor = computeTextureColor(vTexture, vType, uVerticalOffset);
    vec3 diffuse = computeDiffuseLighting(vNormal, lightDirection, lightColor);
    vec3 ambient = vec3(0.4);

    fFragColor = (diffuse + ambient) * textureColor;
}
