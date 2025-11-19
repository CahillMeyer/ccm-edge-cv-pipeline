#pragma once
#include <chrono>
#include <string>
#include <iostream>

namespace ccm::core {

class PerfTimer {
public:
    explicit PerfTimer(const std::string& name) 
        : m_name(name), m_start(std::chrono::high_resolution_clock::now()) {}

    ~PerfTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count();
        
        double ms = static_cast<double>(duration_us) / 1000.0;

        std::cout << "[Perf] " << m_name << ": " << ms << " ms" << std::endl;
    }

    PerfTimer(const PerfTimer&) = delete;
    PerfTimer& operator=(const PerfTimer&) = delete;

private:
    std::string m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

} // namespace ccm::core