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
* Functions
*************************************/

/*-----------------------------
- Starts a GLFW window
-------------------------------*/
GLFWwindow *start_glfw(int w_width, int w_height, char *monitor);

#endif