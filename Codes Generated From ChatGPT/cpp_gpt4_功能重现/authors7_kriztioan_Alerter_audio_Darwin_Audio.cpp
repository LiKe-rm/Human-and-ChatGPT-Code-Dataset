#include <iostream>
#include <string>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreAudio/CoreAudioTypes.h>

class Audio {
private:
    AudioComponentInstance mixer;
    Float32 *samples;
    UInt32 n_samples;
    AudioStreamBasicDescription outputFormat;

public:
    Audio() : mixer(nullptr), samples(nullptr), n_samples(0) {
        outputFormat.mSampleRate = 44100.0;
        outputFormat.mFormatID = kAudioFormatLinearPCM;
        outputFormat.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked | kAudioFormatFlagIsNonInterleaved;
        outputFormat.mBytesPerPacket = sizeof(Float32);
        outputFormat.mFramesPerPacket = 1;
        outputFormat.mBytesPerFrame = sizeof(Float32);
        outputFormat.mChannelsPerFrame = 2;
        outputFormat.mBitsPerChannel = 8 * sizeof(Float32);
    }

    ~Audio() {
        audioStop();
        if (samples) {
            delete[] samples;
        }
    }

    OSStatus audioStart() {
        AudioComponentDescription mixerDescription;
        mixerDescription.componentType = kAudioUnitType_Output;
        mixerDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
        mixerDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
        mixerDescription.componentFlags = 0;
        mixerDescription.componentFlagsMask = 0;

        AudioComponent mixerComponent = AudioComponentFindNext(NULL, &mixerDescription);
        if (mixerComponent == NULL) {
            std::cerr << "Could not find audio component." << std::endl;
            return -1;
        }

        OSStatus status = AudioComponentInstanceNew(mixerComponent, &mixer);
        if (status != noErr) {
            std::cerr << "Could not create audio component instance." << std::endl;
            return status;
        }

        AURenderCallbackStruct renderCallback;
        renderCallback.inputProc = audioRenderer;
        renderCallback.inputProcRefCon = this;

        status = AudioUnitSetProperty(mixer, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &renderCallback, sizeof(renderCallback));
        if (status != noErr) {
            std::cerr << "Could not set render callback." << std::endl;
            return status;
        }

        status = AudioUnitSetProperty(mixer, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &outputFormat, sizeof(outputFormat));
        if (status != noErr) {
            std::cerr << "Could not set stream format." << std::endl;
            return status;
        }

        status = AudioUnitInitialize(mixer);
        if (status != noErr) {
            std::cerr << "Could not initialize audio unit." << std::endl;
            return status;
        }

        return AudioOutputUnitStart(mixer);
    }

    OSStatus audioStop() {
        if (mixer) {
            AudioOutputUnitStop(mixer);
            AudioUnitUninitialize(mixer);
            AudioComponentInstanceDispose(mixer);
            mixer = nullptr;
        }
        return noErr;
    }

    OSStatus loadSoundFromFile(const std::string &filename) {
        // Load the sound data from file using any available audio file library
        // For example, libsndfile can be used here: http://www.mega-nerd.com/libsndfile/

        // Read sound data into `samples` array and set `n_samples` to the number of samples
        // ...

        return noErr;
    }

    OSStatus playSound() {
        if (!samples || n_samples == 0) {
            std::cerr << "No audio samples loaded." << std::endl;
            return -1;
        }
        return audioStart();
    }

private:
    static OSStatus audioRenderer(void *inRefCon,
    AudioUnitRenderActionFlags *ioActionFlags,
    const AudioTimeStamp *inTimeStamp,
    UInt32 inBusNumber,
    UInt32 inNumberFrames,
    AudioBufferList *ioData) {
        Audio *self = static_cast<Audio *>(inRefCon);

        if (!self->samples || self->n_samples == 0) {
            return noErr;
        }

        UInt32 sampleIndex = 0;
        for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
            for (UInt32 channel = 0; channel < ioData->mNumberBuffers; ++channel) {
                Float32 *buffer = static_cast<Float32 *>(ioData->mBuffers[channel].mData);
                buffer[frame] = (sampleIndex < self->n_samples) ? self->samples[sampleIndex] : 0;
            }
            sampleIndex++;
        }

        if (sampleIndex >= self->n_samples) {
            self->audioStop();
        }

        return noErr;
    }
};

