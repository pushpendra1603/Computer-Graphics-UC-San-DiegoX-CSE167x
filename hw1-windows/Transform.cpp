// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <iostream>
#include <string>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis0) {
  // YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(axis0);
	float rad = glm::radians(degrees);
	float costheta = glm::cos(rad);
	float sintheta = glm::sin(rad);
	mat3 I(1.0);
	mat3 aat = mat3(axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
		axis.y * axis.x, axis.y * axis.y, axis.y * axis.z,
		axis.z * axis.x, axis.z * axis.y, axis.y * axis.z);
	mat3 astar = mat3(0, axis.z, -axis.y,
		-axis.z, 0, axis.x,
		axis.y, -axis.x, 0);
  return (costheta * I) + ((1 - costheta) * aat) + (sintheta * astar);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	vec3 rotationAxis = vec3(0, 1, 0);
	rotationAxis = vec3(up);
	mat3 rotationAmount = rotate(degrees, rotationAxis);
	eye = eye * rotationAmount;
	up = glm::normalize(up * rotationAmount);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 rotationAxis = vec3(1, 0, 0);
	rotationAxis = glm::normalize(glm::cross(eye, up));
	mat3 rotationAmount = rotate(degrees, rotationAxis);
	eye = rotationAmount * eye;
	up = glm::normalize(rotationAmount * up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HEREs
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(glm::normalize(up), w));
	vec3 v = glm::cross(w, u);
	// You will change this return call
	return mat4(
		u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		-u.x * eye.x - u.y * eye.y - u.z * eye.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z, 1);
  // You will change this return call
}

Transform::Transform()
{

}

Transform::~Transform()
{

}