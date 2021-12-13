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
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class Object
{
	public:
		Object();
		~Object();
		void Update(glm::mat4 systemModel, btVector3 PhysicsPos);;
		void SetAngle(bool, float);
		void Render();
		glm::vec4 getDiffuse();
		glm::vec4 getSpecular();
		float getShine();

		bool Create(const char*);

		// Getters
		glm::mat4 GetModel();
		bool isGun = false;
		float angle;
		bool isEnemy=false;

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
		std::string textureName;
};

#endif 
