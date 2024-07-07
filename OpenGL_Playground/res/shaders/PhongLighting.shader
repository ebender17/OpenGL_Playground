#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 v_FragPos;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_ProjectionView;
uniform mat3 u_NormalWorld;

void main()
{
	v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
	v_Normal = u_NormalWorld * a_Normal;

	gl_Position = u_ProjectionView * vec4(v_FragPos, 1.0);
}


#shader fragment
#version 450 core

out vec4 o_FragColor;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform Light u_Light;

void main()
{
	vec3 ambient = u_Light.ambient * u_Material.ambient;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPos);
	float diffuseComponent = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * (diffuseComponent * u_Material.diffuse);

	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * (specularComponent * u_Material.specular);

	vec3 result = ambient + diffuse + specular;
	o_FragColor = vec4(result, 1.0);
}