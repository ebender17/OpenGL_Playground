#pragma once

#include "glm/glm.hpp"

struct MaterialFlatColor
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;

	MaterialFlatColor() = default;

	MaterialFlatColor(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
		: Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
	{
	}
};

struct MaterialTextures
{
	unsigned int Diffuse;
	unsigned int Specular;
	unsigned int Emissive;
	float Shininess;

	MaterialTextures() = default;

	MaterialTextures(unsigned int diffuse, unsigned int specular, unsigned int emissive, float shininess)
		: Diffuse(diffuse), Specular(specular), Emissive(emissive), Shininess(shininess)
	{
	}
};

struct Light
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	Light() = default;

	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: Ambient(ambient), Diffuse(diffuse), Specular(specular)
	{
	}
};
