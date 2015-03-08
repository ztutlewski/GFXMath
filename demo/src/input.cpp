#include "input.h"
#include "glapplication.h"
#include <iostream>

namespace gofxengine
{
	Input* Input::currentInput;
	bool Input::inputFuncsInitialized;

	Input::Input(){}

	Input::Input(const GLApplication& application)
	{
		for (size_t i = 0; i < 26; i++)
		{
			letterKeysDown[i] = false;
		}

		for (size_t i = 0; i < 10; i++)
		{
			numberKeysDown[i] = false;
		}
	}

	bool Input::InputFuncsInitialized()
	{
		return inputFuncsInitialized;
	}

	void Input::ConsumeEvents()
	{
		mouseDeltaX = 0.0f;
		mouseDeltaY = 0.0f;
	}

	void MouseMoveEvent(GLFWwindow* window, double xPos, double yPos)
	{
		Input& currentInput = Input::GetCurrentInput();

		currentInput.lastMousePosX = currentInput.mousePosX;
		currentInput.mousePosX = xPos;

		currentInput.lastMousePosY = currentInput.mousePosY;
		currentInput.mousePosY = yPos;

		currentInput.mouseDeltaX = (float)(currentInput.mousePosX - currentInput.lastMousePosX);
		currentInput.mouseDeltaY = (float)(currentInput.mousePosY - currentInput.lastMousePosY);
	}

	void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
		{
			Input::GetCurrentInput().letterKeysDown[key - GLFW_KEY_A] = action != GLFW_RELEASE;
		}
		else if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
		{
			Input::GetCurrentInput().numberKeysDown[key - GLFW_KEY_0] = action != GLFW_RELEASE;
		}
	}

	void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
	{

	}

	Input& Input::GetCurrentInput()
	{
		return *currentInput;
	}

	void UseInput(Input* input, const GLApplication& application)
	{
		Input::currentInput = input;

		if (!Input::inputFuncsInitialized)
		{
			GLFWwindow* window = application.GetWindow();

			glfwSetCursorPosCallback(window, MouseMoveEvent);
			glfwSetKeyCallback(window, KeyEvent);
			glfwSetMouseButtonCallback(window, MouseButtonEvent);

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			Input::inputFuncsInitialized = true;
		}
	}
}