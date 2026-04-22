#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//koko
#include <windows.h>
#include "Camera.h"
#include<vector>
#include <ctime>
#include <iostream>

float angle;
// =======================================================
// 🔷 Shader Sources
// =======================================================

float angleY = 0.0f;
int score = 0;
glm::vec3 goalPos = glm::vec3(0, 0, -8);
float goalCooldown = 0.0f;
//bool reachedGoal = false;


// Vertex Shader
const char* VertexShaderCode = R"(
#version 330 core
layout(location = 0) in vec3 apos;     // Vertex position
layout(location = 1) in vec3 aColor;   // Vertex color
layout(location = 2) in vec2 aTex;     // Texture coordinates

out vec3 vertexcolor;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(apos, 1.0);
    vertexcolor = aColor;
    texCoord = aTex;
}
)";

// Fragment Shader
const char* FragmentShaderCode = R"(
#version 330 core
in vec3 vertexcolor;
in vec2 texCoord;

out vec4 fragmentcolor;

uniform sampler2D tex0;   // Texture sampler

void main()
{
    fragmentcolor = texture(tex0, texCoord);
}
)";

//koko
Camera camera;
float speed = 3.0f;


// =======================================================
// 🔷 Main Function
// =======================================================

//koko3

glm::vec3 playerPos = glm::vec3(0.0f, 0.0f, 0.0f);
float playerSpeed = 3.0f;


//koko4
//دالة التصادم
//AABB Collision (Axis-Aligned Bounding Box) -->لأننا نقارن حدود مربعات (Box vs Box)

GLuint LoadTexture(const char* path)
{
	stbi_set_flip_vertically_on_load(true); // 👈 الحل

	int w, h, c;
	unsigned char* data = stbi_load(path, &w, &h, &c, 0);

	if (!data)
	{
		std::cout << "Failed to load texture: " << path << std::endl;
		return 0;
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	GLuint format = (c == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return tex;
}
bool checkCollision(glm::vec3 player, glm::vec3 wall)
{
	float playerHalf = 0.25f;   // أصغر شوي
	float wallHalf = 0.3f;      // لأن scale = 1

	bool collisionX = abs(player.x - wall.x) < (playerHalf + wallHalf);
	bool collisionZ = abs(player.z - wall.z) < (playerHalf + wallHalf);

	return collisionX && collisionZ;
}


int main()
{
	srand(time(NULL));


	// ===================================================
	// 1️⃣ Initialize GLFW
	// ===================================================
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";
		return -1;
	}

	// Request OpenGL 3.3 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ===================================================
	// 2️⃣ Create Window
	// ===================================================
	GLFWwindow* window = glfwCreateWindow(800, 600, "Texture Example", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//koko
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	// ===================================================
	// 3️⃣ Initialize GLEW
	// ===================================================
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW\n";
		return -1;
	}

	// ===================================================
	// 4️⃣ Vertex Data (Position + Color + Texture UV)
	// ===================================================
	GLfloat vertices[] = {
		// Position                  // Color               // UV
		-0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.3f, 0.0f, 0.0f,//0
		0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 0.0f,//1
		-0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.0f, 1.0f,//2
		0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 1.0f, 1.0f,//3
		0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.0f, 1.0f,//4
		0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.0f, 0.0f,//5
		-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 1.0f, 1.0f,//6
		-0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.3f, 1.0f, 0.0f,//7
	};

	GLuint indices[] = {
		// Front face (z = 0)
		0, 1, 2,
		1, 3, 2,

		// Back face (z = -0.5)
		4, 6, 5,
		5, 6, 7,

		// Left face
		0, 2, 7,
		2, 6, 7,

		// Right face
		1, 5, 3,
		3, 5, 4,

		// Top face
		2, 3, 6,
		3, 4, 6,

		// Bottom face
		0, 7, 1,
		1, 7, 5
	};

	// ===================================================
	// 5️⃣ Create Shaders
	// ===================================================
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &VertexShaderCode, nullptr);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &FragmentShaderCode, nullptr);
	glCompileShader(fs);

	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// ===================================================
	// 6️⃣ Create VAO, VBO, EBO
	// ===================================================
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	GLuint texturePlayer, textureWall, textureGoal;

	// ===================================================
	// 7️⃣ Load Image using stb_image
	// ===================================================
	texturePlayer = LoadTexture("player.png");
	textureWall = LoadTexture("wall.png");
	textureGoal = LoadTexture("goal.png");

	// ===================================================
	// 8️⃣ Create Texture
	// ===================================================
	/*GLuint texture;*/

	//koko8
	

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//koko8

	//// Determine format
	//GLuint format = (channels == 4) ? GL_RGBA : GL_RGB;

	//// Upload texture
	//glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	//// Generate mipmaps
	//glGenerateMipmap(GL_TEXTURE_2D);

	//// Free image from RAM
	//stbi_image_free(data);

	// ===================================================
	// 9️⃣ Connect Texture to Shader
	// ===================================================
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "tex0"), 0);

	//koko2
	std::vector<glm::vec3> walls = {
	{0,0,-5},
	{2,0,-5},
	{-2,0,-5},
	{4,0,-5},
	{-4,0,-5},

	{4,0,-3},
	{4,0,-1},

	{-4,0,-3},
	{-4,0,-1}
	};


	// ===================================================
	// 🔁 Render Loop
	// ===================================================
	while (!glfwWindowShouldClose(window))
	{

//koko
  // =======================
     // 🎮 Input Handling
     // =======================
	

	//koko3
		// =======================
// 🎮 Player Movement
// =======================
		// حركة اللاعب فقط

		//koko4

		glm::vec3 newPos = playerPos;

		//koko9

		glm::vec3 forward = glm::normalize(glm::vec3(camera.FrontPosition.x, 0, camera.FrontPosition.z));
		glm::vec3 right = glm::normalize(glm::cross(forward, camera.WorldUp));

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			newPos += forward * playerSpeed * 0.016f;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			newPos -= forward * playerSpeed * 0.016f;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			newPos += right * playerSpeed * 0.016f;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			newPos -= right * playerSpeed * 0.016f;

		// =======================
		// 🧱 Collision Check
		// =======================
		/*bool collision = false;

		for (auto& wall : walls)
		{
			if (checkCollision(newPos, wall))
			{
				collision = true;
				break;
			}
		}

		if (!collision)
		{
			playerPos = newPos;
		}*/

		////glm::vec3 newPos = playerPos;
		
	
		//koko5

	// حركة X
		glm::vec3 testX = playerPos;
		testX.x = newPos.x;

		bool collisionX = false;
		for (auto& wall : walls)
		{
			if (checkCollision(testX, wall))
			{
				collisionX = true;
				break;
			}
		}

		if (!collisionX)
			playerPos.x = testX.x;

		// حركة Z
		glm::vec3 testZ = playerPos;
		testZ.z = newPos.z;

		bool collisionZ = false;
		for (auto& wall : walls)
		{
			if (checkCollision(testZ, wall))
			{
				collisionZ = true;
				break;
			}
		}

		if (!collisionZ)
			playerPos.z = testZ.z;

//

		



		//koko3قبل حساب الـ  view
		/*camera.CameraPosition = playerPos + glm::vec3(0, 2, 5);
		camera.FrontPosition = glm::normalize(playerPos - camera.CameraPosition);*/


		//koko5

		

		/*if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			angleY += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			angleY -= 0.02f;*/

		//koko6

		float cameraSpeed = 1.5f;

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			angleY += cameraSpeed * 0.016f;

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			angleY -= cameraSpeed * 0.016f;


		glm::vec3 offset = glm::vec3(
			sin(angleY) * 5,
			2,
			cos(angleY) * 5
		);

		camera.CameraPosition = playerPos + offset;
		camera.FrontPosition = glm::normalize(playerPos - camera.CameraPosition);


		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);


		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		GLuint modelLoc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		//koko8

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureGoal);

		// =======================
// 🟫 Goal
// =======================

		//koko5

		/*glm::vec3 goalPos = glm::vec3(0, 0, -8);*/

		glm::mat4 goal = glm::mat4(1.0f);
		goal = glm::translate(goal, goalPos);
		goal = glm::scale(goal, glm::vec3(0.3f, 1.2f, 0.3f));

		glUseProgram(program);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(goal));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); //ِAddition 


		

		////glm::mat4 goal = glm::mat4(1.0f);
		//goal = glm::translate(goal, goalPos);
		//goal = glm::scale(goal, glm::vec3(0.5f));

		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(goal));
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		////koko5
		//if (checkCollision(playerPos, goalPos))
		//{
		//	std::cout << "You Win!" << std::endl;
		//}

		////koko6

		//if (checkCollision(playerPos, goalPos) && !reachedGoal)
		//{
		//	score += 10;
		//	reachedGoal = true;

		//	Beep(1000, 200);

		//	std::cout << "Score: " << score << std::endl;

		//	//koko6
		//	// توليد موقع جديد
		//	goalPos = glm::vec3(
		//		(rand() % 10) - 5,
		//		0,
		//		-(rand() % 10)
		//	);
		//}


		////koko7
		//if (goalCooldown > 0.0f)
		//	goalCooldown -= 0.016f;

		//koko8

		float deltaTime = 0.016f; // لاحقًا احسبه صح
		goalCooldown -= deltaTime;

		////koko9

		//float currentTime = glfwGetTime();
		//float deltaTime = currentTime - lastTime;
		//lastTime = currentTime;


		
		//koko11

		if (checkCollision(playerPos, goalPos) && goalCooldown <= 0.0f)
		{
			score += 10;
			Beep(1000, 200);

			std::cout << "Score: " << score << std::endl;

			bool valid = false;

			while (!valid)
			{
				glm::vec3 newGoal = glm::vec3(
					(rand() % 10) - 5,
					0,
					(rand() % 10) - 5
				);

				valid = true;

				for (auto& wall : walls)
				{
					if (checkCollision(newGoal, wall))
					{
						valid = false;
						break;
					}
				}

				if (valid)
					goalPos = newGoal;
			}

			goalCooldown = 0.5f;
		}
		

			goalCooldown = 0.5f; // نصف ثانية منع تكرار
		}

		//
		GLuint viewLoc = glGetUniformLocation(program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLuint projLoc = glGetUniformLocation(program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUseProgram(program);

		//koko7

		//// Bind texture before drawing
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);

		
		
		

		//koko2
	// =======================
// 🟫 Ground
// =======================
		glm::mat4 ground = glm::mat4(1.0f);
		ground = glm::translate(ground, glm::vec3(0.0f, -1.0f, 0.0f));
		ground = glm::scale(ground, glm::vec3(20.0f, 1.0f, 20.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ground));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



		//koko8
		glBindTexture(GL_TEXTURE_2D, texturePlayer);

		//koko3

		// =======================
// 🟥 Player
// =======================
		glm::mat4 player = glm::mat4(1.0f);
		player = glm::translate(player, playerPos);
		player = glm::scale(player, glm::vec3(0.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(player));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		

		
		//
		//koko2

		// =======================
// 🧱 Walls
// =======================

		//koko8
		glBindTexture(GL_TEXTURE_2D, textureWall);

		for (auto& pos : walls)
		{
			glm::mat4 wall = glm::mat4(1.0f);
			wall = glm::translate(wall, pos);
			wall = glm::scale(wall, glm::vec3(1.0f, 2.0f, 1.0f));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(wall));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ===================================================
	// 🧹 Cleanup
	// ===================================================
	glfwTerminate();
	return 0;
}
