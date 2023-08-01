#include <iostream>
#include <fstream>
#include <string>
#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioToolbox.h>
#include <vector>

class MacOSAudioPlayer {
public:
    MacOSAudioPlayer();
    ~MacOSAudioPlayer();

    bool loadAudioFile(const std::string &filePath);
    void setSampleRate(Float64 sampleRate);
    void setChannels(UInt32 channels);
    void setStereoPan(Float32 pan);

    void audioStart();
    void audioStop();
    void audioClear();

    static OSStatus audioRenderer(void *inRefCon,
                                  AudioUnitRenderActionFlags *ioActionFlags,
                                  const AudioTimeStamp *inTimeStamp,
                                  UInt32 inBusNumber,
                                  UInt32 inNumberFrames,
                                  AudioBufferList *ioData);

    typedef OSStatus (*OutsideRenderer)(void *inRefCon,
                                        AudioUnitRenderActionFlags *ioActionFlags,
                                        const AudioTimeStamp *inTimeStamp,
                                        UInt32 inBusNumber,
                                        UInt32 inNumberFrames,
                                        AudioBufferList *ioData);

    void setOutsideRenderer(OutsideRenderer renderer);

private:
    void createAudioUnit();
    void applyAudioProperties();

    AudioComponentInstance m_audioUnit;
    std::vector<char> m_audioData;
    UInt64 m_audioDataIndex;

    Float64 m_sampleRate;
    UInt32 m_channels;
    Float32 m_stereoPan;

    OutsideRenderer m_outsideRenderer;
};

MacOSAudioPlayer::MacOSAudioPlayer()
    : m_audioUnit(nullptr), m_audioDataIndex(0),
      m_sampleRate(44100), m_channels(2), m_stereoPan(0),
      m_outsideRenderer(nullptr) {
    createAudioUnit();
}

MacOSAudioPlayer::~MacOSAudioPlayer() {
    if (m_audioUnit) {
        AudioComponentInstanceDispose(m_audioUnit);
    }
}

bool MacOSAudioPlayer::loadAudioFile(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open audio file: " << filePath << std::endl;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    m_audioData.resize(size);
    file.read(m_audioData.data(), size);

    return true;
}

void MacOSAudioPlayer::setSampleRate(Float64 sampleRate) {
    m_sampleRate = sampleRate;
    applyAudioProperties();
}

void MacOSAudioPlayer::setChannels(UInt32 channels) {
    m_channels = channels;
    applyAudioProperties();
}

void MacOSAudioPlayer::setStereoPan(Float32 pan) {
    m_stereoPan = pan;
    applyAudioProperties();
}

void MacOSAudioPlayer::audioStart() {
    AudioOutputUnitStart(m_audioUnit);
}

void MacOSAudioPlayer::audioStop() {
    AudioOutputUnitStop(m_audioUnit);
}

void MacOSAudioPlayer::audioClear() {
    m_audioData.clear();
    m_audioDataIndex = 0;
}

OSStatus MacOSAudioPlayer::audioRenderer(void *inRefCon,
                                         AudioUnitRenderActionFlags *ioActionFlags,
                                         const AudioTimeStamp *inTimeStamp,
                                         UInt32 inBusNumber,
                                         UInt32 inNumberFrames,
                                         AudioBufferList *ioData) {
    MacOSAudioPlayer *player = static_cast<MacOSAudioPlayer *>(inRefCon);
    if (player->m_outsideRenderer) {
        return player->m_outsideRenderer(inRefCon, ioActionFlags, inTimeStamp,
                                         inBusNumber, inNumberFrames, ioData);
    }
    for (UInt32 i = 0; i < ioData->mNumberBuffers; i++) {
        AudioBuffer *buffer = &ioData->mBuffers[i];
        size_t bytesToCopy = inNumberFrames * player->m_channels * sizeof(Float32);

        if (player->m_audioDataIndex + bytesToCopy > player->m_audioData.size()) {
            bytesToCopy = player->m_audioData.size() - player->m_audioDataIndex;
        }

        memcpy(buffer->mData, player->m_audioData.data() + player->m_audioDataIndex, bytesToCopy);
        buffer->mDataByteSize = bytesToCopy;
        player->m_audioDataIndex += bytesToCopy;

        if (player->m_audioDataIndex >= player->m_audioData.size()) {
            player->m_audioDataIndex = 0;
        }
    }

    return noErr;
 }

void MacOSAudioPlayer::setOutsideRenderer(OutsideRenderer renderer) {
    m_outsideRenderer = renderer;
}

void MacOSAudioPlayer::createAudioUnit() {
    AudioComponentDescription desc;
    desc.componentType = kAudioUnitType_Output;
    desc.componentSubType = kAudioUnitSubType_DefaultOutput;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;
    desc.componentFlags = 0;
    desc.componentFlagsMask = 0;
    AudioComponent comp = AudioComponentFindNext(nullptr, &desc);
    AudioComponentInstanceNew(comp, &m_audioUnit);

    AURenderCallbackStruct callback;
    callback.inputProc = audioRenderer;
    callback.inputProcRefCon = this;
    AudioUnitSetProperty(m_audioUnit, kAudioUnitProperty_SetRenderCallback,
                         kAudioUnitScope_Input, 0, &callback, sizeof(callback));

    applyAudioProperties();
}

void MacOSAudioPlayer::applyAudioProperties() {
    if (!m_audioUnit) {
        return;
    }

    AudioStreamBasicDescription streamFormat;
    streamFormat.mSampleRate = m_sampleRate;
    streamFormat.mFormatID = kAudioFormatLinearPCM;
    streamFormat.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked | kAudioFormatFlagIsNonInterleaved;
    streamFormat.mBytesPerPacket = sizeof(Float32);
    streamFormat.mFramesPerPacket = 1;
    streamFormat.mBytesPerFrame = sizeof(Float32);
    streamFormat.mChannelsPerFrame = m_channels;
    streamFormat.mBitsPerChannel = 8 * sizeof(Float32);
    streamFormat.mReserved = 0;

    AudioUnitSetProperty(m_audioUnit, kAudioUnitProperty_StreamFormat,
                         kAudioUnitScope_Input, 0, &streamFormat, sizeof(streamFormat));

    AudioUnitSetProperty(m_audioUnit, kAudioUnitProperty_Pan,
                         kAudioUnitScope_Global, 0, &m_stereoPan, sizeof(m_stereoPan));

    AudioUnitInitialize(m_audioUnit);
}



   
