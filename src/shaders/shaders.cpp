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
Shader::Shader()
{

}

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
	set_shaders(vertex_path, fragment_path);
}

Shader::~Shader()
{
	delete [] vert_path;
	delete [] frag_path;
}

void Shader::set_shaders(const char* vertex_path, const char* fragment_path)
{
	int vert_len = strlen(vertex_path) + 1;
	int frag_len = strlen(fragment_path) + 1;
	vert_path = new char[vert_len];
	frag_path = new char[frag_len];
	strcpy_s(vert_path, vert_len, vertex_path);
	strcpy_s(frag_path, frag_len, fragment_path);

	compile_shaders();
	link_shaders();

	glDeleteShader(vert);
	glDeleteShader(frag); 
}

void Shader::read_shader_file(char *path, char **source)
{
	FILE *fp;

	fopen_s(&fp, path, "r");
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	rewind(fp);
	*source = new char[sz];
	fgets(*source, sz, (FILE*)fp); 
	fclose(fp);
}

void Shader::compile_shaders()
{
	char *vert_src = NULL;
	char *frag_src = NULL;

	read_shader_file(vert_path, &vert_src);
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vert_src, NULL);
	glCompileShader(vert);
	check_shader_compile(vert);
	delete [] vert_src;

	read_shader_file(frag_path, &frag_src);
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &frag_src, NULL);
	glCompileShader(frag);
	check_shader_compile(frag);	
	delete [] frag_src;
}

void Shader::link_shaders()
{
	program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	check_shader_program(program);
}

void Shader::check_shader_compile(unsigned int shader)
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

void Shader::check_shader_program(unsigned int program)
{
	int  success;
	char info_log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << info_log << std::endl;
	}
}

void Shader::use()
{
	glUseProgram(program);
}

unsigned int Shader::get_vert()
{
	return vert;
}

unsigned int Shader::get_frag()
{
	return frag;
}

unsigned int Shader::get_program()
{
	return program;
}