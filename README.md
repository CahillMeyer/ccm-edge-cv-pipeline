# ccm-edge-cv-pipeline

Modular C++ computer vision pipeline for **edge devices**
(Jetson, Raspberry Pi, x86 Linux).

> Demonstrates how to build a real-time camera pipeline using C++,
> OpenCV, and GStreamer/V4L2 with a focus on performance, structure, and testability.

---

## Goals

This repository is a **reference implementation** for:

- Capturing frames from USB / CSI cameras on Linux (Jetson, Pi, x86).
- Building a **modular processing pipeline** in C++.
- Integrating **OpenCV** and optional DNN backends.
- Measuring **latency and throughput** under realistic conditions.

---

## Features (planned)

- ✅ **CMake-based Architecture**: Modular library/executable separation.
- ✅ **Hardware Abstraction**: `ICameraSource` interface for easy sensor swapping.
- ✅ **Config-Driven**: YAML-based pipeline construction at runtime.
- ✅ **Robust IO**: MJPEG optimizations for WSL/USB bandwidth constraints.
- ⏳ **Metrics**: FPS + timing metrics (Coming in Phase 5).
- ⏳ **Inference**: Optional ONNX/TensorRT support.

---

## Tech Stack

- **Language:** C++17
- **Libraries:** OpenCV, fmt, spdlog
- **Platforms:** Ubuntu, Jetson, Raspberry Pi
- **Build system:** CMake

---

## Repository Layout (planned)

```
src/
  core/
    frame_queue.hpp
    pipeline.hpp
  io/
    camera_capture.cpp
    camera_capture.hpp
  stages/
    grayscale_stage.cpp
    blur_stage.cpp
    motion_stage.cpp
  app/
    main.cpp
include/
config/
  pipeline_example.yaml
docs/
  architecture.md
  performance.md
tests/
CMakeLists.txt
```

---

## Minimal Example

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) { std::cerr << "Failed to open camera"; return 1; }

    cv::Mat frame, gray;
    while (cap.read(frame)) {
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::imshow("edge-cv-pipeline", gray);
        if (cv::waitKey(1) == 27) break;
    }
    return 0;
}
```

---

## Build Instructions

```
sudo apt-get install build-essential cmake libopencv-dev
git clone https://github.com/CahillMeyer/ccm-edge-cv-pipeline.git
cd ccm-edge-cv-pipeline
mkdir build && cd build
cmake ..
make -j$(nproc)
```

---

## Roadmap

- [ ] OpenCV capture demo
- [ ] Config-driven pipeline graph
- [ ] Per-stage performance metrics
- [ ] ONNX/TensorRT support
- [ ] Simple object detection overlay
- [ ] Jetson Dockerfile

---

## License  
MIT License

---

## Contact  
**Cahill Meyer** – Embedded Vision & Edge AI Engineer  
GitHub: https://github.com/CahillMeyer
