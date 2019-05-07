#ifndef CAMERA_H
#define CAMERA_H

/************************************
* Headers
*************************************/
#include <shaders/shaders.h>
#include <delta_time/delta_time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

/************************************
* Definitions
*************************************/
#define DFLT_MOUSE_SENSITIVITY			0.09
#define DFLT_MOUSE_SENSITIVITY_INCR		0.001
#define DFLT_STRAFE_SPEED		5.0
#define DFLT_STRAFE_SPEED_INCR	0.5
#define DFLT_MOVE_SPEED			3.0
#define DFLT_MOVE_SPEED_INCR	0.3
#define MAX_PITCH  89.9999f
#define MIN_PITCH -89.9999f

/************************************
* Macros
*************************************/
#define min(a,b)		(((a)<(b))?(a):(b))
#define max(a,b)		(((a)>(b))?(a):(b))
#define clamp(c,a,b)	(max((a),min((c),(b))))

/************************************
* Types
*************************************/
class Camera
{
	private:
		glm::mat4 model;
		glm::vec3 pos		= glm::vec3(0.0f, 0.0f,  3.0f);
		glm::vec3 front		= glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up_view	= glm::vec3(0.0f, 1.0f,  0.0f);
		glm::mat4 clip;

		double last_x, last_y, pitch, yaw;

	public:
		Camera() : delta_time(glfwGetTime) { }
		DeltaTime delta_time;

		unsigned int shader_id;

		double sensitivity = DFLT_MOUSE_SENSITIVITY;
		double strafe_speed = DFLT_STRAFE_SPEED;
		double move_speed = DFLT_MOVE_SPEED;
		
		void set_world(glm::mat4 model);
		void move_forward();
		void move_backwards();
		void move_left();
		void move_right();
		void set_up_view(glm::vec3 up);
		void set_mouse(glm::vec2 mouse_pos);
		void set_clip_perspective(double fov, double aspect, double near_plane, double far_plane);
		void set_clip_orthographic(double width, double height, double near_plane, double far_plane);

		void use_world();
		void use_view();
		void use_clip();

		void use();
		void update();
};

/************************************
* Functions
*************************************/

#endif 