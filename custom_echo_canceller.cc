#include "custom_acoustic_echo_canceller.h"

#include "rtc_base/logging.h"
#include "absl/types/optional.h"
#include "api/make_ref_counted.h"
#include "api/scoped_refptr.h"
#include "rtc_base/checks.h"
#include "modules/audio_processing/aec3/echo_canceller3.h"
#include "api/audio/echo_canceller3_config.h"
#include "api/audio/echo_canceller3_factory.h"


namespace webrtc {

// Anonymous namespace for private implementation details
namespace {

const char kLogTag[] = "CustomAEC";
const int kSampleRateHz = 48000;
const size_t kChannelNum = 1;

std::unique_ptr<EchoCanceller3> aec3;
std::unique_ptr<AudioBuffer> nearend_audio_buffer;
std::unique_ptr<AudioBuffer> farend_audio_buffer;
std::unique_ptr<AudioBuffer> aec_linear_audio;
int16_t farend_processed_data[480]; // Assuming a 10ms frame at 48kHz.

}  // namespace


CustomAcousticEchoCanceller::CustomAcousticEchoCanceller() {

    //  webrtc::EchoCanceller3Config config;
    EchoCanceller3Config config;
    config.filter.export_linear_aec_output = true;

    // webrtc::EchoCanceller3Factory aec_factory(config);
    EchoCanceller3Factory aec_factory(config);
    aec3 = aec_factory.Create(kSampleRateHz, kChannelNum, kChannelNum);

    RTC_LOG(LS_INFO) << kLogTag << ": Custom Acoustic Echo Canceller object initialized";

    nearend_audio_buffer = std::make_unique<AudioBuffer>(
        kSampleRateHz, kChannelNum,
        kSampleRateHz, kChannelNum,
        kSampleRateHz, kChannelNum);

    aec_linear_audio = std::make_unique<AudioBuffer>(
        kSampleRateHz / 3, kChannelNum,
        kSampleRateHz / 3, kChannelNum,
        kSampleRateHz / 3, kChannelNum);

    farend_audio_buffer = std::make_unique<AudioBuffer>(
        kSampleRateHz, kChannelNum,
        kSampleRateHz, kChannelNum,
        kSampleRateHz, kChannelNum);

    RTC_LOG(LS_INFO) << kLogTag << ": Audio buffers created for echo cancellation";
}

void CustomAcousticEchoCanceller::ProcessNearEnd(int16_t* near_end_signal) {
    RTC_DCHECK(aec3);
    RTC_DCHECK(near_end_signal);

    RTC_LOG(LS_INFO) << kLogTag << ": Processing near-end signal for echo cancellation";
    StreamConfig stream_config(kSampleRateHz, kChannelNum);

    nearend_audio_buffer->CopyFrom(near_end_signal, stream_config);
    aec3->AnalyzeCapture(nearend_audio_buffer);
    nearend_audio_buffer->SplitIntoFrequencyBands();
    aec3->SetAudioBufferDelay(0);
    aec3->ProcessCapture(nearend_audio_buffer, aec_linear_audio, false);
    nearend_audio_buffer->MergeFrequencyBands();
    nearend_audio_buffer->CopyTo(stream_config, near_end_signal);

    RTC_LOG(LS_INFO) << kLogTag << ": Near-end signal processed";
}

void CustomAcousticEchoCanceller::ProcessFarEnd(int16_t* far_end_signal) {
    RTC_DCHECK(aec3);
    RTC_DCHECK(far_end_signal);

    RTC_LOG(LS_INFO) << kLogTag << ": Processing far-end signal for echo cancellation";
    StreamConfig stream_config(kSampleRateHz, kChannelNum);

    farend_audio_buffer->CopyFrom(far_end_signal, stream_config);
    farend_audio_buffer->SplitIntoFrequencyBands();
    aec3->AnalyzeRender(farend_audio_buffer);
    farend_audio_buffer->MergeFrequencyBands();
    farend_audio_buffer->CopyTo(stream_config, farend_processed_data);

    RTC_LOG(LS_INFO) << kLogTag << ": Far-end signal processed";
}


CustomAcousticEchoCanceller::~CustomAcousticEchoCanceller() {
    // Resources are automatically freed by the unique_ptr destructors.
    RTC_LOG(LS_INFO) << kLogTag << ": Custom Acoustic Echo Canceller object destroyed";
}

}  // namespace webrtc

