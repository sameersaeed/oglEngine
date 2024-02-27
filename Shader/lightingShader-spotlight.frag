#version 330 core

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    vec3  position;
    vec3  direction;
    float cutOff;
    float outerCutOff;
};

struct Material {
    sampler2D   diffuse;
    sampler2D   specular;
    sampler2D   emission;
    float       shininess;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

in vec2 TexCoords;
in vec3 FragPos;  
in vec3 Normal;  

out vec4 FragColor;

void main()
{
    vec3 lightDir = normalize(-light.direction);
    float theta = dot(lightDir, normalize(-light.direction));

    if(theta > light.cutOff) // within cutoff range -  calculate lighting
    {
        vec3 norm     = normalize(Normal);
        vec3 viewDir    = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm); 

        float diff = max(dot(norm, lightDir), 0.0);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    
        vec3 emission;
    
        // keeping emissive texture within borders of container
        if (texture(material.specular, TexCoords).rgb == vec3(0.0f))    
            emission = vec3(texture(material.emission, TexCoords));
    
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        
        float theta = dot(lightDir, normalize(-light.direction)); 
        float epsilon = (light.cutOff - light.outerCutOff);
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        diffuse  *= attenuation;
        specular *= attenuation;   

        FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
    }
    else  // outside cutoff range - only use ambient lighting 
        FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
}