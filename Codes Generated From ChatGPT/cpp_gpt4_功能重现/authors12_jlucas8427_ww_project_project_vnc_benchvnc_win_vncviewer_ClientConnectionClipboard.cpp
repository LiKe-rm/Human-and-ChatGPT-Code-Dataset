#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <windows.h>
#include <rfb/rfbclient.h>

// GNU通用公共许可证声明
/*
  Copyright (C) 2023 Your Name

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

std::mutex clipboard_mutex;

void update_local_clipboard(const std::string& data) {
    std::unique_lock<std::mutex> lock(clipboard_mutex);

    if (!OpenClipboard(NULL)) {
        std::cerr << "Failed to open clipboard" << std::endl;
        return;
    }

    EmptyClipboard();
    HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, data.size() + 1);
    if (!hData) {
        CloseClipboard();
        std::cerr << "Failed to allocate memory" << std::endl;
        return;
    }

    memcpy(GlobalLock(hData), data.c_str(), data.size() + 1);
    GlobalUnlock(hData);
    SetClipboardData(CF_TEXT, hData);
    CloseClipboard();
}

std::string get_clipboard_data() {
    std::unique_lock<std::mutex> lock(clipboard_mutex);
    std::string data;

    if (!IsClipboardFormatAvailable(CF_TEXT) || !OpenClipboard(NULL)) {
        return data;
    }

    HGLOBAL hData = GetClipboardData(CF_TEXT);
    if (hData) {
        data = static_cast<const char*>(GlobalLock(hData));
        GlobalUnlock(hData);
    }

    CloseClipboard();
    return data;
}

void handle_local_clipboard_update(rfbClient* client) {
    static std::string previous_data;
    std::string data = get_clipboard_data();

    if (data != previous_data) {
        rfbClientSendClipboard(client, data.c_str(), data.length());
        previous_data = data;
    }
}

void handle_remote_clipboard_update(rfbClient* client, const char* text, int len) {
    std::string data(text, len);
    update_local_clipboard(data);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }

    const char* host = argv[1];
    int port = atoi(argv[2]);

    rfbClient* client = rfbGetClient(8, 3, 4);
    client->MallocFrameBuffer = rfbDefaultMallocFrameBuffer;
    client->GotFrameBufferUpdate = rfbDefaultGotFrameBufferUpdate;
    client->GotClipText = handle_remote_clipboard_update;
    client->appData.useRemoteCursor = 1;
    client->appData.compressLevel = 9;
    client->appData.qualityLevel = 9;

    if (!rfbInitClient(client, &argc, argv)) {
        std::cerr << "Failed to initialize VNC client" << std::endl;
        return 1;
    }

    std::thread clipboard_monitor([&client]() {
        while (true) {
            handle_local_clipboard_update(client);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    while (rfbIsActive(client)) {
        rfbCheckFds(client, 1000);
        rfbProcessEvents(client, 1000);
    }

    clipboard_monitor.detach();
    rfbClientCleanup(client);

    return 0;
}
