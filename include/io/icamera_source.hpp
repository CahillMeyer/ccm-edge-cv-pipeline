#pragma once
#include <opencv2/core.hpp>
#include <optional>
#include <string>

namespace ccm::io {

struct CameraConfig {
    int device_id = 0;
    int width = 640;
    int height = 480;
    double fps = 30.0;
    std::string name = "Camera";
};

class ICameraSource {
public:
    virtual ~ICameraSource() = default;

    // Initialize the hardware connection
    [[nodiscard]] virtual bool open(const CameraConfig& config) = 0;

    // Release hardware resources
    virtual void close() = 0;

    // Capture a single frame. Returns std::nullopt if failed/empty.
    // We use optional to avoid returning empty cv::Mat which is error-prone.
    [[nodiscard]] virtual std::optional<cv::Mat> capture() = 0;

    // Get actual hardware parameters (might differ from requested config)
    [[nodiscard]] virtual double get_fps() const = 0;
    [[nodiscard]] virtual std::string get_name() const = 0;
    [[nodiscard]] virtual bool is_opened() const = 0;
};

} // namespace ccm::io