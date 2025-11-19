#include "core/config_loader.hpp"
#include <yaml-cpp/yaml.h>
#include <iostream>

namespace ccm::core {

PipelineConfig ConfigLoader::load_from_file(const std::string& path) {
    PipelineConfig config;
    
    try {
        YAML::Node root = YAML::LoadFile(path);

        // 1. Parse Camera Settings
        if (root["camera"]) {
            auto cam = root["camera"];
            config.camera.device_id = cam["id"].as<int>(0);
            config.camera.width = cam["width"].as<int>(640);
            config.camera.height = cam["height"].as<int>(480);
            config.camera.fps = cam["fps"].as<double>(30.0);
            config.camera.name = "ConfiguredCam";
        }

        // 2. Parse Pipeline Stages
        if (root["pipeline"]) {
            for (const auto& node : root["pipeline"]) {
                if (node["type"]) {
                    config.stages.push_back(node["type"].as<std::string>());
                }
            }
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "[Error] Config loading failed: " << e.what() << std::endl;
        // In a real app, we might throw or return a default
    }

    return config;
}

} // namespace ccm::core