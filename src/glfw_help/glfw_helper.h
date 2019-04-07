#ifndef GLFW_HELPER_H
#define GLFW_HELPER_H

/*==================================================
= Description: This provides helper functions to 
= facilitate GLFW
====================================================*/

/************************************
* Headers
*************************************/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

/************************************
* Types
*************************************/
struct key_handle
{
	int				key_id;
	int				key_name;
	unsigned int	clicked;
	bool			pressed;
	bool			unpressed;
};

#define DFLT_KEYS_SIZE		16
#define NO_KEY_ID			-1

class GLFWInputHandler
{
	private:
	GLFWwindow *window;
	key_handle **keys;
	int keys_sz;

	void init_key(key_handle *key, int key_id, int key_name);

	public:

	GLFWInputHandler();
	GLFWInputHandler(GLFWwindow *in_window);
	~GLFWInputHandler();

	void set_window(GLFWwindow *in_window);

	int  get_clicks();
	bool get_pressed();
	bool get_unpressed();

	void update();
	void add_key(int key_id, int key_name);
	void remove_key(int key_id);

};

/************************************
* Functions
*************************************/

/*-----------------------------
- Starts a GLFW window
-------------------------------*/
GLFWwindow *start_glfw(int w_width, int w_height, char *monitor);



#endif