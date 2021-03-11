// Phong shader for simple game lighting
#version 410

in vec4 vPosition;
in vec3 vNormal;

uniform vec3 Ka; // The ambient color of the model's material
uniform vec3 Kd; // The diffuse color of the model's material
uniform vec3 Ks; // The specular color of the model's material
uniform float Ns; // The specular power of the mode's material;

// Ambient coor of the light
uniform vec3 AmbientColor; 
// Color of the light
uniform vec3 LightColor; 
uniform vec3 LightingDirection;

uniform vec3 CameraPosition; // Position of the camera for specular  calculations

out vec4 FragColor;

void main(){
    // Make sure the normal and the light directions have been normalized
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightingDirection);

    // Now we can calculate the lambert term, negative the light direction
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate the view vector and the relfection vector
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);

    // Determine the value of thesApecular term
    float specularTerm = pow(max(0, dot(R,V)), 32);

    // Determine the value of the ambient
    vec3 ambient = AmbientColor * Ka;
    // Determine the value of diffuse 
    vec3 diffuse = LightColor  * Kd * lambertTerm; 
    // Determine the value of the specular
    vec3 specular = LightColor * Ks * specularTerm;

    // Output the final color
    FragColor = vec4(ambient + diffuse + specular, 1);;
}