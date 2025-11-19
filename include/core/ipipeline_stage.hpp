#pragma once
#include <opencv2/core.hpp>
#include <string>

namespace ccm::core {

/// @brief The result of a single pipeline stage's processing.
///
/// Contains the processed frame and a control flag. If `success` is false,
/// the pipeline may choose to abort further processing for this frame
/// (e.g., if an object detector found nothing of interest).
struct StageResult {
    cv::Mat frame;
    bool success = true;
};

/// @brief Interface for all image processing modules.
///
/// Stages are the building blocks of the pipeline. They can be
/// loaded dynamically based on the YAML configuration.
class IPipelineStage {
public:
    virtual ~IPipelineStage() = default;

    /// @brief Core processing logic.
    /// @param input The input frame (passed by value/ref depending on OpenCV optimization).
    /// @return StageResult containing the output frame and status.
    [[nodiscard]] virtual StageResult process(cv::Mat input) = 0;

    /// @brief Get the display name of the stage for profiling/debugging.
    /// @return String name of the stage (e.g., "Grayscale", "YOLOv5").
    [[nodiscard]] virtual std::string get_name() const = 0;
};

} // namespace ccm::core