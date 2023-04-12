#version 330 core
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor; 
void main()
{
    vec3 lightColor = vec3(1.0,1.0,1.0);

    //Calculate Ambient
    float ambientStrength = 0.4f;
    vec3 ambient = ambientStrength * lightColor;
    
    //Calculate Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //Calculate specular
    float specularStrength = 2;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * ourColor;
    FragColor = vec4(result, 1.0);

}