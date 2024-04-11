#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat3 u_NormalWorld;

void main()
{
	FragPos = vec3(u_Model * vec4(position, 1.0));
	Normal = u_NormalWorld * normal;

	gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_LightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_LightPos - FragPos);
	float diffuseComponent = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseComponent * u_LightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = specularStrength * specularComponent * u_LightColor;

	vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
	FragColor = vec4(result, 1.0);
}