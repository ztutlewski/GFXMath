#include "glapplication.h"
#include "log.h"
#include "ssevec.h"
#include "vecmath.h"
#include "input.h"
#include "scalar_math.h"
#include "shader.h"
#include "mesh.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include "string_convert.h"

#include "ssemat44.h"

using namespace std;
using namespace gofxmath;

namespace gofxengine
{
	Input input;
	SseMat44 projection, view, mv, mvp;
	GLint screenWidth = 640, screenHeight = 480;
	float pitch, yaw;

	SseVec camPos = SetSseVec3(0.0f, 0.0f, 0.0f);
	SseVec camFwd = SetSseVec3(0.0f, 0.0f, 1.0f);
	SseVec camUp = SetSseVec3(0.0f, 1.0f, 0.0f);
	SseVec camRt = SetSseVec3(1.0f, 0.0f, 0.0f);
	SseVec camRot = SetSseVec3(0.0f, 0.0f, 0.0f);
	SseVec worldUp = SetSseVec3(0.0f, 1.0f, 0.0f);

	void HandleControls()
	{
		static const float SENSITIVITY = 0.001f;
		static const float MOVEMENT_SPEED = 0.05f;
		static const float MAX_PITCH = 60.0f * DEG_TO_RAD;

		// Calculate camera rotations
		pitch += input.mouseDeltaY * SENSITIVITY;
		pitch = max(min(pitch, MAX_PITCH), -MAX_PITCH);

		yaw -= input.mouseDeltaX * SENSITIVITY;
		yaw = yaw > 0 ? (fmodf(yaw + F_PI, F_2PI) - F_PI) : (fmodf(yaw - F_PI, F_2PI) + F_PI);

		SseVec yawRot = QuaternionFromAxisAngle(SetSseVec3(0.0f, 1.0f, 0.0f), yaw);
		SseVec pitchRot = QuaternionFromAxisAngle(SetSseVec3(1.0f, 0.0f, 0.0f), pitch);

		// Generate the rotation matrix for the view, and update the camera's relative forward, right, and up directions
		SseMat44 rotationMat = RotationMatrixFromEuler(SetSseVec3(pitch, yaw, 0.0f));
		camFwd = TransformVec3(rotationMat, SetSseVec3(0.0f, 0.0f, 1.0f));
		camFwd = Vec3Normalize(camFwd);
		camRt = Vec3Cross(worldUp, camFwd);
		camUp = Vec3Cross(camFwd, camRt);
		

		float fwrdMovement = -(input.letterKeysDown[18] - input.letterKeysDown[22]) * MOVEMENT_SPEED;
		float sideMovement = (input.letterKeysDown[0] - input.letterKeysDown[3]) * MOVEMENT_SPEED;
		SseVec movement;
		SseVec zero = SetVecZero();
		SseVec tmp0 = VecBlend<LEFT,RIGHT,LEFT,LEFT>(camFwd, zero);
		SseVec right = Vec3MulScalar(camRt, sideMovement);
		SseVec forward = Vec3MulScalar(tmp0, fwrdMovement);
		movement = Vec3Add(forward, right);
		SseVec tmpCamPos = Vec3Add(camPos, movement);

		camPos = tmpCamPos;

		view = LookDir(camPos, camFwd, worldUp);
	}

	void GlfwErrorCallback(int error, const char* description)
	{
		GLLogErr("GLFW ERROR: code " + gofxengine::cvt_to_string(error) + " msg:" + description);
	}

	void UpdateFPSCounter(GLFWwindow* window)
	{

		static double previous_seconds = glfwGetTime();
		static int frame_count;
		double current_seconds = glfwGetTime();
		double elapsed_seconds = current_seconds - previous_seconds;

		if (elapsed_seconds > 0.25)
		{
			previous_seconds = current_seconds;
			double fps = (double)frame_count / elapsed_seconds;
			string tmp = "opengl @ fps: " + gofxengine::cvt_to_string(fps);
			glfwSetWindowTitle(window, tmp.c_str());
			frame_count = 0;
		}
		frame_count++;
	}

	GLuint LoadShaders()
	{
		GLuint vs = LoadShader("VertexShader.vert", GL_VERTEX_SHADER);
		GLuint fs = LoadShader("FragmentShader.frag", GL_FRAGMENT_SHADER);
		return CreateShaderProgram(vs, fs);
	}

	GLuint LoadMeshes()
	{
		const float POS_Z = 0.0f;

		ColorVertex vert[4]{
			{ { -0.5f,  0.5f, POS_Z }, { 1.0f, 0.0f, 0.0f } },
			{ {  0.5f, -0.5f, POS_Z }, { 0.0f, 1.0f, 0.0f } },
			{ { -0.5f, -0.5f, POS_Z }, { 1.0f, 0.0f, 1.0f } },
			{ {  0.5f,  0.5f, POS_Z }, { 0.5f, 0.0f, 0.5f } }
		};

		GLuint indices[6]{
			2,1,0,
			1,3,0
		};

		GLuint vertVBOID = 0;
		glGenBuffers(1, &vertVBOID);
		glBindBuffer(GL_ARRAY_BUFFER, vertVBOID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ColorVertex) * 4, &vert[0].pos.x, GL_STATIC_DRAW);

		GLuint idxVBOID = 0;
		glGenBuffers(1, &idxVBOID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxVBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indices, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertVBOID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), BUFFER_OFFSET(0));

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertVBOID);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), BUFFER_OFFSET(12));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxVBOID);

		glBindVertexArray(0);
		return vao;
	}


	GLApplication::GLApplication()
	{
	}

	bool GLApplication::InitGLFW()
	{
		assert(RestartGLLog());

		// start GL context and O/S window using the GLFW helper library
		GLLog("Starting GLFW\n" + string(glfwGetVersionString()) + "\n");

		// register the error call-back function that we wrote, above
		glfwSetErrorCallback(GlfwErrorCallback);

		if (!glfwInit())
		{
			cerr << "ERROR: could not start GLFW3" << endl;
			return false;
		}

		return true;
	}

	void GLApplication::SetHints(GLint majorVersion, GLint minorVersion)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	bool GLApplication::InitWindowed(GLint majorVersion, GLint minorVersion, GLint pixelWidth, GLint pixelHeight, const char* const title)
	{
		SetHints(majorVersion, minorVersion);
		window = glfwCreateWindow(pixelWidth, pixelHeight, title, NULL, NULL);

		if (!window)
			return false;

		InitApplication();

		return true;
	}

	bool GLApplication::InitFullscreen(GLint majorVersion, GLint minorVersion, const char* const title)
	{
		SetHints(majorVersion, minorVersion);
		GLFWmonitor* mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(mon);
		window = glfwCreateWindow(vmode->width, vmode->height, title, mon, NULL);

		if (!window)
			return false;

		InitApplication();

		return true;
	}

	void GLApplication::InitApplication()
	{
		glfwMakeContextCurrent(window);

		LogGLParams();

		// start GLEW extension handler
		glewExperimental = GL_TRUE;
		glewInit();

		// get version info
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		cout << "Renderer: " << renderer << endl;
		cout << "OpenGL version supported " << version << endl;

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST);// enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
		glEnable(GL_CULL_FACE); // cull face
		glCullFace(GL_BACK); // cull back face
		glFrontFace(GL_CW); // GL_CCW for counter clock-wise

		UseInput(&input, *this);
	}

	int GLApplication::StartGameLoop()
	{
		array<float, 16> mvpData;
		GLuint shaderProgram = LoadShaders();
		GLuint vao = LoadMeshes();
		projection = PerspectiveProjectionMatrix(0.1f, 1000.0f, 90.0f * DEG_TO_RAD, (float)screenWidth / (float)screenHeight);

		SseVec rotationQuat = QuaternionFromAxisAngle(SetSseVec3(0.0f, 1.0f, 0.0f), F_2PI_3 * 0.5f);
		SseVec tmpRotQuat = rotationQuat;
		SseVec translationVec = SetSseVec3(0.0f, 0.0f, 2.0f);

		SseMat44 translation = TranslationMatrixFromVec3(translationVec);

		SseMat44 models[12];

		models[0] = translation;

		for (size_t i = 1; i < 12; i++)
		{
			SseMat44 rotation = RotationMatrixFromQuaternion(tmpRotQuat);
			models[i] = MatrixMultiply(rotation, translation);
			tmpRotQuat = QuaternionMultiply(tmpRotQuat, rotationQuat);
		}

		view = LookDir(camPos, camFwd, camUp);

		GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);

		while (!glfwWindowShouldClose(window))
		{
			UpdateFPSCounter(window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

			for (size_t i = 0; i < 12; i++)
			{
				mv = MatrixMultiply(view, models[i]);
				mvp = MatrixMultiply(projection, mv);
				mvpData = MatrixToArray(mvp);

				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, mvpData.data());
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
			}

			glfwPollEvents();
			HandleControls();
			input.ConsumeEvents();
			glfwSwapBuffers(window);

			if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			{
				glfwSetWindowShouldClose(window, 1);
			}
			else if (glfwGetKey(window, GLFW_KEY_P))
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				while (!glfwGetKey(window, GLFW_KEY_U) && !glfwWindowShouldClose(window))
				{
					glfwPollEvents();
					if (glfwGetKey(window, GLFW_KEY_ESCAPE))
					{
						glfwSetWindowShouldClose(window, 1);
					}
				}

				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}

		glfwTerminate();

		return 0;
	}

	GLFWwindow* GLApplication::GetWindow() const
	{
		return window;
	}
}