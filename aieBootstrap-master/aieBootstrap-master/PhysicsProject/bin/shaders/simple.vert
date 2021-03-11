// a simple shader
#version 410

layout(location = 0) in vec4 Position;

uniform mat4 ProjectionViewModel;
uniform vec4 MeshFlatColor;
out vec4 simpleFlatColor;

void main(){
    if(MeshFlatColor != 0){
        simpleFlatColor = MeshFlatColor;
    }
    else{
        simpleFlatColor = vec4(1, 0, 1, 1);
    }

    gl_Position = ProjectionViewModel * Position;
}