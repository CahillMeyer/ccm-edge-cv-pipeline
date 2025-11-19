#pragma once
#include "core/ipipeline_stage.hpp"

namespace ccm::stages {

class GrayscaleStage : public core::IPipelineStage {
public:
    // We just declare the overrides here
    core::StageResult process(cv::Mat input) override;
    std::string get_name() const override;
};

} // namespace ccm::stages