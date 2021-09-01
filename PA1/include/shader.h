#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "string.h"

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize(std::string VertexName_S, std::string FragName_S);
    void Enable();
    bool AddShader(GLenum ShaderType);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
