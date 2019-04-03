/*==================================================
= Description: This provides helper functions to
= facilitate GLFW
====================================================*/

/************************************
* Headers
*************************************/
#include <glfw_help/glfw_helper.h>


/************************************
* Functions
*************************************/

GLFWwindow * start_glfw(int w_width, int w_height, char *monitor)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(w_width, w_height, monitor, NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return window;
	}
	glfwMakeContextCurrent(window);

	return window;
}