#pragma once
#include "io/icamera_source.hpp" // For CameraConfig struct
#include <string>
#include <vector>

namespace ccm::core {

struct PipelineConfig {
    io::CameraConfig camera;
    std::vector<std::string> stages;
};

class ConfigLoader {
public:
    static PipelineConfig load_from_file(const std::string& path);
};

} // namespace ccm::core