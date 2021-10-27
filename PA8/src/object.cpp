
#include "object.h"

Object::Object()
{

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}



bool Object::Create(const char* modelFilePath, const char* texFilePath)
{

  //=======================MODEL LOADING====================
  ObjFilePath = modelFilePath;
  textureFilePath = texFilePath;

  //Assimp importer:
  unsigned int index;
  aiMesh* mesh;
  aiVector3D aiUV;
  aiVector3D aiVector;
  Assimp::Importer importer;

  const aiScene *Scene = importer.ReadFile( ObjFilePath.c_str(), aiProcess_Triangulate);
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

  //=============TEXTURE LOADING===============================================


  Magick::Image* tex= new Magick::Image(textureFilePath.c_str());
  Magick::Blob m_blob;
  tex->write(&m_blob,"RGBA");

  //initialze textures
  glGenTextures(1, &Texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->columns(), tex->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return true;
}


void Object::Update(glm::mat4 PhysicsMatrix)
{
  model = PhysicsMatrix; // pass in the mat4 created by bullet
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

