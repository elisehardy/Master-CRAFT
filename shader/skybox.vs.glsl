#{{ HEADER }}

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in int aFace;


in vec3 vPosition;
in vec2 vTexture;
flat out int vFace;

void main(){
    vPosition = vec3(uMV * vertexPosition);
    vTexture = aTexture;
    vFace = aFace;

    gl_Position = uMVP * vertexPosition;
}

