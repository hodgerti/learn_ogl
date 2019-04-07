#ifndef SHADERS_H
#define SHADERS_H

/************************************
* Headers
*************************************/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

/************************************
* Functions
*************************************/
/*-----------------------------
- Check shaders
-------------------------------*/
void check_shader_compile(unsigned int shader);

/*-----------------------------
- Check shader program
-------------------------------*/
void check_shader_program(unsigned int shader_program);

/*-----------------------------
- Compile shaders
-------------------------------*/
void compile_shaders
(
	unsigned int *vertex_shader, 
	unsigned int *fragment_shader
);

void link_shaders
(
	unsigned int *shader_program,
	unsigned int *shaders,
	int			  num_shaders
);

#endif