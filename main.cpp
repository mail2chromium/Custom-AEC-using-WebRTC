#include "custom_acoustic_echo_canceller.h"

#include <fstream>
#include <vector>
#include <iostream>

int main() {
    // Create an instance of the echo canceller.
    webrtc::CustomAcousticEchoCanceller echo_canceller;

    // Open the near-end and far-end audio files in binary mode.
    std::ifstream nearend_file("nearend.pcm", std::ios::binary);
    std::ifstream farend_file("farend.pcm", std::ios::binary);

    if (!nearend_file.is_open() || !farend_file.is_open()) {
        std::cerr << "Error opening audio files." << std::endl;
        return -1;
    }

    // Read the far-end samples into a vector.
    std::vector<int16_t> far_end_samples(std::istreambuf_iterator<char>(farend_file), {});
    farend_file.close();

    // Process the far-end signal.
    if (!far_end_samples.empty()) {
        echo_canceller.ProcessFarEnd(far_end_samples.data());
    } else {
        std::cerr << "Far-end audio file is empty." << std::endl;
        return -1;
    }

    // Read the near-end samples into a vector.
    std::vector<int16_t> near_end_samples(std::istreambuf_iterator<char>(nearend_file), {});
    nearend_file.close();

    // Process the near-end signal.
    if (!near_end_samples.empty()) {
        echo_canceller.ProcessNearEnd(near_end_samples.data());
    } else {
        std::cerr << "Near-end audio file is empty." << std::endl;
        return -1;
    }

    // Write the processed near-end samples back to a file.
    std::ofstream processed_nearend_file("processed_nearend.pcm", std::ios::binary);
    if (!processed_nearend_file.is_open()) {
        std::cerr << "Error opening processed audio file for writing." << std::endl;
        return -1;
    }

    processed_nearend_file.write(reinterpret_cast<const char*>(near_end_samples.data()), near_end_samples.size() * sizeof(int16_t));
    processed_nearend_file.close();

    return 0;
}
