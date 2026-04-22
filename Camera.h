#include<GLM/glm.hpp>

class Camera{

public:
	Camera(); // constructor

	glm::vec3 CameraPosition; // camera position in world space
	glm::vec3 FrontPosition;  // forward direction (where the camera looks)
	glm::vec3 WorldUp;        // global up direction (usually Y axis)

	glm::mat4 GetViewMatrix(); // returns the view matrix

	float yaw;        // rotation around Y axis (horizontal rotation)
	float deltaTime;  // frame time (used to make movement frame-independent)

	void UpdateCameraFront(); // updates Front vector based on yaw
	void TurnRight();         // rotate camera to the right
	void TurnLeft();          // rotate camera to the left
	void MoveForward(float speed);  // move forward
	void MoveBackward(float speed); // move backward
};