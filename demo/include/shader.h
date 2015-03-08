#ifndef SHADER_DOT_H
#define SHADER_DOT_H
#include <glew.h>
#include <GLFW\glfw3.h>
#include <string>

namespace gofxengine
{
	std::string GL_type_to_string(GLenum type);
	bool Is_valid(GLuint prog);
	void Print_program_and_shader_info_log(GLuint prog);
	GLuint LoadShader(const std::string& fileName, GLuint shaderType);
	GLuint CreateShaderProgram(GLuint vertShader, GLuint fragShader);
}
#endif