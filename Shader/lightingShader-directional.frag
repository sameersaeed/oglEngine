#version 330 core

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
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
    vec3 norm     = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    
    vec3 viewDir    = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient   * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse   * diff * vec3(texture(material.diffuse, TexCoords));  
    vec3 specular = light.specular  * spec * vec3(texture(material.specular, TexCoords));  
    
    vec3 emission;
    
    // keeping emissive texture within borders of container
    if (texture(material.specular, TexCoords).rgb == vec3(0.0f))    
        emission = vec3(texture(material.emission, TexCoords));
    
    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}