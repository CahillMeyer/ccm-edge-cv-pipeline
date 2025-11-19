# CCM Edge CV Pipeline
A modular, lightweight, C++ computer-vision pipeline designed for **Jetson**, **Raspberry Pi**, and general Linux systems.  
Built for **real-time processing**, **config-driven pipelines**, and **extensibility**.

## 🚀 Status Overview
This repository is under active development.  
It already includes a minimal working pipeline, and the architecture is evolving toward a fully configurable multi-stage system.

## ✔ Implemented Features (Current)

### 🎥 Basic Camera Pipeline
- OpenCV capture from USB/MIPI (index/size from config)
- Grayscale + simple processing stages
- Real-time FPS counter
- Clean separation between **app**, **core**, **I/O**, and **stages**

### 🧩 Minimal Modular Architecture
- `IPipelineStage` interface
- Simple `Pipeline`/config loading core
- First concrete stage: `GrayscaleStage`
- IO abstraction layer (`ICameraSource`) with an OpenCV-based implementation

### ⚙️ Initial YAML Configuration Support
- Configure:
  - camera index
  - resolution
  - FPS target
  - enabled stages
- YAML → pipeline construction (basic version)

### 🛠 Modern CMake Build
- CMake 3.16+
- C++17
- Targets:  
  - `edgecv_core`  
  - `edgecv_app`
- OpenCV detection + linking

## 📍 Planned Features (Roadmap)

### 🔁 Pipeline & Architecture
- Async / threaded stages
- Back-pressure system
- Frame pool allocator
- Stage-level metrics + profiling hooks

### 🧠 AI & Acceleration
- ONNX models
- TensorRT integration (Jetson)
- SIMD acceleration for common operators

### 🏗 Deployment
- Jetson-optimized Docker image
- Raspberry Pi tuned build flags

### 📦 I/O Backends
- GStreamer capture nodes
- RTSP streaming output
- Video recorder stage

## 📂 Repository Layout (Current + Planned)

```text
ccm-edge-cv-pipeline/
├── CMakeLists.txt
├── config/
│   └── pipeline_basic.yaml
├── docs/
│   └── architecture.md
├── include/
│   ├── core/
│   │   ├── config_loader.hpp
│   │   ├── ipipeline_stage.hpp
│   │   └── perf_timer.hpp
│   ├── io/
│   │   ├── icamera_source.hpp
│   │   └── opencv_camera.hpp
│   └── stages/
│       └── grayscale_stage.hpp
├── src/
│   ├── app/
│   │   └── main.cpp
│   ├── core/
│   │   └── config_loader.cpp
│   ├── io/
│   │   ├── camera_capture.hpp
│   │   └── opencv_camera.cpp
│   └── stages/
│       └── grayscale_stage.cpp
└── tests/
    └── test_frame_queue.cpp
```

> ℹ️ Some directories represent the **target architecture** and are partially implemented.

## 🧪 Example YAML Configuration

`config/pipeline_basic.yaml`:

```yaml
camera:
  index: 0
  width: 640
  height: 480
  fps: 30

pipeline:
  stages:
    - type: grayscale
```

## ▶ Building and Running

### 1. Configure
```bash
mkdir build && cd build
cmake -DEDGECV_ENABLE_TENSORRT=OFF -DEDGECV_ENABLE_PROFILING=ON ..
```

### 2. Build
```bash
cmake --build .
```

### 3. Run
```bash
./edgecv_app ../config/pipeline_basic.yaml
```

## 🏗 Architecture Overview
See full details in `docs/architecture.md`.

```text
[ Camera Capture (ICameraSource / OpenCV camera) ]
        ↓
[ Frame Queue / Capture Loop ]
        ↓
[ Pipeline (Stage Chain) ]
        ↓
[ Output (Window / File / Stream) ]
```

## 🧪 Tests

### `test_frame_queue.cpp`
- Push/pop behaviour
- Blocking wait
- Thread-safety basics

Run tests:

```bash
ctest
```

## 🔧 CI / CD

Badges:

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

## 🔗 Related Projects

### CCM ESP32 Vision Node
MCU camera streaming node for edge devices.

### CCM EdgeVision Starter Kit
Jetson/Pi YOLO & GStreamer CV starter repo.

## 👨‍💻 About CCMCode
This repository forms part of **CCMCode’s Edge Vision Suite**, a collection of modern, minimal, and production-oriented embedded CV systems.

## 📜 License
MIT License.
