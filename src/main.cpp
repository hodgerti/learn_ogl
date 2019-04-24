/*==================================================
= Description: This is the main file
====================================================*/

/************************************
* Headers
*************************************/
#include <glfw_help/glfw_helper.h>
#include <shaders/shaders.h>
#include <textures/textures.h>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <geometry/geometry.h>
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

#define RESOURCES_FOLDER		"D:/Documents/learn_ogl/learn_ogl_resources/"
#define TEXTURES_FOLDER			RESOURCES_FOLDER"textures/"

#define CONTAINER_TEX_DIFF		TEXTURES_FOLDER"container.jpg"
#define AWESOMEFACE_TEX_DIFF	TEXTURES_FOLDER"awesomeface.png"

#define TEX_MIX_INCR	0.05f

/************************************
* Global variables
*************************************/
GLFWwindow			*window;
GLFWInputHandler	input_handler;
Shader			    shader;
Texture				container_tex_diff, awesomeface_tex_diff;
unsigned int		VBO, EBO, VAO;
float				tex_mix_amount = 0.0f;


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
	if(input_handler.pop_click(GLFW_KEY_W))
	{
		tex_mix_amount += TEX_MIX_INCR;
	}
	if(input_handler.pop_click(GLFW_KEY_S))
	{
		tex_mix_amount -= TEX_MIX_INCR;
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
	input_handler.add_key(GLFW_KEY_W, GLFW_KEY_W);
	input_handler.add_key(GLFW_KEY_S, GLFW_KEY_S);

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
	glVertexAttribPointer(VERT_SHADER_LOCATION, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(VERT_SHADER_LOCATION);
	glVertexAttribPointer(VERT_SHADER_COLOR, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(VERT_SHADER_COLOR);
	glVertexAttribPointer(VERT_SHADER_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(VERT_SHADER_TEX_COORD);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// load textures
	stbi_set_flip_vertically_on_load(true);

	container_tex_diff.set_target(GL_TEXTURE_2D);
	container_tex_diff.set_unit(GL_TEXTURE0);
	container_tex_diff.add_parameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	container_tex_diff.add_parameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	container_tex_diff.add_parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	container_tex_diff.add_parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	container_tex_diff.load(CONTAINER_TEX_DIFF);

	awesomeface_tex_diff.set_target(GL_TEXTURE_2D);
	awesomeface_tex_diff.set_unit(GL_TEXTURE1);
	awesomeface_tex_diff.add_parameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	awesomeface_tex_diff.add_parameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	awesomeface_tex_diff.add_parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	awesomeface_tex_diff.add_parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	awesomeface_tex_diff.load(AWESOMEFACE_TEX_DIFF);

	shader.use();
	glUniform1i(glGetUniformLocation(shader.get_program(), 
									 TEX_UNIFORM_0), 
									 get_tex_unit_num(container_tex_diff.get_unit()));
	glUniform1i(glGetUniformLocation(shader.get_program(), 
									 TEX_UNIFORM_1), 
									 get_tex_unit_num(awesomeface_tex_diff.get_unit()));

	return 0;
}

/*-----------------------------
- Cleanup and end context
-------------------------------*/
int stop()
{
	glfwTerminate();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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

		// draw
		glUniform1f(glGetUniformLocation(shader.get_program(), TEX_MIX_UNIFORM), tex_mix_amount);
		
		container_tex_diff.use();
		awesomeface_tex_diff.use();
		shader.use();

		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 6);
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