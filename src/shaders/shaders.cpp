/************************************
* Headers
*************************************/
#include <shaders/shaders.h>

/************************************
* Raw shaders
*************************************/
const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

/************************************
* Functions
*************************************/
void check_shader_compile(unsigned int shader)
{
	int  success;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
	}
}

void check_shader_program(unsigned int shader_program)
{
	int  success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << info_log << std::endl;
	}
}

void compile_shaders
(
	unsigned int *vertex_shader, 
	unsigned int *fragment_shader
)
{
	*vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(*vertex_shader);
	check_shader_compile(*vertex_shader);

	*fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(*fragment_shader);
	check_shader_compile(*fragment_shader);
}

void link_shaders
(
	unsigned int *shader_program,
	unsigned int *shaders,
	int			  num_shaders
)
{
	*shader_program = glCreateProgram();
	for(int i = 0; i < num_shaders; i++)
	{
		glAttachShader(*shader_program, shaders[i]);
	}
	glLinkProgram(*shader_program);
	check_shader_program(*shader_program);
}