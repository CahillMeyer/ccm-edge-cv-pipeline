#include "io/opencv_camera.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <chrono>
#include <thread>

// Using the namespace for convenience in app code
using namespace ccm::io;

int main(int argc, char** argv) {
    std::cout << "[CCM-Pipeline] Initializing..." << std::endl;

    // 1. Configuration
    CameraConfig config;
    config.device_id = (argc > 1) ? std::stoi(argv[1]) : 0;
    config.width = 640;
    config.height = 480;
    config.fps = 30.0;
    config.name = "PrimaryCam";

    // 2. Instantiate Concrete Implementation (but access via Interface could be done)
    OpenCVCamera camera;

    if (!camera.open(config)) {
        return -1;
    }

    // 3. Main Loop
    int frame_count = 0;
    auto last_time = std::chrono::steady_clock::now();

    while (true) {
        // Capture using the clean optional interface
        auto frame_opt = camera.capture();
        
        if (!frame_opt) {
            std::cerr << "[Warning] Frame dropped or stream ended." << std::endl;
            // Simple retry logic or break
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        cv::Mat frame = *frame_opt;

        // --- Visualization ---
        // FPS Counter
        frame_count++;
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - last_time).count() >= 1) {
            std::cout << "[Stats] FPS: " << frame_count << std::endl;
            frame_count = 0;
            last_time = now;
        }

        cv::imshow("CCM Edge Pipeline", frame);
        if (cv::waitKey(1) == 27) break;
    }

    return 0;
}