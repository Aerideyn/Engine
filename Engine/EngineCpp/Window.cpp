#include "Window.h"
#include "Monitor.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

// tracking pointers / counters
int WindowIDCounter = 0;
GLEWContext* CurrentGlewContext = nullptr;
Render::Window* ActiveWindow = nullptr;

// This needs to be defined for GLEW MX to work.
GLEWContext* glewGetContext(){ return CurrentGlewContext; }

// Non fullscreen window creation.
Render::Window Render::Window::CreateWindow(int Width, int Height, const char* Title)
{
	return Render::Window(glfwCreateWindow(Width, Height, Title, NULL, NULL));
}

// creates a full screen window on the targeted monitor.
Render::Window Render::Window::CreateFullscreenWindow(int Width, int Height, const char* Title, Monitor monitor)
{
	return Render::Window(glfwCreateWindow(Width, Height, Title, monitor.Handle, NULL));
}

// constructor.
Render::Window::Window()
{
	windowGlewContext = 0;
	windowHandle = 0;
	WindowID = -1;
}

Render::Window::Window(GLFWwindow* handle)
{	
	if (handle == nullptr){
		std::cout << "Failed to open GLFW window." << std::endl;
	}

	windowHandle = handle;
	WindowID = WindowIDCounter++;
	windowGlewContext = std::shared_ptr<GLEWContext>(new GLEWContext());
	GLuint VertexArrayID = -1;

	// store current context so it can be restored after.
	Window* previous = ActiveWindow;

	// capture opengl context in order to initialize glew into this window.
	ActiveWindow = this;
	glfwMakeContextCurrent(windowHandle);
	CurrentGlewContext = windowGlewContext.get();
	
	// initialize glew into this window.
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// a problem occured when trying to init glew, report it:
		printf("GLEW Error occured, Description: %s\n", glewGetErrorString(err));
		glfwDestroyWindow(windowHandle);
		windowHandle = nullptr;
	}

	// setup VAO
	glGenVertexArrays(1, &VertexArrayID);
	VAOid = VertexArrayID;

	if (previous == nullptr) 
		glBindVertexArray(static_cast<GLuint>(VAOid)); // this is the first window created - bind it's VAO.
	else 
		previous->SetAsActive(); // restore context if it was not null initially.
}

Render::Window::~Window()
{
}

void Render::Window::Clear(bool ClearDepthbuffer)
{
	if (ClearDepthbuffer)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);
}

void Render::Window::Close()
{
	glfwSetWindowShouldClose(windowHandle, GL_TRUE);
}

void Render::Window::Display()
{
	glfwSwapBuffers(windowHandle);
	glfwPollEvents();
}

void Render::Window::SetAsActive()
{
	if (ActiveWindow == nullptr || ActiveWindow->WindowID != WindowID)
	{
		ActiveWindow = this;
		glfwMakeContextCurrent(windowHandle);
		CurrentGlewContext = windowGlewContext.get();
		if (VAOid > 0) glBindVertexArray(static_cast<GLuint>(VAOid));
	}
}

Render::Window& Render::Window::GetActiveWindow()
{
	return *ActiveWindow;
}

int Render::Window::GetWidthX()
{
	int width, height;
	glfwGetWindowSize(windowHandle, &width, &height);
	return width;
}

int Render::Window::GetWidthY()
{
	int width, height;
	glfwGetWindowSize(windowHandle, &width, &height);
	return height;
}

float Render::Window::GetAspectRatio()
{
	return static_cast<float>(GetWidthX()) / GetWidthY();
}