#{{ HEADER }}

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTexture;
//uniform vec3 uKd;
//uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;


vec3 blinnPhong(vec3 position_vs, vec3 normal_vs){
    vec3 w_zero = normalize(-position_vs);
    vec3 w_i = normalize(uLightDir_vs);
    vec3 halfVector = (w_zero + w_i) / 2.0;

    return uLightIntensity * (texture(uTexture, vTexCoords).xyz * (dot(w_i, normal_vs)) + vec3(1.0, 1.0, 1.0) * (pow(dot(halfVector, normal_vs), uShininess)));
}

void main() {
    fFragColor = blinnPhong(vPosition, normalize(vNormal));
}
