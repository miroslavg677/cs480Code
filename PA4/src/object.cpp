#include "object.h"




Object::Object(std::string MeshName_O) // Get the OBJ file name 
{  
  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */
  
  /*
  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
    {{-1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
    {{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };
  */
  LoadOBJ_File(MeshName_O, Vertices, Indices); // Load in the OBJ file 


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

//This function parses the OBJ file and loads in the vertices and indices
bool Object::LoadOBJ_File(std::string filename, std::vector<Vertex> &Vertices, std::vector<unsigned int> &Indices)
  {
    bool NoUVs; // Used to load in OBJs without UVs and Normals
    std::vector<Vertex> Temp_Vertices;      // Used to store the verices temporarily
    std::vector<unsigned int> Temp_Indices; // Used to store the indices temporarilt

    std::string fullpath = "../Meshes/" + filename; // Get the whole relative file path
    const char * file_path = fullpath.c_str(); // Convert to a c string
    FILE * file = fopen(file_path, "r"); // open the OBJ file
    if(file == NULL)
    {
      std::cerr << "Error cannot open OBJ file" << std::endl;
      return false;
    }

    while(true)
    {
    //Read the file line by line:
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break;

    else
      {
        // Handle the vertices headers
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
          glm::vec3 vertex;
          fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
          Temp_Vertices.push_back({{vertex.x, vertex.y, vertex.z}, {1.0f, 0.72765f, 0.221276f}});

        }

        //Handle the faces 
        //If NoUVs is false the OBJ file has normals and UVs baked in
        else if (( strcmp( lineHeader, "f" ) == 0 ) && !NoUVs)
        {
          std::string vertex1, vertex2, vertex3;
          unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
          int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                                                      &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
                                                      &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
                                                      &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                                                      //Indices        //UVs        //Normals 
                                                      //We don't do anything yet with the UVs and Normals but we still need to read them in
          Temp_Indices.push_back(vertexIndex[0]);
          Temp_Indices.push_back(vertexIndex[1]);
          Temp_Indices.push_back(vertexIndex[2]);
          

            if(matches != 9)
            {
              NoUVs = true;
              rewind(file);
              //Either the OBJ file has no UVs and Normals 
              //Or it's incomatible either way reset and set the flag to true.
            }
          }
          //Attempt to read the file again this time without Normals or UVs
          else if (( strcmp( lineHeader, "f" ) == 0 ) && NoUVs)
          {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d %d %d\n", 
                                                      &vertexIndex[0], 
                                                      &vertexIndex[1], 
                                                      &vertexIndex[2]);
                                                      //Indices     
                                                      //No Normals or UVs this time      
            Temp_Indices.push_back(vertexIndex[0]);
            Temp_Indices.push_back(vertexIndex[1]);
            Temp_Indices.push_back(vertexIndex[2]);
            if(matches != 3)
            {
              //If the parsing fails a second time the OBJ loader cannot read the file
              //Give the user a message explaining why it may not be working
              std::cerr << "The OBJ file cannot be read" << std::endl;
              std::cerr << "Note this OBJ loader only supports:" << std::endl;
              std::cerr << "1: .obj files with no Normals or UVs backed in " << std::endl;
              std::cerr << "or" << std::endl;
              std::cerr << "2: .obj files with both Normals and UVs baked in" << std::endl;
              return false;
            }
          }
        }
      }
      //Set the vertices and indices
      Vertices = Temp_Vertices;
      Indices = Temp_Indices;

      //Print Vertices and Indices for debgging purposes
      /*
      std::cerr << "Vertices: " << std::endl;
      for(int i =0; i < Temp_Vertices.size(); i++)
      {
        std::cerr << Temp_Vertices[i].vertex[0] << ", " << Temp_Vertices[i].vertex[1] << Temp_Vertices[i].vertex[2] << std::endl;   
        
      }


      std::cerr << "Indices: " << std::endl;
      for(int i =0; i < Indices.size(); i++)
      {
        if(i % 3 == 0)
        {
          std::cerr << Temp_Indices[i] << ", " << std::endl; 
        }
        else
        {
          std::cerr << Temp_Indices[i] << ", "; 
        }
      } 
      */
    
  };

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}



void Object::Update(unsigned int dt, bool &reverse, bool &paused) // passing in the references to the bool flags
{

  
  //If R is pressed the cube reverses directions 
  //Uses the references set in engine.cpp
  if(reverse)
  {
  angle -= dt * M_PI/1000;
  }
  else
  {
    angle += dt * M_PI/1000;
  }
  
  
  
   
  

  if(paused)
  {
    // When the scene is paused the cube stops spinning in it's orbit but continues spinning about it's own y axis
    //The cube has been paused
    model = glm::rotate(glm::mat4(1.0f), (angle2), glm::vec3(0.0, 1.0, 0.0))
          * glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, 0.0f, 0.0f))
          * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
          waspaused = true;
  }

  else if(!paused && waspaused)
  {
    // Only runs for one frame 
    // Ensures that when the cube starts spinning again afeter being paused 
    // It is in the same spot as when it stopped spinning
    model = glm::rotate(glm::mat4(1.0f), (angle2), glm::vec3(0.0, 1.0, 0.0))
          * glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, 0.0f, 0.0f))
          * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
          waspaused = false;
          angle = angle2;
  }
  else
  {
    //The cube spins both about its axis and orbit
    //Normal not paused behavior
    model =( glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0))
          * glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, 0.0f, 0.0f))
          * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0)));
    
    angle2 = angle;
  }
  
  
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

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

