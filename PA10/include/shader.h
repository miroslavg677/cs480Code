#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <fstream>
using namespace std;

#include "graphics_headers.h"

// NOTE: I repurposed this to act as an external shader loader
// I initially tried writing a whole new class, but I realized I'm lazy
class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    int loadShader(char* filename);
    bool AddShader(GLenum ShaderType, char* filename);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;
    GLchar* shaderSource;   
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */