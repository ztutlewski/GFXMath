#ifndef INPUT_DOT_H
#define INPUT_DOT_H

namespace gofxengine
{
	class GLApplication;

	class Input
	{
	public:
		bool letterKeysDown[26];// A-Z
		bool numberKeysDown[10];// 0-9

		double mousePosX;
		double mousePosY;

		double lastMousePosX;
		double lastMousePosY;

		float mouseDeltaX;
		float mouseDeltaY;

		Input();

		void ConsumeEvents();

		static bool InputFuncsInitialized();

		friend void UseInput(Input* input, const GLApplication& application);

		static Input& GetCurrentInput();
	private:
		static Input* currentInput;
		static bool inputFuncsInitialized;
	};
}

#endif