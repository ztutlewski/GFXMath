#include "log.h"

#include <glew.h>
#include <GLFW\glfw3.h>
#include <time.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include "string_convert.h"

using namespace std;

namespace gfxengine
{
	const string GL_LOG_FILE = "gl.log";
	const string GL_ERR_FILE = "gl_err.log";

	bool RestartGLLog()
	{
		ofstream file(GL_LOG_FILE);

		if (!file.is_open())
		{
			cerr << "ERROR: could not open GL_LOG_FILE log file \"" << GL_LOG_FILE << "\" for writing" << endl;
			return false;
		}

		time_t rawTime = time(NULL);
		struct tm now;

#if defined(_MSC_VER)
		localtime_s(&now, &rawTime);
#else
		now = *localtime(&rawTime);
#endif

		file << "GL_LOG_FILE log. local time " << (now.tm_year + 1900) << '-' << (now.tm_mon + 1) << '-' << now.tm_mday
			<< " :: " << gfxengine::cvt_to_string(now.tm_hour) << ":" << gfxengine::cvt_to_string(now.tm_min) << ":" << gfxengine::cvt_to_string(now.tm_sec) << endl;

		file.close();

		return true;
	}

	bool GLLog(const string& message)
	{
		ofstream file(GL_LOG_FILE, ios_base::app);

		if (!file)
		{
			cerr << "ERROR: could not open GL_LOG_FILE \"" << GL_LOG_FILE << "\" file for appending" << endl;
			return false;
		}

		file << message << endl;
		file.close();

		return true;
	}

	bool GLLogErr(const string& message) 
	{
		ofstream file(GL_ERR_FILE, ios_base::app);

		if (!file)
		{
			cerr << "ERROR: could not open GL_LOG_FILE \"" << GL_ERR_FILE << "\" file for appending" << endl;
			return false;
		}

		file << message << endl;
		file.close();

		return true;
	}

	void LogGLParams() 
	{
		static const GLenum params[] = {
			GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
			GL_MAX_CUBE_MAP_TEXTURE_SIZE,
			GL_MAX_DRAW_BUFFERS,
			GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
			GL_MAX_TEXTURE_IMAGE_UNITS,
			GL_MAX_TEXTURE_SIZE,
			GL_MAX_VARYING_FLOATS,
			GL_MAX_VERTEX_ATTRIBS,
			GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
			GL_MAX_VERTEX_UNIFORM_COMPONENTS,
			GL_MAX_VIEWPORT_DIMS,
			GL_STEREO,
		};
		static const string names[] = {
			"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
			"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
			"GL_MAX_DRAW_BUFFERS",
			"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
			"GL_MAX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_TEXTURE_SIZE",
			"GL_MAX_VARYING_FLOATS",
			"GL_MAX_VERTEX_ATTRIBS",
			"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
			"GL_MAX_VIEWPORT_DIMS",
			"GL_STEREO",
		};
		GLLog("GL Context Params:");
		// integers - only works if the order is 0-10 integer return types
		for (int i = 0; i < 10; i++) {
			int v = 0;
			glGetIntegerv(params[i], &v);
			GLLog(names[i] + " " + gfxengine::cvt_to_string(v));
		}
		// others
		int v[2];
		v[0] = v[1] = 0;
		glGetIntegerv(params[10], v);
		GLLog(names[10] + " " + gfxengine::cvt_to_string(v[0]) + " " + gfxengine::cvt_to_string(v[1]));
		unsigned char s = 0;
		glGetBooleanv(params[11], &s);
		GLLog(names[11] + " " + gfxengine::cvt_to_string((unsigned int)s));
		GLLog("-----------------------------");
	}
}