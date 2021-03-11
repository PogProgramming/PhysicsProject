// a simple shader for flat colours
#version 410

out vec4 FragColor;
in vec4 simpleFlatColor;

void main(){
    FragColor = simpleFlatColor;
}