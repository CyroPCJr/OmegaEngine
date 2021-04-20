# Omega Engine

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

# Table of Contents
1. [About](#about)
2. [How to use](#how-to-use)
3. [Features](#features)
4. [External Libraries](#external-libraries)
5. [License](#license)
6. [Acknowledgments](#acknowledgments)

## About
Omega engine is a Custom Game Engine developed using C++17 and DirectX 11. 

The purpose to build this project to understand better how engines works under the hood to develop games.

---

## How to use it
### Prerequisite:
Visual Studio 2019

### How to use:

Creating new windows c ++ project, adding the library as reference Omega.h and using the Omega Property sheet.
#### Example:
```cpp
#include <OmegaEngine/Inc/Omega.h>
```
To use Dear ImGui API calls, it is necessary to include the header in .cpp files:
#### Example:
```cpp
#include <ImGui\Inc\imgui.h>
```
---

## Features

#### Artificial intelligence
* Implemented Agents, AIWorld and Entities, with that AIWorld can manage Agents along the world.
* Implemented `Finite-State-Machine` supporting Agents that can switching states behaviours along the AIWorld.
* Implmented pathfinding algorithms such as `Breadth-first search`, `Depth-first search`, `Dijkstra` and `A-star` allow for Agents moving along the graph.
* Implemented Steering behaviors module so that can help agents to move more natural and smoothly. Support behavios such as:
  * Alignment Group
  * Cohesion Group
  * Separation Group
  * Evade
  * Flee
  * Arrive
  * Seek
  * Wandering
  * Avoidance Obstacle
  * Hide

#### Core
* Implemented windows initialzaion using Win32 API.
* Implemented Memory management:
  * `Block Allocator`: Store and release a certain chunk of memory of objects avoiding memory fragmentation. 
  * `Typed Allocator`: Custom Class types that can used whitin block allocator.
  * `Handle`: Handle Pool that manages accessibility and checks the validation of Handles.
* Implemented Meta System witch is usefull to retrieve objects information in run time: Including support : `ARRAY`, `POINTER`, `CLASS`, `FIELD`

#### Graphics
* Animation: 
 * Implemented support to save and load animation keyframe using Assimp API once is extract model.
 * Implemented play animation once the file is loaded.
 * Implemented support to draw Skeletal using `SimpleDraw` with Debug UI (Dear ImGui).
* Implemented Camera witch allow to move around and oriented into the world view.
* Material: Support `Textures`, `Colors`,`LightTypes`, `Material` and `Sampler`.
* Mesh:
 * Implemented `MeshBuilder` withc allowed to rendere differents shapres such as: `Cube`,`Plane`, `Sphere`, `Quads` and `Cylinder`.
 * Implemented `VertexTypes` to cache information from `MeshBuilder`.
 * Implemented `SimpleDraw` using for visual debuging.
* Renderer:
 * Implemented `TexturesManager` to load, assign and render the textures using Direct3D as render pipeline.
 * Implemente `SpriteRendererManager` support to draw fonts and load 2D textures with position and scale.

#### Math
* Linear Algebra: Vector2, Vector3, Vector4, Matrix3, Matrix4, Quaternion and Perlin Noise.
* Geometry: AABB, OBB, Ray, Sphere, Circle, Line Segment, Rectangle and Plane.
* Implemented `EngineMath` as helper class to support all functionality such geometry intersections and helper function for linear algebra.

#### Physics
* Implmented Physics World to manage all physics particles and constraints in the scene.
* Implemented Particles system using Verlet integration.
* Constratints can be applied either fixed or spring constraints.

---

## External Libraries

* [Assimp](https://github.com/assimp/assimp) used to import 3D models
* [Dear ImGui](https://github.com/ocornut/imgui) used for Debug UI
* [DirectXTK](https://github.com/microsoft/DirectXTK) DirectX Tool Kit for DirectX 11
* [FW1FontWrapper](https://github.com/gamelaster/FW1FontWrapper) used to render Fonts using Direct3D 11
* [RapidJson](https://github.com/Tencent/rapidjson/) used to serialize and deserilize Json files

---

## License

- Copyright(c) 2021 CyroPCJr <a href="https://github.com/CyroPCJr/OmegaEngine/blob/main/LICENSE" target="_blank">LICENSE.md</a>.

---

## Acknowledgments
* Peter Chan
