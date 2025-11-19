#include "stages/grayscale_stage.hpp"
#include <opencv2/imgproc.hpp> // Required for cv::cvtColor

namespace ccm::stages {

core::StageResult GrayscaleStage::process(cv::Mat input) {
    if (input.empty()) return {input, false};

    // Optimization: specific check for channel count
    if (input.channels() == 1) {
        return {input, true};
    }

    cv::Mat output;
    cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
    
    return {output, true};
}

std::string GrayscaleStage::get_name() const {
    return "Grayscale Conversion";
}

} // namespace ccm::stages