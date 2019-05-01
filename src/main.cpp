/*==================================================
= Description: This is the main file
====================================================*/

/************************************
* Headers
*************************************/
#include <glfw_help/glfw_helper.h>
#include <shaders/shaders.h>
#include <textures/textures.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <transform/transform.h>

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
* Macros
*************************************/
#define min(a,b)		(((a)<(b))?(a):(b))
#define max(a,b)		(((a)>(b))?(a):(b))
#define clamp(c,a,b)	(max((a),min((c),(b))))


/************************************
* Global variables
*************************************/
GLFWwindow			*window;
GLFWInputHandler	input_handler;
Shader			    shader;
Texture				container_tex_diff, awesomeface_tex_diff;
unsigned int		VBO, EBO, VAO;
float				tex_mix_amount = 0.0f;
float				camera_speed = 0.02f;
float				camera_speed_inc_amount = 0.001f;
glm::vec3 pos_view   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 front_view = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up_view    = glm::vec3(0.0f, 1.0f,  0.0f);


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
	if(input_handler.check_pressed(GLFW_KEY_W))
	{
		pos_view += camera_speed * front_view;
	}
	if(input_handler.check_pressed(GLFW_KEY_A))
	{
		pos_view -= glm::normalize(glm::cross(front_view, up_view)) * camera_speed;
	}
	if(input_handler.check_pressed(GLFW_KEY_S))
	{
		pos_view -= camera_speed * front_view;
	}
	if(input_handler.check_pressed(GLFW_KEY_D))
	{
		pos_view += glm::normalize(glm::cross(front_view, up_view)) * camera_speed;
	}
	if(input_handler.pop_click(GLFW_KEY_UP))
	{
		camera_speed += camera_speed_inc_amount;
	}
	if(input_handler.pop_click(GLFW_KEY_DOWN))
	{
		camera_speed -= camera_speed_inc_amount;
	}
	camera_speed = clamp(camera_speed, camera_speed_inc_amount, 15.0f*camera_speed_inc_amount);
}



/*-----------------------------
- Initialize window/context
- and anything else that needs it
-------------------------------*/
int init()
{
	// make the window
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
	input_handler.add_key(GLFW_KEY_A, GLFW_KEY_A);
	input_handler.add_key(GLFW_KEY_S, GLFW_KEY_S);
	input_handler.add_key(GLFW_KEY_D, GLFW_KEY_D);
	input_handler.add_key(GLFW_KEY_UP, GLFW_KEY_UP);
	input_handler.add_key(GLFW_KEY_DOWN, GLFW_KEY_DOWN);

	// set OGL features
	glEnable(GL_DEPTH_TEST);

	// set up shaders
	shader.set_shaders( BASIC_VERT_SHADER, BASIC_FRAG_SHADER );

	// set up VAOs
	glGenVertexArrays(1, &VAO);  

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERT_SHADER_LOCATION, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(VERT_SHADER_LOCATION);
	glVertexAttribPointer(VERT_SHADER_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view space
		//glm::vec3 target_view = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 direction_view = glm::normalize(pos_view - target_view);
		//glm::vec3 up_world = glm::vec3(0.0f, 1.0f, 0.0f);
		//glm::vec3 right_view = glm::normalize(glm::cross(up_world, direction_view));  // opposite direction
		//glm::vec3 up_view = glm::cross(direction_view, right_view); 

		glm::mat4 view;
		view = glm::lookAt(pos_view, pos_view + front_view, up_view);

		unsigned int uniform_loc = glGetUniformLocation(shader.get_program(), VIEW_MAT_UNIFORM);
		glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(view));

		// clip space
		glm::mat4 projection	= glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH/WINDOW_HEIGHT), 0.1f, 100.0f);
		
		uniform_loc = glGetUniformLocation(shader.get_program(), PROJECTION_MAT_UNIFORM);
		glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(projection));

		// draw
		glUniform1f(glGetUniformLocation(shader.get_program(), TEX_MIX_UNIFORM), tex_mix_amount);
		
		container_tex_diff.use();
		awesomeface_tex_diff.use();
		shader.use();

		glBindVertexArray(VAO);
		for( int idx = 0; idx < sizeof(cube_positions)/sizeof(glm::vec3); idx++ )
		{
			// world space
			glm::mat4 model	= glm::mat4(1.0f);

			model =	glm::translate(model, cube_positions[idx]);
			model =	glm::rotate(model, 
				                ((float)glfwGetTime() * glm::radians(50.0f)) + ((float)idx * 25.0f), 
				                glm::vec3(1.0f+(1.0f/(float)(idx+1)), 0.3f+(1.5f/(float)(idx+1)), 0.5f+(3.0f/(float)(idx+1))));
			
			uniform_loc = glGetUniformLocation(shader.get_program(), MODEL_MAT_UNIFORM);
			glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
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