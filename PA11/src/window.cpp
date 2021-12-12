#include <window.h>

Window::Window()
{
	window = NULL;
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Initialize(const string &name, int* width, int* height)
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		cout << "Failed to initialize GLFW\n";
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( *width, *height, name.c_str(), NULL, NULL);
	if( window == NULL ){
		cout<< "Failed to open GLFW window.\n";
		return false;
	}
    glfwMakeContextCurrent(window);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, *width / 2, *height / 2);
	return true;
}

GLFWwindow* Window::getWindow() {
	return window;
}

void Window::Swap()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

