# 3D Maze Game — Computer Graphics Final Project

A simple interactive 3D maze game developed in **C++ using Modern OpenGL 3.3** as a final project for a Computer Graphics course.

The project was created as a practical introduction to real-time 3D graphics and game development concepts, combining rendering, textures, camera movement, player interaction, collision detection, and a simple scoring system.

## 🎮 Project Overview

The player controls a character inside a 3D maze and must navigate through the environment to reach randomly generated targets.

The game includes a scoring system:

* **+10 points** when the player reaches a target.
* **-20 points** when the player moves outside the playable area.
* After collecting a target, a new target position is generated while avoiding wall collisions.
* The current score is displayed through the console.

## ✨ Features

* 3D maze environment
* Player movement and interaction
* Third-person camera system
* Camera rotation around the player
* Wall collision detection using **AABB (Axis-Aligned Bounding Box)**
* Dynamic target generation
* Score management system
* Boundary/out-of-bounds detection
* Texture mapping
* Depth testing
* Vertex and Fragment Shaders
* Perspective projection
* Keyboard-based interaction

## 🎮 Controls

| Key | Action              |
| --- | ------------------- |
| `W` | Move Forward        |
| `S` | Move Backward       |
| `A` | Move Left           |
| `D` | Move Right          |
| `Q` | Rotate Camera Left  |
| `E` | Rotate Camera Right |

## 🛠️ Technologies & Libraries

* **C++**
* **Modern OpenGL 3.3 Core Profile**
* **GLFW** — Window creation and keyboard input
* **GLEW** — OpenGL extension loading
* **GLM** — Mathematics and transformations
* **stb_image** — Texture loading
* **GLSL** — Vertex and Fragment Shaders
* **Visual Studio** — Development environment

## 🧠 Computer Graphics Concepts

This project applies several fundamental Computer Graphics concepts:

### 3D Transformations

The project uses transformation matrices for:

* Translation
* Scaling
* Camera/view transformations
* Perspective projection

### Camera System

A custom camera system is used to follow the player and rotate around the game environment.

The camera position is calculated using trigonometric functions and the player's position, creating an orbit-style third-person view.

### Collision Detection

The project implements **AABB collision detection** to prevent the player from passing through maze walls.

Collision checks are performed separately along the X and Z axes to allow smoother movement around obstacles.

### Texture Mapping

Textures are loaded and applied to different objects in the scene, including:

* Player
* Walls
* Goal
* Ground

### Shaders

The rendering pipeline uses custom GLSL shaders:

* **Vertex Shader** — handles vertex transformation through Model, View, and Projection matrices.
* **Fragment Shader** — samples textures to produce the final object appearance.

## 🏗️ Project Structure

```text
CG_FinalProject_Mohammed_Rajab_Agha/
│
├── main.cpp
├── Camera.cpp
├── Camera.h
├── Texture.h
│
├── player.png
├── wall.png
├── goal.png
│
├── CG_Temp.sln
├── CG_Temp.vcxproj
├── CG_Temp.vcxproj.filters
│
└── README.md
```

## 🚀 How to Run

### Requirements

* Windows
* Visual Studio
* OpenGL 3.3 compatible graphics support

### Steps

1. Clone the repository:

```bash
git clone https://github.com/MohammedMahmoudRajabAgha/CG_FinalProject_Mohammed_Rajab_Agha.git
```

2. Open the solution:

```text
CG_Temp.sln
```

3. Make sure the required OpenGL libraries and project dependencies are available.

4. Build the project in Visual Studio.

5. Run the application.

## 🎯 Learning Objectives

This project was developed to strengthen practical understanding of:

* 3D graphics programming
* OpenGL rendering pipeline
* Vertex and fragment shaders
* Coordinate systems and transformations
* Camera mathematics
* Texture mapping
* Collision detection
* Real-time user input
* Basic game mechanics
* C++ programming

## 🔮 Possible Future Improvements

The project can be extended with:

* Multiple maze levels
* More advanced player movement
* Improved collision handling
* Better UI for displaying the score
* Sound effects and background music
* Timer and game-over system
* More detailed 3D models
* Lighting and shadow effects
* Improved rendering architecture

## 👨‍💻 Author

**Mohammed Mahmoud Rajab Agha**

Software Engineering Student

[GitHub](https://github.com/MohammedMahmoudRajabAgha)

---

> A learning-focused Computer Graphics project demonstrating the transition from basic OpenGL concepts to an interactive 3D environment.
