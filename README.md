# LibMath

A C++ math library for game development, written from scratch as a solo school project over two years. 
It provides vectors, matrices, quaternions, 2D/3D geometric primitives and collision tests, and 
is used as the math foundation of all my other projects (software rasterizer, 3D game engine, animation programming).

---

## Table of Contents

- [Overview](#overview)
- [Core Features](#core-features)
- [Usage](#usage)
- [Collisions](#collisions)
- [Unit Tests](#unit-tests)
- [Implementation Highlights](#implementation-highlights)
- [Development History](#development-history)
- [Tech Stack](#tech-stack)
- [Build](#build)

---

## Overview

LibMath translates the formulas learned in math classes into code that is usable in a video game project, 
while building an intuition for their performance cost. It is split into two CMake targets:

- **LibMath**: the library itself, exposed under the `LibMath` namespace
- **UnitTest**: an application that tests the library exhaustively

The library has no external dependency: only `<cmath>`, `<climits>`, `<cfloat>` and compiler intrinsics are allowed. 
It compiles in Debug and Release with `/Wall /WX` (all warnings treated as errors).

## Core Features

- **Angle conversion** between degrees and radians
- **Vectors**: `Vector2`, `Vector3`, `Vector4`
  - Constructors, accessors, `operator[]`, comparison, arithmetic operators
  - Dot product, cross product, magnitude, normalization, homogenization (4D)
  - Angle between vectors, projection, reflection, `lerp`
- **Matrices**: 2x2, 3x3 and 4x4
  - Determinant, minors, cofactors, adjugate, transpose, inverse
  - Matrix x matrix, matrix x vector and matrix x scalar products
  - Factory functions: identity, translation, rotation (X / Y / Z or around a center), scale, full transform, perspective projection
- **Quaternions**
  - Axis-angle construction, conjugate, inverse, normalization
  - Vector rotation, conversion to matrix, angle between quaternions
  - `slerp`
- **2D geometry**: `Point2D`, `Line2D`, `Rectangle`, `Circle`
- **3D geometry**: `Point3D`, `Line3D` (ray), `Plane`, `Prism`, `Sphere`, `Capsule`
- **Collision detection** in 2D and 3D (see below)

## Usage

```cpp
#include <LibMath/Vector/Vector3.h>
#include <LibMath/Matrix/Matrix4.h>

using namespace LibMath;

Vector3 direction(1.f, 2.f, 3.f);
direction.normalize();

Matrix4 transform = Matrix4::createTransform(
    Vector3(0.f, 1.f, 0.f),   // translation
    Vector3(0.f, 1.f, 0.f),   // axis
    Degree(90.f),             // angle
    Vector3(1.f));            // scale
```

## Collisions

| 2D | Point | Line | Rectangle | Circle | 
|---|:-:|:-:|:-:|:-:|
| **Point** | | X | X | X |
| **Line** | | X | X | X |
| **Rectangle** | | | X | |
| **Circle** | | | | X |

| 3D | Point | Ray | Plane | Sphere | Capsule | Prism |
|---|:-:|:-:|:-:|:-:|:-:|:-:|
| **Point** | | | | X | X | X |
| **Ray** | | | X | X | X | X |
| **Plane** | | | X | X | X | |
| **Sphere** | | | | X | X | |
| **Capsule** | | | | | X | X |

## Unit Tests

The `UnitTest` application covers every function of the library: constructors, operators, math operations, geometry accessors and collisions. 
The library must pass every test before each tagged delivery.

Floating-point comparisons use a tolerance-based comparison rather than `==`, as recommended for IEEE-754 floats.

## Implementation Highlights

- **No dependencies**: pure C++ with the standard math header only
- **Warning-free**: builds with `/Wall /WX` in Debug and Release. Three purely informational
  MSVC warnings that `/Wall` enables are suppressed with `/wd`:
  - `C4514`: unreferenced inline function removed
  - `C5045`: compiler inserted Spectre mitigation (informational)
  - `C4464`: relative include path contains `..` (used for the library's include layout)
- **Float-safe comparisons**: combined absolute and relative tolerance for equality checks, including comparisons around zero
- **Clean structs**: structs only hold data, constructors, accessors and overloaded operators
- **Quaternion rotations**: rotation uses quaternions rather than Euler angles, and `slerp` gives mathematically correct interpolation
- **Reusable**: designed as a standalone dependency for every later project (rasterizer, platformer engine, skeletal animation)

## Development History

The library grew with the school year, with one git tag per delivery:

| Tag | Content |
|---|---|
| `Algorithmie` | Angle conversion, 2D vectors, 2D matrices, 2D geometry and collisions |
| `Rasterizer` | 3D and 4D vectors, 3D matrices (3x3, 4x4) |
| `Platformer` | 3D geometry and 3D collisions |
| `Animation` | Quaternions |

## Tech Stack

Written in C++ on Windows, built with CMake.

| Purpose | Library |
|---|---|
| Math functions | C++ standard library (`<cmath>`) |
| Build system | CMake |

No third-party library is used.

## Build

The project uses **CMake**.

### Requirements

- Windows
- [CMake](https://cmake.org/) 3.24 or newer
- Visual Studio 2022 (MSVC)

### 1. Configure and build

```bash
git clone https://github.com/Potatoes251/LibMath.git
cd LibMath

cmake -S . -B build
cmake --build build --config Release
```

### 2. Run the tests

```bash
build/Release/UnitTest.exe
```

(For a Debug build, use `--config Debug` and run from `build/Debug/`.)

### 3. Use it in your own project

Add the repository as a subdirectory and link the `LibMath` target:

```cmake
add_subdirectory(LibMath)
target_link_libraries(MyProject PRIVATE LibMath)
```

### Notes
- Both Debug and Release build with `/Wall /WX`, minus the three suppressed warnings
  listed in [Implementation Highlights](#implementation-highlights).
- Build outputs (`build/`, `.exe`, `.obj`, `.vs/`) are excluded from the repository via `.gitignore`.
