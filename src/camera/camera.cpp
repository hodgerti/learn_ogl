/************************************
* Headers
*************************************/
#include <camera/camera.h>

/************************************
* Functions
*************************************/

void Camera::set_world(glm::mat4 model)
{
	this->model = model;
}

void Camera::move_forward()
{
	float speed = move_speed * delta_time.delta_time;
	pos += speed * front;
}

void Camera::move_backwards()
{
	float speed = move_speed * delta_time.delta_time;
	pos -= speed * front;
}

void Camera::move_left()
{
	float speed = move_speed * delta_time.delta_time;
	pos -= glm::normalize(glm::cross(front, up_view)) * speed;
}

void Camera::move_right()
{
	float speed = move_speed * delta_time.delta_time;
	pos += glm::normalize(glm::cross(front, up_view)) * speed;
}

void Camera::set_up_view(glm::vec3 up)
{
	up_view = up;
}

void Camera::set_mouse(glm::vec2 mouse_pos)
{
	float x_offset = mouse_pos.x - last_x;
	float y_offset = last_y - mouse_pos.y;
	last_x = mouse_pos.x;
	last_y = mouse_pos.y;

	yaw   += x_offset * sensitivity;
	pitch += y_offset * sensitivity; 

	pitch = clamp(pitch, MIN_PITCH, MAX_PITCH);

	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(front);
}

void Camera::set_clip_perspective(double fov, double aspect, double near_plane, double far_plane)
{
	clip = glm::perspective(glm::radians((float)fov), (float)aspect, (float)near_plane, (float)far_plane);
}
void Camera::set_clip_orthographic(double width, double height, double near_plane, double far_plane)
{
	clip = glm::ortho(0.0f, (float)width, 0.0f, (float)height, (float)near_plane, (float)far_plane);
}

void Camera::use_world()
{
	unsigned int uniform_loc = glGetUniformLocation(shader_id, MODEL_MAT_UNIFORM);
	glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(model));
}

void Camera::use_view()
{
	glm::mat4 view = glm::lookAt(pos, pos + front, up_view);
	unsigned int uniform_loc = glGetUniformLocation(shader_id, VIEW_MAT_UNIFORM);
	glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::use_clip()
{
	unsigned int uniform_loc = glGetUniformLocation(shader_id, PROJECTION_MAT_UNIFORM);
	glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(clip));
}

void Camera::use()
{
	use_world();
	use_view();
	use_clip();
}

void Camera::update()
{
	delta_time.update();
}