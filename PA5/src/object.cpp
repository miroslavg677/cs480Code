#include "object.h"
	//Constructor
Object::Object() {
  


  
  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

	angle = 0.0f;

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

    // getFileLength: Returns the length of the file.
unsigned long getFileLength(ifstream& file) {
    if(file) {
        file.seekg(0, ios::end);                // Jump to the end of the file
        unsigned long length = file.tellg();    // Set the current position to the 'length' variable
        file.seekg(0, ios::beg);                // Jump back to the beginning

        return length;
    }
    else return 0;
}

	// Overloaded Constructor
Object::Object(char* modelobj) {

	int error = loadOBJ(modelobj);
	//no if (error == -1) because loadOBJ handles the error message
	if (error == -2) {
		cout << "file has no meshes" << endl;
	}
	else if (error == -3) {
		cout << "mesh has either no positions or faces" << endl;
	}

	angle = 0.0f;

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec2) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

    // Deconstructor
Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

	// loadOBJ: Loads info from a .obj file to make an object
int Object::loadOBJ(char* modelobj) {
	Assimp::Importer importer;

	// Load our .obj file info to scene
	const aiScene* scene = importer.ReadFile(modelobj, aiProcess_Triangulate);

	if(!scene){
      cout<<"importer.ReadFile (" << modelobj << "):  " << importer.GetErrorString() << endl;
      return -1;
   }

	if (!scene->HasMeshes())
		return -2;

	aiMaterial *mtl;

	glm::vec3 vert_buffer;
	glm::vec3 color_buffer;

	for (int i = 0; i < scene->mNumMeshes; i++) {
		//If the .obj has multiple materials, Assimp creates a different mesh for each
		aiMesh &mesh = *scene->mMeshes[i];

		if (!mesh.HasPositions() || !mesh.HasFaces())
			return -3;
		
		// The material used is indexed in the mesh object
		mtl = scene->mMaterials[mesh.mMaterialIndex];

		aiColor4D diffuse;
		//For now, the diffuse color is all we need
		aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse);

		for (int j = 0; j < mesh.mNumVertices; j++) {
			//This could be implemented without buffers, but I don't like long horizontal code
			vert_buffer = {mesh.mVertices[j].x, mesh.mVertices[j].y, mesh.mVertices[j].z};
			color_buffer = {diffuse.r, diffuse.g, diffuse.b};

			Vertices.push_back({{vert_buffer}, {color_buffer}});
		}

		for (int j = 0; j < mesh.mNumFaces; j++) {
			aiFace face = mesh.mFaces[i];

			Indices.push_back(face.mIndices[0]);
			Indices.push_back(face.mIndices[1]);
			Indices.push_back(face.mIndices[2]);
		}
	}

	return 0;
}

    // Update: Defines how the object moves. This is where we need to define spinning and orbiting.
void Object::Update(unsigned int dt)
{
	angle += dt * M_PI/5000;

	//glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 0.0, 0.0));     // Moves the cube in the x-direction
	//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));

	//model = rotate * translate * rotate;    // Here we basically spin the cube by [angle] degrees, translate it 5 units from the origin, and rotate about the origin by [angle] degrees
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glDrawArrays(GL_TRIANGLES, 0, Vertices.size());

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

