#include "io/opencv_camera.hpp"
#include <iostream> 

// TODO: Integrate spdlog for standardized logging across the pipeline.

namespace ccm::io {

OpenCVCamera::~OpenCVCamera() {
    close();
}

bool OpenCVCamera::open(const CameraConfig& config) {
    if (m_cap.isOpened()) {
        close();
    }

    m_config = config;
    
    // Open the camera (API preference can be added here, e.g., cv::CAP_V4L2)
    // For generic compatibility, we use default backend.
    if (!m_cap.open(config.device_id)) {
        std::cerr << "[Error] Failed to open camera ID: " << config.device_id << std::endl;
        return false;
    }

    // Force MJPEG to reduce USB bandwidth (Critical for WSL/usbipd)
    m_cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

    // Apply configuration
    // Note: Many USB cameras require setting resolution *before* FPS
    m_cap.set(cv::CAP_PROP_FRAME_WIDTH, static_cast<double>(config.width));
    m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, static_cast<double>(config.height));
    
    // Attempt to set FPS (hardware may ignore this or choose nearest supported)
    if (config.fps > 0) {
        m_cap.set(cv::CAP_PROP_FPS, config.fps);
    }

    // Read back actual parameters
    double actual_w = m_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double actual_h = m_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    m_fps = m_cap.get(cv::CAP_PROP_FPS);

    std::cout << "[Info] Camera Opened: " << config.name 
              << " | Res: " << actual_w << "x" << actual_h 
              << " | FPS: " << m_fps << std::endl;

    return true;
}

void OpenCVCamera::close() {
    if (m_cap.isOpened()) {
        m_cap.release();
        std::cout << "[Info] Camera Closed: " << m_config.name << std::endl;
    }
}

std::optional<cv::Mat> OpenCVCamera::capture() {
    if (!m_cap.isOpened()) {
        return std::nullopt;
    }

    cv::Mat frame;
    if (!m_cap.read(frame) || frame.empty()) {
        return std::nullopt;
    }
    return frame;
}

} // namespace ccm::io