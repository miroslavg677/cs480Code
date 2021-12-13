#include "shader.h"

// NOTE: This class has been repurposed to act as an external shader loader
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

bool Shader::Initialize()
{
  m_shaderProg = glCreateProgram();

  if (m_shaderProg == 0) 
  {
    std::cerr << "Error creating shader program\n";
    return false;
  }

  return true;
}

    // getShaderFileLength: Returns the length of the file.
unsigned long getShaderFileLength(ifstream& file) {
    if(file) {
        file.seekg(0, ios::end);                // Jump to the end of the file
        unsigned long length = file.tellg();    // Set the current position to the 'length' variable
        file.seekg(0, ios::beg);                // Jump back to the beginning

        return length;
    }
    else return 0;
}

    // loadShader: Converts the text file contents into a usable program
int Shader::loadShader(char* filename) {
    std::ifstream file;                  //open the file, check for initialization errors
    file.open(filename, ios::in);
    if(!file) return -1;            // Error: File Not Found

    unsigned long length = getShaderFileLength(file);
    if (length == 0) return -2;     // Error: File is Empty

    shaderSource = (GLchar*) new char[length+1];

    shaderSource[length] = 0;   // 0 will be our end value

    unsigned int i = 0;
    while(file.good()) {
        shaderSource[i] = file.get();
        if (!file.eof()) 
            i++;
    }

    shaderSource[i] = 0;

    file.close();

    return 0;
}

    // Use this method to add shaders to the program. When finished - call finalize()
    // Creates a shader using the program written in loadShader
bool Shader::AddShader(GLenum ShaderType, char* filename)   //GLenum ShaderType
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) 
    {
        std::cerr << "Error creating shader type " << ShaderType << std::endl;
        return false;
    }

    // Save the shader object - will be deleted in the destructor
    m_shaderObjList.push_back(ShaderObj);

    int error = loadShader(filename);
	if (error == -1) {
		cout << "Error: Shader File Not Found" << endl;}
	else if (error == -2) {
		cout << "Error: Shader File is empty" << endl;}

    GLint Lengths[1] = { (GLint)strlen((const char*)shaderSource) };

    glShaderSource(ShaderObj, 1, (const GLchar**)&shaderSource, Lengths);

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
