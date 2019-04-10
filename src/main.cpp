/*==================================================
= Description: This is the main file
====================================================*/

/************************************
* Headers
*************************************/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glfw_help/glfw_helper.h>
#include <geometry/geometry.h>
#include <shaders/shaders.h>
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
GLFWwindow			*window;
GLFWInputHandler	input_handler;
Shader			    shader;
unsigned int		VBO, EBO, VAO;

/************************************
* Callbacks
*************************************/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 


/*-----------------------------
- Process inputs
-------------------------------*/
void process_inputs()
{
	input_handler.update();
	if(input_handler.check_pressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
	if(input_handler.get_clicks(GLFW_KEY_P) > 4)
	{
		glfwSetWindowShouldClose(window, true);
	}
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

	// setup keys
	input_handler.set_window(window);
	input_handler.add_key(GLFW_KEY_ESCAPE, GLFW_KEY_ESCAPE);
	input_handler.add_key(GLFW_KEY_P, GLFW_KEY_P);

	// set up shaders
	shader.set_shaders( BASIC_VERT_SHADER, BASIC_FRAG_SHADER );

	// set up VAOs
	glGenVertexArrays(1, &VAO);  

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_indices), rectangle_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERT_SHADER_LOCATION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(VERT_SHADER_LOCATION);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
		// input
		process_inputs();

		// rendering calls here
		//  --------

		// clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw rectangle
		float time_value = (float)glfwGetTime();
		float green_value = (sin(time_value) / 2.0f) + 0.5f;
		//int vertex_color_location = glGetUniformLocation(shader.get_program(), "ourColor");
		shader.use();
		//glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		
		// check if any events are triggered, call needed callbacks, and update window state
		glfwPollEvents();
		// swap color buffer
		glfwSwapBuffers(window);
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