#{{ HEADER }}

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in int aData;

uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat4 uNormal;
uniform vec3 uChunkPosition;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexture;
flat out int vAnimated;
flat out int vType;
flat out int vFace;


// Use to extract the bits 0b0000xxxx of aData, representing the type of the cube.
const int TYPE = 15;
// Use to extract the bits 0b0xxx0000 of aData, representing the current face of the cube.
const int FACE = 112;
// Use to extract the bits 0bx0000000 of aData, telling if the cube is animated.
const int ANIMATED = 128;

void main(){
    vec4 vertexPosition = vec4(aPosition + uChunkPosition, 1);

    vPosition = vec3(uMV * vertexPosition);
    vNormal = vec3(uNormal * vec4(aNormal, 0));
    vTexture = aTexture;
    vAnimated = (aData & ANIMATED) >> 7;
    vFace = (aData & FACE) >> 4;
    vType = aData & TYPE;

    gl_Position = uMVP * vertexPosition;
}

