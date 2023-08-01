/*
 * Copyright 2023 The C++ Open Source Project
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
#include <string>
#include <sstream>
#include "BluetoothCodecStatus.h"
#include "BluetoothDevice.h"

class A2dpStackEvent {
public:
    // Event types for STACK_EVENT message (coming from native)
    static const int EVENT_TYPE_NONE = 0;
    static const int EVENT_TYPE_CONNECTION_STATE_CHANGED = 1;
    static const int EVENT_TYPE_AUDIO_STATE_CHANGED = 2;
    static const int EVENT_TYPE_CODEC_CONFIG_CHANGED = 3;

    // Do not modify without updating the HAL bt_av.h files.
    // Match up with btav_connection_state_t enum of bt_av.h
    static const int CONNECTION_STATE_DISCONNECTED = 0;
    static const int CONNECTION_STATE_CONNECTING = 1;
    static const int CONNECTION_STATE_CONNECTED = 2;
    static const int CONNECTION_STATE_DISCONNECTING = 3;
    // Match up with btav_audio_state_t enum of bt_av.h
    static const int AUDIO_STATE_REMOTE_SUSPEND = 0;
    static const int AUDIO_STATE_STOPPED = 1;
    static const int AUDIO_STATE_STARTED = 2;

    int type = EVENT_TYPE_NONE;
    BluetoothDevice device;
    int valueInt = 0;
    BluetoothCodecStatus codecStatus;

    A2dpStackEvent(int type) : type(type) {}

    std::string toString() {
        std::stringstream result;
        result << "A2dpStackEvent {type:" << eventTypeToString(type);
        result << ", device:" << device.toString();
        result << ", value1:" << eventTypeValueIntToString(type, valueInt);
        if (codecStatus.isValid()) {
            result << ", codecStatus:" << codecStatus.toString();
        }
        result << "}";
        return result.str();
    }

private:
    static std::string eventTypeToString(int type) {
        switch (type) {
            case EVENT_TYPE_NONE:
                return "EVENT_TYPE_NONE";
            case EVENT_TYPE_CONNECTION_STATE_CHANGED:
                return "EVENT_TYPE_CONNECTION_STATE_CHANGED";
            case EVENT_TYPE_AUDIO_STATE_CHANGED:
                return "EVENT_TYPE_AUDIO_STATE_CHANGED";
            case EVENT_TYPE_CODEC_CONFIG_CHANGED:
                return "EVENT_TYPE_CODEC_CONFIG_CHANGED";
            default:
                return "EVENT_TYPE_UNKNOWN:" + std::to_string(type);
        }
    }

    static std::string eventTypeValueIntToString(int type, int value) {
        switch (type) {
            case EVENT_TYPE_CONNECTION_STATE_CHANGED:
                switch (value) {
                    case CONNECTION_STATE_DISCONNECTED:
                        return "DISCONNECTED";
                    case CONNECTION_STATE_CONNECTING:
                        return "CONNECTING";
                    case CONNECTION_STATE_CONNECTED:
                        return "CONNECTED";
                    case CONNECTION_STATE_DISCONNECTING:
                        return "DISCONNECTING";
                    default:
                        break;
                }
                break;
            case EVENT_TYPE_AUDIO_STATE_CHANGED:
                switch (value) {
                    case AUDIO_STATE_REMOTE_SUSPEND:
                        return "REMOTE_SUSPEND";
                    case AUDIO_STATE_STOPPED:
                        return "STOPPED";
                    case AUDIO_STATE_STARTED:
                        return "STARTED";
                    default:
                        break;
                }
                break;
            default:
            break;
    }
    return std::to_string(value);
}
};

// Sample implementation of BluetoothDevice and BluetoothCodecStatus
// These are not complete implementations, but enough to make the code work.

class BluetoothDevice {
public:
std::string address = "00:00:00:00:00:00";
std::string toString() const {
    return "BluetoothDevice{address:" + address + "}";
}
};

class BluetoothCodecStatus {
public:
bool valid = false;
bool isValid() const {
    return valid;
}

std::string toString() const {
    return "BluetoothCodecStatus{valid:" + std::to_string(valid) + "}";
}
};

int main() {
A2dpStackEvent event(A2dpStackEvent::EVENT_TYPE_CONNECTION_STATE_CHANGED);
event.device.address = "01:23:45:67:89:AB";
event.valueInt = A2dpStackEvent::CONNECTION_STATE_CONNECTED;
event.codecStatus.valid = true;
std::cout << event.toString() << std::endl;

return 0;
}