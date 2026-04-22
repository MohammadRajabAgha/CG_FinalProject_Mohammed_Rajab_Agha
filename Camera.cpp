#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Camera.h"

Camera::Camera(){

	CameraPosition = glm::vec3(0, 0, 0); // start at origin
	FrontPosition = glm::vec3(0, 0, -1); // looking toward -Z by default
	WorldUp = glm::vec3(0, 1, 0);        // Y axis is up
	yaw = -90;                           // makes initial direction = -Z
	deltaTime = 0.016;                   // ~60 FPS
}

void Camera::UpdateCameraFront(){
	glm::vec3 targetVector;

	// compute forward direction using yaw (rotation around Y axis)
	targetVector.x = cos(glm::radians(yaw));
	targetVector.y = 0; // no pitch (no up/down looking)
	targetVector.z = glm::sin(glm::radians(yaw));

	FrontPosition = targetVector; // update direction
}

void Camera::TurnRight(){
	yaw += 2 * deltaTime; // increase yaw
	UpdateCameraFront();  // update direction
}

void Camera::TurnLeft(){
	yaw -= 2 * deltaTime; // decrease yaw
	UpdateCameraFront();  // update direction
}

void Camera::MoveForward(float speed){
	// move forward in the Front direction
	CameraPosition += FrontPosition * speed * deltaTime;
}

void Camera::MoveBackward(float speed){
	// move backward (opposite of Front)
	CameraPosition -= FrontPosition * speed * deltaTime;
}

glm::mat4 Camera::GetViewMatrix(){
	// build view matrix using lookAt
	return glm::lookAt(
		CameraPosition,                  // camera position
		CameraPosition + FrontPosition, // target (where we look)
		WorldUp                         // up direction
		);
}