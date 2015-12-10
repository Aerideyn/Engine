#pragma once
#include <memory>

typedef struct GLEWContextStruct GLEWContext;
struct GLFWwindow;

GLEWContext* glewGetContext();

namespace Services
{
	class Keyboard;
	class Mouse;
}

namespace Render
{
	class Monitor;
	class Window
	{
		friend class Services::Keyboard;
		friend class Services::Mouse;
	public:
		~Window();
		Window();
		static Window CreateWindow(int Width, int Height, const char* Title);
		static Window CreateFullscreenWindow(int Width, int Height, const char* Title, Monitor Monitor);
	private:
		Window(GLFWwindow* window);
		int WindowID;
		int VAOid;
		GLFWwindow* windowHandle;
		std::shared_ptr<GLEWContext> windowGlewContext;
	public:
		void Clear(bool ClearDepthBuffer);
		void Close();
		void Display();
		void SetAsActive();
		int GetWidthX();
		int GetWidthY();
		float GetAspectRatio();
		static Window& GetActiveWindow();

	};
}