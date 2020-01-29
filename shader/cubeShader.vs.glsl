#{{ HEADER }}

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in int aType;

uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat4 uNormal;
uniform vec3 uChunkPosition;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexture;
flat out int vType;


void main(){
    vec4 vertexPosition = vec4(aPosition + uChunkPosition, 1);

    vPosition = vec3(uMV * vertexPosition);
    vNormal = vec3(uNormal * vec4(aNormal, 0));
    vTexture = aTexture;
    vType = aType;

    gl_Position = uMVP * vertexPosition;
}

