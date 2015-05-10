#version 410 core

in vec3 passPosition;
in vec3 passColor;
in vec3 passNormal;
in vec3 passTexCoords;
out vec4 outColor;

uniform vec3 cameraPosition;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float range; // range < 0 = infinite range
    bool enabled;
} lights[1];

void main()
{
    lights[0].enabled = true;
    lights[0].position = vec3(0.0, 3.0, 0.0);
    //lights[0].position = cameraPosition;
    lights[0].ambient = vec3(0.7, 0.7, 0.7);
    lights[0].diffuse = vec3(0.5, 0.5, 0.5);
    lights[0].specular = vec3(0.4, 0.4, 0.4);
    lights[0].range = 150;
    
    //vec3 ambient = vec3(0.0, 0.0, 0.0);
    //vec3 diffuse = vec3(0.0, 0.0, 0.0);
    //vec3 specular = vec3(0.0, 0.0, 0.0);
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    for (int i = 0; i < lights.length(); i++)
        if (lights[i].enabled)
        {
            float k = 1;
            if (lights[i].range > 0)
                k = pow(max(0.0, 1 - distance(lights[i].position, passPosition) / lights[i].range), 2);
            
            vec3 surfaceToLight = normalize(lights[i].position - passPosition);
            
            // Ambient lighting
            ambient += lights[i].ambient * k;
        
            // Diffuse lighting
            diffuse += lights[i].diffuse * max(0.0, dot(passNormal, surfaceToLight)) * k;
            
            // Specular lighting
            float shininess = 2;
            if (dot(passNormal, surfaceToLight) > 0)
                specular += lights[i].specular * pow(max(0.0, dot(normalize(cameraPosition - passPosition), reflect(-surfaceToLight, passNormal))), shininess) * k;
            
        }
    vec3 color = passColor * (ambient + diffuse + specular);
    outColor = vec4(color, 1.0);
}
