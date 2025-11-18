#pragma once
#include "io/icamera_source.hpp"
#include <opencv2/videoio.hpp>
#include <memory>

namespace ccm::io {

class OpenCVCamera : public ICameraSource {
public:
    OpenCVCamera() = default;
    ~OpenCVCamera() override;

    bool open(const CameraConfig& config) override;
    void close() override;
    std::optional<cv::Mat> capture() override;

    double get_fps() const override { return m_fps; }
    std::string get_name() const override { return m_config.name; }
    bool is_opened() const override { return m_cap.isOpened(); }

private:
    cv::VideoCapture m_cap;
    CameraConfig m_config;
    double m_fps = 0.0;
};

} // namespace ccm::io