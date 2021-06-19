// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis0) 
{
    
    mat3 ret;
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
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
    ret = (costheta * I) + ((1 - costheta) * aat) + (sintheta * astar);
    return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    vec3 rotationAxis = vec3(0, 1, 0);
    //rotationAxis = vec3(up);
    mat3 rotationAmount = rotate(degrees, rotationAxis);
    eye = eye * rotationAmount;
    up = glm::normalize(up * rotationAmount);
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1. 
    vec3 rotationAxis = vec3(1, 0, 0);
    //rotationAxis = glm::cross(glm::normalize(eye), up);
    mat3 rotationAmount = rotate(degrees, rotationAxis);
    eye = eye * rotationAmount;
    up = glm::normalize(up * rotationAmount);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    vec3 w = glm::normalize(eye-center);
    vec3 u = glm::normalize(glm::cross(glm::normalize(up), w));
    vec3 v = glm::cross(w, u);
    ret = mat4(
                u.x, v.x, w.x, 0,
                u.y, v.y, w.y, 0,
                u.z, v.z, w.z, 0,
                -u.x * eye.x - u.y * eye.y - u.z * eye.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z, 1);
    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    float yScale = 1.0F / tan(glm::radians(fovy) * 0.5);
    float xScale = yScale / aspect;
    float range = zNear - zFar;
    float a = ((zNear + zFar) / range);
    float b = (2 * zNear * zFar) / range;
    ret = mat4(
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, a, -1,
        0, 0, b, 0);

    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    ret = mat4(
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    ret = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    );
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
