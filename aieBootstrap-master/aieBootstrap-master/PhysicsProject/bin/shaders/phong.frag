// A simple shader for flat colors
#version 410

in vec4 vPosition;
in vec3 vNormal;

uniform vec3 Ka;  //The lambient color of the model's material
uniform vec3 Kd; //the diffuse color of the model's material
uniform vec3 Ks; //the specular color of the model's material
uniform float Ns;//the specular power of the model's material


uniform vec3 AmbientColor; // Ambient color of the light
uniform vec3 LightColor; // color of the light
uniform vec3 LightDirection; 

const int MAX_LIGHTS =4;
uniform int numLights;
uniform vec3 PointLightColor[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform vec3 CameraPosition; // Position of the cam viewport for specular calcualtions

out vec4 FragColor;

vec3 diffuse(vec3 direction, vec3 color, vec3 normal)
{
    return color * max(0,dot(normal,-direction));
}

vec3 specular(vec3 direction, vec3 color, vec3 normal, vec3 view)
{
    vec3 R = reflect(direction,normal);

    //calculate the specular term
    float specTerm = pow(max(0,dot(R,view)),Ns);
    return specTerm * color;
}

void main()
 {
    //make sure the normal and the light directions have been normalized
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    //now we can calculate the lambert term, negative the light direction
    //float lambertTerm = max(0,min(1,dot(N,-L)));

    //calculate the diffuse lighting from the sunlight 
    vec3 diffuseTotal = diffuse(L,LightColor, N);

    //Calculate the view vector ad the reflection vector
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L,N);

     vec3 specularTotal = specular(L,LightColor,N,V);

    //determine the value of the specular term
        for (int i = 0; i < numLights; i++)
    {
        vec3 direction = vPosition.xyz - PointLightPosition[i];
        float distance = length(direction);
        direction = direction / distance;

        //get the light intensity with the inverse square law
        vec3 color = PointLightColor[i] / (distance * distance);

        diffuseTotal += diffuse(direction,color,N);
        specularTotal += specular(direction,color,N,V);
    }

    //Determine the value of the ambient
    vec3 ambient = AmbientColor * Ka;
    //Determine the value of the diffuse
    vec3 diffuse =  Kd * diffuseTotal;
    //Determine the value of the specular
    vec3 specular =  Ks * specularTotal;

    //output the final color
    FragColor = vec4(ambient + diffuse + specular, 1);
}