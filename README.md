# Omega Engine

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

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

#### AI
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

#### Input
#### Math
#### Physics

---

## External Libraries

* [Assimp](https://github.com/assimp/assimp) used to import 3D models
* [Dear Imgui](https://github.com/ocornut/imgui) used for Debug UI
* [DirectXTK](https://github.com/microsoft/DirectXTK) DirectX Tool Kit for DirectX 11
* [FW1FontWrapper](https://github.com/gamelaster/FW1FontWrapper) used to render Fonts using Direct3D 11
* [RapidJson](https://github.com/Tencent/rapidjson/) used to serialize and deserilize Json files

---

## License

- Copyright(c) 2021 CyroPCJr <a href="https://github.com/CyroPCJr/OmegaEngine/blob/main/LICENSE" target="_blank">LICENSE.md</a>.

---

## Acknowledgments
* Peter Chan
