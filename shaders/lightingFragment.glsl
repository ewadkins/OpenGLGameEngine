#version 410 core

in vec3 passPosition;
in vec3 passColor;
in vec3 passNormal;
in vec3 passTexCoords;
out vec4 outColor;

uniform vec3 cameraPosition;
uniform bool lightingEnabled;
uniform float shininess;

uniform sampler2D textures[NUM_TEXTURES];

struct Light
{
    int type; // 0 = point, 1 = directional, 2 = spotlight
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float range; // 0 = infinite range
    float beamAngle;
    bool enabled;
};

uniform Light lights[NUM_LIGHTS];

void main()
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    vec3 color = passColor;
    
    if (lightingEnabled) {
        for (int i = 0; i < lights.length(); i++)
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
                    k *= max(0.0, sqrt(cosTheta - cos(radians(lights[i].beamAngle))));
                }
                
                // Ambient lighting
                ambient += lights[i].ambient * k;
                
                // Diffuse lighting
                diffuse += lights[i].diffuse * max(0.0, dot(passNormal, surfaceToLight)) * k;
                
                // Specular lighting
                if (shininess > 0)
                    specular += lights[i].specular * pow(max(0.0, dot(surfaceToCamera, lightReflection)), shininess) * k;
            }
        color = color * (ambient + diffuse) + specular; // adding specular directly to surface color allows for glare
    }
    
    
    int texIndex = int(passTexCoords.z + (passTexCoords.z >= 0 ? 0.5 : -0.5));
    if (texIndex != 0) {
        if (texIndex == -1)
            texIndex = 0;
        color = color * texture(textures[texIndex], passTexCoords.st).rgb;
    }
    
    outColor = vec4(color, 1.0);
}
