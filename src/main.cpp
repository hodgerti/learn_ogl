/*==================================================
= Description: This is the main file
====================================================*/

/************************************
* Headers
*************************************/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glfw_help/glfw_helper.h>
#include <stdio.h>
#include <stdlib.h>

/************************************
* Types
*************************************/

/************************************
* Definitions
*************************************/
#define CONTEXT_TITLE		"LearnOpenGL"
#define WINDOW_WIDTH		800
#define WINDOW_HEIGHT		600

/************************************
* Global variables
*************************************/
GLFWwindow *window;
GLFWInputHandler input_handler;

/************************************
* Callbacks
*************************************/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 


/*-----------------------------
- Initialize window/context
- and anything else that needs it
-------------------------------*/
int init()
{
	// make the 
	window = start_glfw(WINDOW_WIDTH, WINDOW_HEIGHT, CONTEXT_TITLE);
	if(window == NULL)
	{
		return -1;
	}

	// generate ogl function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	// set window resizing callback
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

	
	input_handler.set_window(window);
	input_handler.add_key(50, GLFW_KEY_SPACE);
	input_handler.remove_key(50);

	return 0;
}

/*-----------------------------
- Cleanup and end context
-------------------------------*/
int stop()
{
	glfwTerminate();
	return 0;
}

/*-----------------------------
- Run the render loop
-------------------------------*/
int render_loop()
{
	while(!glfwWindowShouldClose(window))
	{
		// swap color buffer
		glfwSwapBuffers(window);
		// check if any events are triggered, call needed callbacks, and update window state
		glfwPollEvents();
	}

	stop();
	return 0;
}

/*-----------------------------
- Main
-------------------------------*/
int main()
{
	int init_status = init(); 
	if(init_status != 0)
	{
		return init_status;
	}

	return render_loop();
}