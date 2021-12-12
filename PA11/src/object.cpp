
#include "object.h"

Object::Object()
{

}

Object::~Object()
{
	Vertices.clear();
	Indices.clear();
}

bool Object::Create(const char* modelFilePath)
{
	//Assimp importer:
	unsigned int index;
	aiMesh* mesh;
	aiMaterial *mtl;
	aiColor4D values;
	float shine;
	std::string sTextureName;
	aiString path;

	aiVector3D aiUV;
	aiVector3D aiVector;
	Assimp::Importer importer;

	const aiScene *Scene = importer.ReadFile( modelFilePath, aiProcess_Triangulate);
	mesh = Scene->mMeshes[0];

	//Get the vertices and the indecies from the Assimp scene
	for(int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& thisFace = mesh->mFaces[i];
		for(int j = 0; j < 3; j++)
		{
			// read in the indices
			index = thisFace.mIndices[j];
			Indices.push_back(index);

			// read in the vertices
			aiVector = mesh->mVertices[thisFace.mIndices[j]];
			aiUV = mesh->mTextureCoords[0][thisFace.mIndices[j]];

			Vertex *temp = new Vertex(glm::vec3(aiVector.x, aiVector.y, aiVector.z), glm::vec2(aiUV.x, aiUV.y));
			Vertices.push_back(*temp);
		}
	}

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	//============MATERIAL DATA LOADING==========================================

	mtl = Scene->mMaterials[mesh->mMaterialIndex];

	aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &values);
	o_diffuse = {values.r, values.g, values.b, values.a};

	aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &values);
	o_specular = {values.r, values.g, values.b, values.a};

	aiGetMaterialFloat(mtl, AI_MATKEY_SHININESS, &shine);
	o_shine = shine;

	//=============TEXTURE LOADING===============================================
	
	if(mtl->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
		sTextureName = path.data;
		textureName = "textures/" + sTextureName;	//add the file location to the texture name
	}
	else
		textureName = "textures/blankTexture.jpg";

	Magick::Blob m_blob;
	Magick::Image *image;
	image = new Magick::Image(textureName);
	image->write(&m_blob, "RGBA");

	//initialze textures
	glGenTextures(1, &Texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

glm::vec4 Object::getDiffuse() {
	return o_diffuse;
}

glm::vec4 Object::getSpecular() {
	return o_specular;
}

float Object::getShine() {
	return o_shine;
}

void Object::Update(glm::mat4 PhysicsMatrix, btVector3 PhysicsPos) // Pass in a mat4 to be used for positioning the model
{

	if(isGun) // The passed in mat4 is the player's position which is tied to the camera position
	{
		glm::vec3 Position = glm::vec3(PhysicsPos.x(), PhysicsPos.y(), PhysicsPos.z());
		glm::mat4 RefMatrix = glm::translate(glm::mat4(1.0), Position);

		model =(glm::translate(RefMatrix, glm::vec3(0.0f, -0.4f, 0.0f)) // position the gun relative to the camera
		      * glm::rotate(glm::mat4(1.0f), (angle - 1.5f), glm::vec3(0.0, 1.0, 0.0))); // Rotate with the player so that the gun is always infront of the player	  
	}
	else
	{
		model = PhysicsMatrix; // pass in the mat4 created by bullet
	}
}


void Object::SetAngle(bool isA_Gun, float Angle) //Used to set the angle of the camera each frame, used to set the gun's rotation to match the player's rotation
{
	angle = Angle;
}


glm::mat4 Object::GetModel()
{
	return model;
}

void Object::Render()

{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

