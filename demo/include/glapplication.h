#ifndef GL_APPLICATION_DOT_H
#define GL_APPLICATION_DOT_H
#include <glew.h>
#include <GLFW\glfw3.h>

namespace gofxengine
{
	class GLApplication
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="GLApplication"/> struct.
		/// </summary>
		GLApplication();

		/// <summary>
		/// Initializes the windowed.
		/// </summary>
		/// <param name="majorVersion">The major version.</param>
		/// <param name="minorVersion">The minor version.</param>
		/// <param name="pixelWidth">Width of the pixel.</param>
		/// <param name="pixelHeight">Height of the pixel.</param>
		/// <param name="title">The title.</param>
		/// <returns></returns>
		bool InitWindowed(GLint majorVersion, GLint minorVersion, GLint pixelWidth, GLint pixelHeight, const char* const title);

		/// <summary>
		/// Initializes the fullscreen.
		/// </summary>
		/// <param name="majorVersion">The major version.</param>
		/// <param name="minorVersion">The minor version.</param>
		/// <param name="title">The title.</param>
		/// <returns></returns>
		bool InitFullscreen(GLint majorVersion, GLint minorVersion, const char* const title);
				
		/// <summary>
		/// Creates the instance.
		/// </summary>
		/// <param name="application">The application.</param>
		/// <returns></returns>
		bool InitGLFW();
		
		/// <summary>
		/// Starts the game loop.
		/// </summary>
		/// <returns></returns>
		int StartGameLoop();
		
		/// <summary>
		/// Gets the window.
		/// </summary>
		/// <returns></returns>
		GLFWwindow* GetWindow() const;
	private:
		GLApplication(GLApplication& other){}

		/// <summary>
		/// Initializes the application.
		/// </summary>
		void InitApplication();

		/// <summary>
		/// Sets the hints.
		/// </summary>
		/// <param name="majorVersion">The major version.</param>
		/// <param name="minorVersion">The minor version.</param>
		void SetHints(GLint majorVersion, GLint minorVersion);

		GLFWwindow* window;
	};
}
#endif