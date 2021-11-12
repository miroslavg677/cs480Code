#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <cstdio>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>

class Object
{
	public:
		Object();
		~Object();
		void Update(glm::mat4 systemModel);
		void Render();
		glm::vec4 getDiffuse();
		glm::vec4 getSpecular();
		float getShine();

		bool Create(const char* modelFilePath, const char* texFilePath);

		// Getters
		glm::mat4 GetModel();

	private:
		glm::mat4 model;
		glm::vec4 o_diffuse;
		glm::vec4 o_specular;
		float o_shine;
		
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		GLuint VB;
		GLuint IB;

		//Texture
		GLuint Texture;

		std::string configFilePath;
		std::string ObjFilePath;
		std::string textureFilePath;
};

#endif 
