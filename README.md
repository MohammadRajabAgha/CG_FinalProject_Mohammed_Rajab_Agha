# Computer Graphics Final Project — 3D Maze

A university final project developed for the **Computer Graphics** course using **C++ and Modern OpenGL 3.3**.

The project was created as an academic application of the computer graphics concepts covered during the course. It implements a simple interactive 3D maze environment to demonstrate concepts such as 3D transformations, camera movement, texture mapping, shaders, keyboard interaction, and collision detection.

> **Note:** This is an academic Computer Graphics project and is not intended to represent professional game development experience.

## 📌 Project Overview

The project provides a simple 3D maze environment where the user can control a player and interact with objects within the scene.

The main purpose of the project is to apply fundamental **Computer Graphics** concepts in a practical implementation rather than to build a production-level game.

## ✨ Implemented Features

* 3D maze environment
* Interactive player movement
* Third-person camera
* Camera rotation
* Keyboard-based interaction
* Texture mapping
* Vertex and Fragment Shaders
* Perspective projection
* Depth testing
* AABB-based collision detection
* Dynamic target generation
* Simple scoring system
* Boundary detection

## 🎮 Controls

| Key | Action              |
| --- | ------------------- |
| `W` | Move Forward        |
| `S` | Move Backward       |
| `A` | Move Left           |
| `D` | Move Right          |
| `Q` | Rotate Camera Left  |
| `E` | Rotate Camera Right |

## 🧠 Computer Graphics Concepts Applied

### 3D Transformations

The project applies transformation matrices for:

* Translation
* Scaling
* Model transformations
* View transformations
* Perspective projection

### Camera

A third-person camera system is implemented to follow the player and rotate around the scene.

The camera position is calculated using the player's position and trigonometric functions to achieve the required rotation behavior.

### Collision Detection

**AABB (Axis-Aligned Bounding Box)** collision detection is used to detect intersections between the player and maze walls.

The collision logic helps prevent the player from passing through obstacles.

### Texture Mapping

Textures are loaded and mapped onto objects in the scene using `stb_image`.

### Shaders

The rendering process uses GLSL shaders:

* **Vertex Shader** — processes vertex transformations.
* **Fragment Shader** — handles the final pixel/texture output.

### OpenGL Rendering

The project uses the Modern OpenGL pipeline with:

* Vertex Buffers
* Vertex Attributes
* VAOs/VBOs
* Model/View/Projection matrices
* Depth testing
* Texture sampling

## 🛠️ Technologies & Libraries

* **C++**
* **Modern OpenGL 3.3**
* **GLSL**
* **GLFW**
* **GLEW**
* **GLM**
* **stb_image**
* **Visual Studio**

## 🎓 Academic Context

**Course:** Computer Graphics
**Project Type:** University Final Project
**Programming Language:** C++
**Graphics API:** Modern OpenGL 3.3

The project was developed to demonstrate practical understanding of the fundamental concepts taught in the Computer Graphics course.

## 📚 Learning Objectives

Through this project, I practiced:

* Understanding the OpenGL rendering pipeline
* Working with 3D coordinate systems
* Applying transformation matrices
* Implementing camera movement
* Working with textures
* Writing basic GLSL shaders
* Handling keyboard input
* Implementing basic collision detection
* Combining multiple graphics concepts into an interactive scene

## 🚀 Running the Project

### Requirements

* Windows
* Visual Studio
* OpenGL 3.3 compatible graphics support

### Steps

1. Clone the repository:

```bash
git clone https://github.com/MohammedMahmoudRajabAgha/CG_FinalProject_Mohammed_Rajab_Agha.git
```

2. Open the Visual Studio solution.

3. Build the project.

4. Run the application.

## 🔮 Possible Future Improvements

As an academic project, the implementation can be extended with additional Computer Graphics concepts such as:

* Lighting
* Shadows
* More advanced 3D models
* Improved rendering techniques
* More complex environments
* Additional visual effects

## 👨‍💻 Author

**Mohammed Mahmoud Rajab Agha**

Software Engineering Student

GitHub:
https://github.com/MohammedMahmoudRajabAgha

---

**Academic project developed for learning and applying Computer Graphics concepts using C++ and Modern OpenGL.**
