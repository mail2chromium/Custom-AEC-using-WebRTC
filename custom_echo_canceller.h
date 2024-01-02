#ifndef CUSTOM_ACOUSTIC_ECHO_CANCELLER_H_
#define CUSTOM_ACOUSTIC_ECHO_CANCELLER_H_

#include <cstdint>

namespace webrtc {

// CustomAcousticEchoCanceller provides a customizable interface for acoustic echo
// cancellation processing on audio signals, based on WebRTC's AEC3 algorithm.
class CustomAcousticEchoCanceller {
 public:
  CustomAcousticEchoCanceller();
  ~CustomAcousticEchoCanceller();

  // Processes the near-end audio signal with echo cancellation.
  // The unprocessed near-end signal is modified in-place to contain the processed signal.
  void ProcessNearEnd(int16_t* near_end_signal);

  // Processes the far-end audio signal to prepare it for echo cancellation
  // in subsequent near-end processing.
  void ProcessFarEnd(int16_t* far_end_signal);
};

}  // namespace webrtc

#endif  // CUSTOM_ACOUSTIC_ECHO_CANCELLER_H_
