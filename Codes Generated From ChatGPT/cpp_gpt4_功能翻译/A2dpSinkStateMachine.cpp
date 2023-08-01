// Copyright (C) 2023 The C++ Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include <queue>

class BluetoothDevice {
public:
    BluetoothDevice(const std::string& address) : m_address(address) {}
    std::string getAddress() const { return m_address; }

private:
    std::string m_address;
};

class AudioConfig {
public:
    AudioConfig(int sampleRate, int channelCount, int encoding)
        : m_sampleRate(sampleRate), m_channelCount(channelCount), m_encoding(encoding) {}

    int getSampleRate() const { return m_sampleRate; }
    int getChannelCount() const { return m_channelCount; }
    int getEncoding() const { return m_encoding; }

private:
    int m_sampleRate;
    int m_channelCount;
    int m_encoding;
};

class A2dpSinkStateMachine;

class State {
public:
    virtual ~State() = default;
    virtual void enter(A2dpSinkStateMachine& stateMachine) {}
    virtual void exit(A2dpSinkStateMachine& stateMachine) {}
    virtual void handleEvent(A2dpSinkStateMachine& stateMachine, int event) {}
};

class A2dpSinkService {
public:
    using StatePtr = std::shared_ptr<State>;

    void connectDevice(const std::string& address);
    void disconnectDevice(const std::string& address);
    void setState(const std::string& address, StatePtr state);
    void removeStateMachine(const std::string& address);

private:
    std::map<std::string, std::shared_ptr<A2dpSinkStateMachine>> m_stateMachines;
    std::mutex m_stateMachinesMutex;
};

class A2dpSinkStateMachine {
public:
    enum Event {
        STACK_EVENT = 200,
        CONNECT = 1,
        DISCONNECT = 2
    };

    A2dpSinkStateMachine(const BluetoothDevice& device, A2dpSinkService& service)
        : m_device(device), m_service(service), m_audioConfig(nullptr) {}

    void setState(std::shared_ptr<State> state);
    void handleEvent(int event);

    const BluetoothDevice& getDevice() const { return m_device; }
    const AudioConfig* getAudioConfig() const { return m_audioConfig.get(); }
    void setAudioConfig(std::unique_ptr<AudioConfig> audioConfig) { m_audioConfig = std::move(audioConfig); }

private:
    BluetoothDevice m_device;
    A2dpSinkService& m_service;
    std::shared_ptr<State> m_currentState;
    std::unique_ptr<AudioConfig> m_audioConfig;
};

// State implementations
class Disconnected : public State {
public:
    void enter(A2dpSinkStateMachine& stateMachine) override;
    void handleEvent(A2dpSinkStateMachine& stateMachine, int event) override;
};

class Connecting : public State {
public:
    void enter(A2dpSinkStateMachine& stateMachine) override;
    void exit(A2dpSinkStateMachine& stateMachine) override;
    void handleEvent(A2dpSinkStateMachine& stateMachine, int event) override;

private:
bool m_incomingConnection = false;
};

class Connected : public State {
public:
void enter(A2dpSinkStateMachine& stateMachine) override;
void handleEvent(A2dpSinkStateMachine& stateMachine, int event) override;
};

class Disconnecting : public State {
public:
void enter(A2dpSinkStateMachine& stateMachine) override;
};

// State implementation details

void Disconnected::enter(A2dpSinkStateMachine& stateMachine) {
std::cout << "Enter Disconnected" << std::endl;
}

void Disconnected::handleEvent(A2dpSinkStateMachine& stateMachine, int event) {
switch (event) {
case A2dpSinkStateMachine::CONNECT:
stateMachine.setState(std::make_shared<Connecting>());
break;
default:
break;
}
}

void Connecting::enter(A2dpSinkStateMachine& stateMachine) {
std::cout << "Enter Connecting" << std::endl;
m_incomingConnection = false;
}

void Connecting::exit(A2dpSinkStateMachine& stateMachine) {
m_incomingConnection = false;
}

void Connecting::handleEvent(A2dpSinkStateMachine& stateMachine, int event) {
switch (event) {
case A2dpSinkStateMachine::STACK_EVENT:
if (!m_incomingConnection) {
stateMachine.setState(std::make_shared<Connected>());
}
break;
default:
break;
}
}

void Connected::enter(A2dpSinkStateMachine& stateMachine) {
std::cout << "Enter Connected" << std::endl;
}

void Connected::handleEvent(A2dpSinkStateMachine& stateMachine, int event) {
switch (event) {
case A2dpSinkStateMachine::DISCONNECT:
stateMachine.setState(std::make_shared<Disconnecting>());
break;
default:
break;
}
}

void Disconnecting::enter(A2dpSinkStateMachine& stateMachine) {
std::cout << "Enter Disconnecting" << std::endl;
stateMachine.setState(std::make_shared<Disconnected>());
}

// A2dpSinkStateMachine implementation details

void A2dpSinkStateMachine::setState(std::shared_ptr<State> state) {
if (m_currentState) {
m_currentState->exit(*this);
}
m_currentState = state;
m_currentState->enter(*this);
}

void A2dpSinkStateMachine::handleEvent(int event) {
m_currentState->handleEvent(*this, event);
}

// A2dpSinkService implementation details

void A2dpSinkService::connectDevice(const std::string& address) {
std::unique_lockstd::mutex lock(m_stateMachinesMutex);
if (m_stateMachines.count(address) == 0) {
    BluetoothDevice device(address);
    auto stateMachine = std::make_shared<A2dpSinkStateMachine>(device, *this);
    m_stateMachines[address] = stateMachine;
    stateMachine->setState(std::make_shared<Disconnected>());
}

m_stateMachines[address]->handleEvent(A2dpSinkStateMachine::CONNECT);
}

void A2dpSinkService::disconnectDevice(const std::string& address) {
std::unique_lockstd::mutex lock(m_stateMachinesMutex);
if (m_stateMachines.count(address) != 0) {
    m_stateMachines[address]->handleEvent(A2dpSinkStateMachine::DISCONNECT);
}
}