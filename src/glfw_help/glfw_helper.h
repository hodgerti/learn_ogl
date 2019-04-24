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
	unsigned int	clicks;
	bool			pressed;
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

		// get number of times button has been clicked. Non-destructive.
		int  get_clicks(int key_id);
		// pop a click off total clicks if one exists. Destructive.
		bool pop_click(int key_id);
		// erase all clicks.
		int  clear_clicks(int key_id);

		// check if button is pressed down
		bool check_pressed(int key_id);
		// check if button is not pressed down
		bool check_unpressed(int key_id);

		void update();
		// Add a key track
		void add_key(int key_id, int key_name);
		// Remove a key track. Doesn't unallocate any memory.
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