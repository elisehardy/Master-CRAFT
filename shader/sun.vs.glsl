#{{ HEADER }}

layout (location = 0) in vec3 aPosition;

uniform mat4 uMVP;

out vec3 vFragColor;


void main(){
    vFragColor = vec3(1);
    gl_Position = uMVP * vec4(aPosition, 1);
}

