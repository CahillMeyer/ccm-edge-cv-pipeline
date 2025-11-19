#include "io/opencv_camera.hpp"
#include "core/config_loader.hpp"
#include "stages/grayscale_stage.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <atomic>
#include <csignal>
#include <map>
#include <functional>

using namespace ccm;

// Global atomic flag for thread-safety
std::atomic<bool> g_running{true};

void signal_handler(int signum) {
    std::cout << "\n[Info] Interrupt signal (" << signum << ") received. Stopping..." << std::endl;
    g_running = false;
}

// Maps string names (from YAML) to stage constructors
using StageCreator = std::function<std::unique_ptr<core::IPipelineStage>()>;

std::unique_ptr<core::IPipelineStage> create_stage(const std::string& name) {
    static const std::map<std::string, StageCreator> factory = {
        { "grayscale", []() { return std::make_unique<stages::GrayscaleStage>(); } }
        // Future: { "blur", []() { return std::make_unique<stages::BlurStage>(); } }
    };

    auto it = factory.find(name);
    if (it != factory.end()) {
        return it->second();
    }
    std::cerr << "[Warn] Unknown stage type in config: " << name << std::endl;
    return nullptr;
}

int main(int argc, char** argv) {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    // 1. Load Configuration
    // Default to "config/pipeline_basic.yaml" if not provided
    std::string config_path = (argc > 1) ? argv[1] : "config/pipeline_basic.yaml";
    std::cout << "[CCM-Pipeline] Loading config from: " << config_path << std::endl;
    
    auto config = core::ConfigLoader::load_from_file(config_path);

    // 2. Initialize Hardware
    io::OpenCVCamera camera;
    if (!camera.open(config.camera)) {
        std::cerr << "[Error] Could not open camera based on config." << std::endl;
        return -1;
    }

    // 3. Build Pipeline Dynamically
    std::vector<std::unique_ptr<core::IPipelineStage>> pipeline;
    for (const auto& stage_name : config.stages) {
        auto stage = create_stage(stage_name);
        if (stage) {
            pipeline.push_back(std::move(stage));
            std::cout << "  + Added Stage: " << stage_name << std::endl;
        }
    }

    if (pipeline.empty()) {
        std::cout << "[Info] Pipeline is empty. Showing raw pass-through." << std::endl;
    }

    // 4. Main Loop
    int frame_count = 0;
    auto last_time = std::chrono::steady_clock::now();

    while (g_running) {
        auto frame_opt = camera.capture();
        if (!frame_opt) { continue; }

        cv::Mat current_frame = *frame_opt;

        // Execute Pipeline
        for (const auto& stage : pipeline) {
            auto result = stage->process(current_frame);
            if (!result.success) break;
            current_frame = result.frame;
        }

        // Visualization
        // Show raw stats every second
        frame_count++;
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - last_time).count() >= 1) {
            // Reset counter
            frame_count = 0;
            last_time = now;
        }

        cv::imshow("CCM Edge Pipeline", current_frame);
        if (cv::waitKey(1) == 27) g_running = false;
    }

    return 0;
}