#pragma once
#include <opencv2/core.hpp>
#include <string>

namespace ccm::core {

// The result of a stage processing.
// Allows us to stop the pipeline if a stage fails or decides to drop a frame.
struct StageResult {
    cv::Mat frame;
    bool success = true;
};

class IPipelineStage {
public:
    virtual ~IPipelineStage() = default;

    // Core processing logic
    // Takes a frame (by value or ref) and returns the processed result
    [[nodiscard]] virtual StageResult process(cv::Mat input) = 0;

    // Metadata for profiling/debugging
    [[nodiscard]] virtual std::string get_name() const = 0;
};

} // namespace ccm::core