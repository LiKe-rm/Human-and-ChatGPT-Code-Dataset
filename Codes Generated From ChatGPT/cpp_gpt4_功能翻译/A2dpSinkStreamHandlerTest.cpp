/*
 * Copyright (C) 2023 The Example Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <gtest/gtest.h>

#include "AudioManager.hpp"
#include "A2dpSinkService.hpp"
#include "A2dpSinkStreamHandler.hpp"

class A2dpSinkStreamHandlerTest : public testing::Test {
protected:
    void SetUp() override {
        m_handlerThread = std::make_unique<std::thread>([this] {
            m_streamHandler.run();
        });

        std::unique_lock<std::mutex> lock(m_readyMutex);
        m_readyCondition.wait(lock, [this] { return m_streamHandler.isReady(); });
    }

    void TearDown() override {
        m_streamHandler.stop();
        if (m_handlerThread->joinable()) {
            m_handlerThread->join();
        }
    }

    AudioManager m_audioManager;
    A2dpSinkService m_a2dpSinkService;
    A2dpSinkStreamHandler m_streamHandler{m_a2dpSinkService, m_audioManager};
    std::unique_ptr<std::thread> m_handlerThread;
    std::mutex m_readyMutex;
    std::condition_variable m_readyCondition;
};

TEST_F(A2dpSinkStreamHandlerTest, TestSrcStart) {
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SRC_STR_START);
    EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestSrcStop) {
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SRC_STR_STOP);
    EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestSnkPlay) {
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::PLAYING);
}

TEST_F(A2dpSinkStreamHandlerTest, TestSnkPause) {
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PAUSE);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestDisconnect) {
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::DISCONNECT);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestSrcPlay) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SRC_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestSrcPlayIot) {
m_audioManager.setIotDevice(true);
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SRC_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::PLAYING);
}

TEST_F(A2dpSinkStreamHandlerTest, TestSrcPause) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SRC_PAUSE);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestFocusGain) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusGain();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::PLAYING);
}

TEST_F(A2dpSinkStreamHandlerTest, TestFocusTransientMayDuck) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusLossTransientCanDuck();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_FLOAT_EQ(m_audioManager.getAudioTrackGain(), AudioManager::DUCK_PERCENT / 100.0f);
}

TEST_F(A2dpSinkStreamHandlerTest, TestFocusLostTransient) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusLossTransient();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

TEST_F(A2dpSinkStreamHandlerTest, TestFocusRerequest) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusLossTransient();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.requestAudioFocus();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::PLAYING);
}

TEST_F(A2dpSinkStreamHandlerTest, TestFocusGainTransient) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusLossTransient();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::DELAYED_PAUSE);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusGain();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::PLAYING);
}

TEST_F(A2dpSinkStreamHandlerTest, TestFocusLost) {
m_streamHandler.handleEvent(A2dpSinkStreamHandler::Event::SNK_PLAY);
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m_audioManager.triggerAudioFocusLoss();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
EXPECT_EQ(m_streamHandler.getStreamState(), A2dpSinkStreamHandler::StreamState::STOPPED);
}

int main(int argc, char** argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
