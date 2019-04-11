#ifndef SHADERS_H
#define SHADERS_H

/************************************
* Headers
*************************************/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>


/************************************
* Constants
*************************************/
#define VERT_SHADER_LOCATION		0

#define SHADERS_LOCATION			PROJECT_DIR"../src/shaders/"
#define VERT_SHADERS_LOCATION		SHADERS_LOCATION"vertex_shaders/"
#define GEOM_SHADERS_LOCATION		SHADERS_LOCATION"geomtry_shaders/"
#define FRAG_SHADERS_LOCATION		SHADERS_LOCATION"fragment_shaders/"

#define GEN_ERROR_FILE
#define SHADER_DEBUG_FILE_LOCATION			PROJECT_OUTPUT_DIR"shader_error_log"

#define VERT_SHADER_FILE_EXTENSION		"vert"
#define GEOM_SHADER_FILE_EXTENSION		"geom"
#define FRAG_SHADER_FILE_EXTENSION		"frag"

#define BASIC_VERT_SHADER		VERT_SHADERS_LOCATION"basic.vert\0"
#define BASIC_FRAG_SHADER		FRAG_SHADERS_LOCATION"basic.frag\0"

// Uniforms
#define FRAG_COLOR			"ourColor"

/************************************
* Types
*************************************/
class Shader
{
	private:

	unsigned int vert;
	unsigned int frag;
	unsigned int program;

	char *vert_path;
	char *frag_path;

	void compile_shaders();

	void link_shaders();

	void read_shader_file(char *path, char **source);

	public:

	Shader();
	Shader(const char* vertex_path, const char* fragment_path);

	~Shader();

	void set_shaders(const char* vertex_path, const char* fragment_path);

	void check_shader_compile(unsigned int shader);
	void check_shader_program(unsigned int program);

	void use();

	unsigned int get_vert();
	unsigned int get_frag();
	unsigned int get_program();

};

/************************************
* Functions
*************************************/

#endif