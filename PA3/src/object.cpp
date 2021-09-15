#include "object.h"


Object::Object()
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

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
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

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}



void Object::Update(unsigned int dt, 
                    bool &reverse, 
                    bool &paused, 
                    glm::mat4 PosReferece, 
                    std::string Type, 
                    bool &MoonScaleUp, 
                    bool &MoonScaleDown) // passing in the references to the bool flags and references
{
  
  // If the object is a Planet the code is the same as PA2
  if(Type == "Planet")
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
  ModelRef = model;
  }


  //If the Object is a moon it needs diffrent transforms
  if(Type == "Moon")
  {
    //HAndles scaling the moon up
    if(MoonScaleUp)
    {
      scaleammount += 0.05f;
      MoonScaleUp = false;
      std::cerr << "Moon scaled up" << std::endl;
    }

    //Handles scaling the moon down
    if(MoonScaleDown && (scaleammount >= 0.0f)) //The moon will not scale bellow 0.0f which avoids undesired behavior
    {
      scaleammount -= 0.05f;
      MoonScaleDown = false;
      std::cerr << "Moon scaled down" << std::endl;
    }

    //the angle determines how fast the moon rotates
    moon_angle += dt * M_PI/2000;

    // Orbit the planet using the peent objects's model matrix
    //Also scales the object up and down
    model =(glm::translate(PosReferece, glm::vec3(4.0f, 0.0f, 0.0f))
          * glm::rotate(glm::mat4(1.0f), (moon_angle), glm::vec3(0.0, 1.0, 0.0))
          * glm::scale(glm::mat4(1.0f), glm::vec3(scaleammount, scaleammount, scaleammount))); 
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

