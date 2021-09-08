#include "shader.h"


std::string VertexNameFinal;
std::string FragNameFinal;

Shader::Shader()
{
  m_shaderProg = 0;
}

Shader::~Shader()
{
  for (std::vector<GLuint>::iterator it = m_shaderObjList.begin() ; it != m_shaderObjList.end() ; it++)
  {
    glDeleteShader(*it);
  }

  if (m_shaderProg != 0)
  {
    glDeleteProgram(m_shaderProg);
    m_shaderProg = 0;
  }
}

bool Shader::Initialize(std::string FragName_S, std::string VertexName_S) // Recieve the file names from the graphics 
{
  //Store the vertex and frag shader file names
  VertexNameFinal = VertexName_S;
  FragNameFinal = FragName_S;
  
  m_shaderProg = glCreateProgram();

  if (m_shaderProg == 0) 
  {
    std::cerr << "Error creating shader program\n";
    return false;
  }

  return true;
}

// Use this method to add shaders to the program. When finished - call finalize()
bool Shader::AddShader(GLenum ShaderType)
{
  std::string s;
  std::string line; //Stores the current line being read
  std::stringstream shader; // stores the whole shader string
  std::string shaderfilepath = "/home/miro/cs480Georgiev/PA2/Shaders/";

  if(ShaderType == GL_VERTEX_SHADER)
  {
    //Read in the Vertex Shader
    
    std::string shaderFilePathFull = shaderfilepath + VertexNameFinal;
    std::ifstream ShaderInput(shaderFilePathFull);
    while(getline(ShaderInput, line))
    {
      //Parse the shader making sure to only put it one new line
      if(line.find("#version 330") != std::string::npos)
      {
          shader << line << '\n';
      }
      else
      {
          shader << line;
      }
    }
    //Finally set the prebuilt shader string variable
    //to the new string and add one more new line
    s = shader.str();
    shader << ' ' << '\n';
  }

  //Same process for the frag shader as for the vertex shader
  else if(ShaderType == GL_FRAGMENT_SHADER)
  {
    
    std::string shaderFilePathFull = shaderfilepath + FragNameFinal;
    std::ifstream ShaderInput(shaderFilePathFull);
    while(getline(ShaderInput, line))
    {
      if(line.find("#version 330") != std::string::npos)
      {
          shader << line << '\n';
      }
      
      else
      {
        shader << line;
      }
    }
    shader << ' ' << '\n';
    s =shader.str();
  }
 
  /*
  
  if(ShaderType == GL_VERTEX_SHADER)
  {
    s = "#version 330\n \
          \
          layout (location = 0) in vec3 v_position; \
          layout (location = 1) in vec3 v_color; \
          \
          smooth out vec3 color; \
          \
          uniform mat4 projectionMatrix; \
          uniform mat4 viewMatrix; \
          uniform mat4 modelMatrix; \
          \
          void main(void) \
          { \
            vec4 v = vec4(v_position, 1.0); \
            gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v; \
            color = v_color; \
          } \
          ";
  }
  */
  /*
  if(ShaderType == GL_FRAGMENT_SHADER)
  {
    s = "#version 330\n \
          \
          smooth in vec3 color; \
          \
          out vec4 frag_color; \
          \
          void main(void) \
          { \
             frag_color = vec4(color.rgb, 1.0); \
          } \
          ";
  }
  */


 

  GLuint ShaderObj = glCreateShader(ShaderType);

  if (ShaderObj == 0) 
  {
    std::cerr << "Error creating shader type " << ShaderType << std::endl;
    return false;
  }

  // Save the shader object - will be deleted in the destructor
  m_shaderObjList.push_back(ShaderObj);

  const GLchar* p[1];
  p[0] = s.c_str();
  GLint Lengths[1] = { (GLint)s.size() };

  glShaderSource(ShaderObj, 1, p, Lengths);

  glCompileShader(ShaderObj);

  GLint success;
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

  if (!success) 
  {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    std::cerr << "Error compiling: " << InfoLog << std::endl;
    return false;
  }

  glAttachShader(m_shaderProg, ShaderObj);

  return true;
}


// After all the shaders have been added to the program call this function
// to link and validate the program.
bool Shader::Finalize()
{
  GLint Success = 0;
  GLchar ErrorLog[1024] = { 0 };

  glLinkProgram(m_shaderProg);

  glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
  if (Success == 0)
  {
    glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
    std::cerr << "Error linking shader program: " << ErrorLog << std::endl;
    return false;
  }

  glValidateProgram(m_shaderProg);
  glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);
  if (!Success)
  {
    glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
    std::cerr << "Invalid shader program: " << ErrorLog << std::endl;
    return false;
  }

  // Delete the intermediate shader objects that have been added to the program
  for (std::vector<GLuint>::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++)
  {
    glDeleteShader(*it);
  }

  m_shaderObjList.clear();

  return true;
}


void Shader::Enable()
{
    glUseProgram(m_shaderProg);
}


GLint Shader::GetUniformLocation(const char* pUniformName)
{
    GLuint Location = glGetUniformLocation(m_shaderProg, pUniformName);

    if (Location == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
    }

    return Location;
}
