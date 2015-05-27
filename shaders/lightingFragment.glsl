#version 410 core

in vec3 passPosition;
in vec3 passColor;
in vec3 passNormal;
in vec3 passTexCoords;
out vec4 outColor;

uniform vec3 cameraPosition;
uniform bool lightingEnabled;
uniform float shininess;

struct Light
{
    int type; // 0 = point, 1 = directional, 2 = spotlight
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float range; // 0 = infinite range
    float spread;
    bool enabled;
};

uniform Light lights[NUM_LIGHTS];

void main()
{
    //lights[0].enabled = true;
    //lights[0].position = vec3(0.0, 30.0, 0.0);
    ////lights[0].position = cameraPosition;
    //lights[0].ambient = vec3(0.3, 0.3, 0.3);
    //lights[0].diffuse = vec3(0.6, 0.6, 0.6);
    //lights[0].specular = vec3(0.4, 0.4, 0.4);
    //lights[0].range = 300;
    
    //vec3 ambient = vec3(0.0, 0.0, 0.0);
    //vec3 diffuse = vec3(0.0, 0.0, 0.0);
    //vec3 specular = vec3(0.0, 0.0, 0.0);
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    vec3 color = passColor;
    
    if (lightingEnabled) {
        for (int i = 0; i < NUM_LIGHTS; i++)
            if (lights[i].enabled)
            {
                vec3 surfaceToLight;
                if (lights[i].type == 1)
                    surfaceToLight = normalize(-lights[i].direction);
                else
                    surfaceToLight = normalize(lights[i].position - passPosition);
                vec3 surfaceToCamera = normalize(cameraPosition - passPosition);
                vec3 lightReflection = reflect(-surfaceToLight, passNormal);
                
                float k = 1;
                if (lights[i].range > 0)
                    k = pow(max(0.0, 1 - distance(lights[i].position, passPosition) / lights[i].range), 2);
                if (lights[i].type == 1)
                    k = 1;
                else if (lights[i].type == 2) {
                    float cosTheta = dot(normalize(lights[i].direction), surfaceToLight);
                    k *= max(0.0, sqrt(cosTheta - cos(radians(lights[i].spread))));
                }
                
                // Ambient lighting
                ambient += lights[i].ambient * k;
                
                // Diffuse lighting
                diffuse += lights[i].diffuse * max(0.0, dot(passNormal, surfaceToLight)) * k;
                
                // Specular lighting
                //if (dot(passNormal, surfaceToLight) > 0)
                if (shininess > 0)
                    specular += lights[i].specular * pow(max(0.0, dot(surfaceToCamera, lightReflection)), shininess) * k;
                
                //ambient = vec3((dot(passNormal, surfaceToLight)));
                //diffuse = vec3((dot(passNormal, surfaceToLight)));
                //specular = vec3((dot(passNormal, surfaceToLight)));
                //ambient = vec3(passNormal[0], 0, passNormal[2]);
                //diffuse = vec3(passNormal[0], 0, passNormal[2]);
                //specular = vec3(passNormal[0], 0, passNormal[2]);
                //ambient = passNormal;
                //diffuse = passNormal;
                //specular = passNormal;
                
            }
        color = color * (ambient + diffuse) + specular;
    }
    outColor = vec4(color, 1.0);
}
