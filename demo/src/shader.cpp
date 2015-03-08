#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>

#include "string_convert.h"

using namespace std;

namespace gfxengine
{
	string GL_type_to_string(GLenum type)
	{
		switch (type)
		{
		case GL_BOOL:
			return "bool";
		case GL_INT:
			return "int";
		case GL_FLOAT:
			return "float";
		case GL_FLOAT_VEC2:
			return "vec2";
		case GL_FLOAT_VEC3:
			return "vec3";
		case GL_FLOAT_VEC4:
			return "vec4";
		case GL_FLOAT_MAT2:
			return "mat2";
		case GL_FLOAT_MAT3:
			return "mat3";
		case GL_FLOAT_MAT4:
			return "mat4";
		case GL_SAMPLER_2D:
			return "sampler2D";
		case GL_SAMPLER_3D:
			return "sampler3D";
		case GL_SAMPLER_CUBE:
			return "samplerCube";
		case GL_SAMPLER_2D_SHADOW:
			return "sampler2DShadow";
		default: break;
		}

		return "other";
	}

	void _print_shader_info_log(GLuint shader_index) 
	{
		int max_length = 2048;
		int actual_length = 0;
		char log[2048];
		glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
		cout << "shader info log for GL index " << shader_index << ":" << endl << log << endl;
	}

	void _print_program_info_log(GLuint prog)
	{
		int max_length = 2048;
		int actual_length = 0;
		char log[2048];
		glGetProgramInfoLog(prog, max_length, &actual_length, log);
		cout << "program info log for GL index " << prog << ":" << endl << log;
	}

	bool Is_valid(GLuint prog) 
	{
		glValidateProgram(prog);
		int params = -1;
		glGetProgramiv(prog, GL_VALIDATE_STATUS, &params);
		cout << "program " << prog << " GL_VALIDATE_STATUS = " << params << endl;
		
		if (GL_TRUE != params)
		{
			_print_program_info_log(prog);
			return false;
		}
		
		return true;
	}

	void Print_program_and_shader_info_log(GLuint prog)
	{
		cout << "--------------------" << endl << "shader program " << prog << " info:" << endl;
		int params = -1;
		glGetProgramiv(prog, GL_LINK_STATUS, &params);
		cout << "GL_LINK_STATUS = " << params << endl;

		glGetProgramiv(prog, GL_ATTACHED_SHADERS, &params);
		cout << "GL_ATTACHED_SHADERS = " << params << endl;

		glGetProgramiv(prog, GL_ACTIVE_ATTRIBUTES, &params);
		cout << "GL_ACTIVE_ATTRIBUTES = " << params << endl;

		for (int i = 0; i < params; i++) 
		{
			char name[64];
			int max_length = 64;
			int actual_length = 0;
			int size = 0;
			GLenum type;

			glGetActiveAttrib(prog, i, max_length, &actual_length, &size, &type, name);

			if (size > 1)
			{
				string nameString(name);

				for (int j = 0; j < size; j++) 
				{
					string long_name = nameString + "[" + gfxengine::cvt_to_string(j) + "]";
					int location = glGetAttribLocation(prog, long_name.c_str());
					cout << "  " << i << ") type:" << GL_type_to_string(type) << " name:" << name << " location:" << location << endl;
				}
			}
			else
			{
				int location = glGetAttribLocation(prog, name);
				cout << "  " << i << ") type:" << GL_type_to_string(type) << "name:" << name << " location : " << location << endl;
			}
		}

		glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, &params);
		printf("GL_ACTIVE_UNIFORMS = %i\n", params);
		for (int i = 0; i < params; i++) 
		{
			char name[64];
			int max_length = 64;
			int actual_length = 0;
			int size = 0;
			GLenum type;

			glGetActiveUniform(prog, i, max_length, &actual_length, &size, &type, name);

			if (size > 1)
			{
				string nameString(name);

				for (int j = 0; j < size; j++)
				{
					string long_name = nameString + "[" + cvt_to_string(j) + "]";
					int location = glGetUniformLocation(prog, long_name.c_str());
					cout << "  " << i << ") type:" << GL_type_to_string(type) << " name:" << name << " location:" << location << endl;
				}
			}
			else 
			{
				int location = glGetUniformLocation(prog, name);
				printf("  %i) type:%s name:%s location:%i\n",
					i, GL_type_to_string(type).c_str(), name, location);
			}
		}

		_print_program_info_log(prog);
	}

	GLuint LoadShader(const std::string& fileName, GLuint shaderType)
	{
		GLuint shader = 0;
		std::string line;
		std::string shaderText = "";
		std::ifstream shaderStream(fileName);

		if (!shaderStream.is_open())
		{
			std::cout << "Unable to open shader file: " << fileName << std::endl;
			return shader;
		}

		while (std::getline(shaderStream, line))
		{
			cout << line << endl;
			shaderText += line + "\n";
		}

		cout << endl;

		shaderStream.close();

		const GLchar* const shaderSource = shaderText.c_str();

		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		// check for compile errors
		int params = -1;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
		if (GL_TRUE != params) {
			cerr << "ERROR: GL shader index " << shader << " did not compile" << endl;
			_print_shader_info_log(shader);
			return false; // or exit or something
		}

		return shader;
	}

	GLuint CreateShaderProgram(GLuint vertShader, GLuint fragShader)
	{
		GLuint prog = glCreateProgram();
		glAttachShader(prog, vertShader);
		glAttachShader(prog, fragShader);

		/*glBindAttribLocation(prog, 0, "vertex_position");
		glBindAttribLocation(prog, 1, "vertex_color");*/

		glLinkProgram(prog);

		int params = -1;
		glGetProgramiv(prog, GL_LINK_STATUS, &params);

		if (params != GL_TRUE)
		{
			cerr << "ERROR: could not link shader programme GL index " << prog << endl;
			_print_program_info_log(prog);
			return false;
		}

		return prog;
	}
}