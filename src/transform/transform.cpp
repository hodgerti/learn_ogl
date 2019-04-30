/************************************
* Headers
*************************************/
#include <transform/transform.h>

/************************************
* Functions
*************************************/
/*-------------------------------------------
- Transform functions
-------------------------------------------*/
glm::vec4 _transform
(
	glm::vec4 in,
	glm::vec3 trans
)
{
	glm::mat4 trans_mat = glm::mat4(1.0f);
	trans_mat = glm::translate(trans_mat, trans);
	return trans_mat * in;
}