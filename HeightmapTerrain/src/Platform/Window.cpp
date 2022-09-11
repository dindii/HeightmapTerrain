#include "Window.h"

#include <Event/KeyEvent.h>
#include <Event/ApplicationEvent.h>
#include <Event/MouseEvent.h>

#include <Util/HAssert.h>
#include <GLFW/glfw3.h>

namespace Height
{
	Window::Window(float width, float height, const char* m_Name)
	{
		HT_ASSERT((width > 0 || height > 0), "Could not create window: negative resolution.");

		m_Width = width;
		m_Height = height;

		bool glfwInitialized = glfwInit();
		HT_ASSERT(glfwInitialized, "Could not initialize window system!");



		m_AspectRatio = (float)m_Width / (float)m_Height;

		m_Window = glfwCreateWindow((int)m_Width, (int)m_Height, m_Name, NULL, NULL);

		HT_ASSERT(m_Window, "Could not create window!");

		glfwSetWindowUserPointer(m_Window, this);

		//For any graphics api
		glfwMakeContextCurrent(m_Window);

		//Set key callback 
		auto KeyCallbackFunc = [](GLFWwindow* window, int key, int scanCode, int action, int mods)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->keyCallback(window, key, scanCode, action, mods);
		};

		//I am creating a lambda and then assigning this lambda to the callback because I can't assign member functions for this function.
		//The main solution for this, would be to define my callback inside glfwSetKeyCallback through a lambda, but I don't want to do this because it would expand A LOT this constructor.
		//So I'm just creating a lambda that will call our function member, this way I keep this constructor short. It doesn't matter anyway performance-wise speaking.
		glfwSetKeyCallback(m_Window, KeyCallbackFunc);

		//Set mouse button callback
		auto MouseButtonCallbackFunc = [](GLFWwindow* window, int button, int action, int mods)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->mouseButtonCallback(window, button, action, mods);
		};

		glfwSetMouseButtonCallback(m_Window, MouseButtonCallbackFunc);

		//Set window resize callback
		auto WindowResizeCallbackFunc = [](GLFWwindow* window, int width, int height)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->windowResizeCallback(window, width, height);
		};

		glfwSetWindowSizeCallback(m_Window, WindowResizeCallbackFunc);


		//Set window close callback
		auto WindowCloseCallbackFunc = [](GLFWwindow* window)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->windowCloseCallback(window);
		};

		glfwSetWindowCloseCallback(m_Window, WindowCloseCallbackFunc);


		//Set window mouse moved callback
		auto WindowMouseMovedCallback = [](GLFWwindow* window, double xpos, double ypos)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->cursorPositionCallback(window, xpos, ypos);
		};

		glfwSetCursorPosCallback(m_Window, WindowMouseMovedCallback);

		glfwWindowHint(GLFW_SAMPLES, 4);
	}

	Window::~Window()
	{

	}

	void Window::OnUpdate()
	{
		swapBuffers();
		pollEvents();
	}

	float Window::GetTime() const
	{
		return (float)glfwGetTime();
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent e(key, false);
				EventCallback(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent e(key, true);
				EventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e(key);
				EventCallback(e);
				break;
			}
		}
	}

	void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		MouseMovedEvent e((uint32_t)xpos, (uint32_t)ypos);
		EventCallback(e);
	}

	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e(button);
				EventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e(button);
				EventCallback(e);
				break;
			}
		}
	}

	void Window::windowResizeCallback(GLFWwindow* window, int width, int height)
	{
		m_Width = width;
		m_Height = height;

		m_AspectRatio = (float)width / (float)height;

		WindowResizeEvent e(width, height);
		EventCallback(e);
	}

	void Window::windowCloseCallback(GLFWwindow* window)
	{
		WindowCloseEvent e;
		EventCallback(e);
	}

}