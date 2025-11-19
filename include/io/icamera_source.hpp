#pragma once
#include <opencv2/core.hpp>
#include <optional>
#include <string>

namespace ccm::io {

/// @brief Configuration parameters for camera initialization.
struct CameraConfig {
    int device_id = 0;
    int width = 640;
    int height = 480;
    double fps = 30.0;
    std::string name = "Camera";
};

/// @brief Abstract interface for video capture backends.
///
/// Implementations may use OpenCV (cv::VideoCapture), GStreamer, or V4L2 directly.
class ICameraSource {
public:
    virtual ~ICameraSource() = default;

    /// @brief Initialize the hardware connection.
    /// @param config The requested camera configuration.
    /// @return True if the camera was successfully opened.
    [[nodiscard]] virtual bool open(const CameraConfig& config) = 0;

    /// @brief Release hardware resources.
    virtual void close() = 0;

    /// @brief Capture a single frame.
    /// @return std::optional containing the frame, or std::nullopt if capture failed/timed out.
    ///
    /// Using std::optional avoids the risk of returning empty cv::Mat objects
    /// that might cause crashes if unchecked.
    [[nodiscard]] virtual std::optional<cv::Mat> capture() = 0;

    // --- Hardware Info ---
    // Get actual hardware parameters (might differ from requested config)
    [[nodiscard]] virtual double get_fps() const = 0;
    [[nodiscard]] virtual std::string get_name() const = 0;
    [[nodiscard]] virtual bool is_opened() const = 0;
};

} // namespace ccm::io