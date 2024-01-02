# Custom WebRTC Acoustic Echo Canceller (AEC)

This repository contains a generic custom implementation of the WebRTC-based Acoustic Echo Canceller (AEC) that is cross-platform compatible.

-----

**Getting Started**
------
High performance audio apps typically require more functionality than the simple ability to play or record sound. They demand responsive realtime system behavior. Webrtc provides browsers and *mobile applications* with Real-Time Communications (RTC) capabilities via simple APIs. 

For *Compilation and Building the WebRTC Library for Android*, you should have to look into this refernce:

- [Compile_WebRTC_Library_For_Android](https://github.com/mail2chromium/Compile_WebRTC_Library_For_Android)


For *real-time Communication and AudioProcessing* in Android, I will recommend you to must visit these refernces:

- [Android_Realtime_Communication_Using_WebRTC](https://github.com/mail2chromium/Android_Realtime_Communication_Using_WebRTC)
- [Android-Native-Development-For-WebRTC](https://github.com/mail2chromium/Android-Native-Development-For-WebRTC)

WebRTC supports  (Audio Microphone Collection), (Encoding), and (RTP packet transmission). Features of *Audio Data* that Webrtc-APM accepts only include;

- **16-bit** linear PCM Audio Data.
- 160-frames of **10 ms**. (Optimal Sample Rate)
- One or Multiple channels should be interleaved.

-----


## Overview

The Custom AEC module provides a simple interface with two primary functions for processing near-end and far-end audio signals. This enables the user to obtain a processed near-end signal that has reduced echo, suitable for high-quality audio communication applications.

## Usage

### Desktop

To integrate this custom AEC into a desktop application:

1. Add the `custom_acoustic_echo_canceller.h` and `custom_acoustic_echo_canceller.cc` files into the `webrtc/src/audio_processing/` directory of the WebRTC codebase.
2. Update the `BUILD.gn` file associated with the directory to include these new files in the build.
3. Include `custom_acoustic_echo_canceller.h` in your project similar to how it's done in the provided `main.cpp` file.

### Android

For Android integration:

1. Place the `custom_acoustic_echo_canceller.h` and `custom_acoustic_echo_canceller.cc` files into `webrtc/src/sdk/android/src/jni/audio_device/`.
2. Add a reference to these files in the `webrtc/src/sdk/android/BUILD.gn` to include them in the build.
3. Build the custom JNI wrapper as part of the WebRTC Android build process.

### iOS

For iOS integration:

1. Place the `custom_acoustic_echo_canceller.h` and `custom_acoustic_echo_canceller.cc` files into `webrtc/src/sdk/objc/native/src/audio/`.
2. Add a reference to these files in the `webrtc/src/sdk/BUILD.gn` to include them in the build.
3. Compile the WebRTC codebase for iOS and build Objective-C wrappers as necessary.

## Example

An example `main.cpp` file is provided to demonstrate the basic usage of the Custom AEC module. It illustrates how to read audio files, process them through the AEC, and write the output.

## Contributions

Contributions to this project are welcome. Please ensure that any pull requests are tested across the supported platforms
