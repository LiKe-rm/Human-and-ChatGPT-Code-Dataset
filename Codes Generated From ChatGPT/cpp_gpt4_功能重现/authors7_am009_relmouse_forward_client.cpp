#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void ProcessEvent(SDL_Event &event, TCPsocket &socket);
void SendData(TCPsocket &socket, const void *data, int len);

int SDL_main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (SDLNet_Init() < 0) {
        std::cerr << "Error initializing SDL_net: " << SDLNet_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Remote Control",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, "127.0.0.1", 12345) < 0) {
        std::cerr << "Error resolving host: " << SDLNet_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    TCPsocket socket = SDLNet_TCP_Open(&ip);
    if (!socket) {
        std::cerr << "Error connecting to server: " << SDLNet_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                ProcessEvent(event, socket);
            }
        }
    }

    SDLNet_TCP_Close(socket);
    SDL_DestroyWindow(window);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}

void ProcessEvent(SDL_Event &event, TCPsocket &socket) {
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            char data[6] = "KEY";
            data[3] = (char)(event.type == SDL_KEYDOWN);
            data[4] = (char)event.key.keysym.sym;
            data[5] = (char)(event.key.keysym.mod & 0xFF);
            SendData(socket, data, sizeof(data));
            break;
        }
        case SDL_MOUSEMOTION: {
            char data[6] = "MMOT";
            data[4] = (char)(event.motion.xrel);
            data[5] = (char)(event.motion.yrel);
            SendData(socket, data, sizeof(data));
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            char data[5] = "MBUT";
            data[4] = (char)(event.button.button | (event.type == SDL_MOUSEBUTTONDOWN ? 0: 0x80));
            SendData(socket, data, sizeof(data));
            break;
        }
        case SDL_MOUSEWHEEL: {
            char data[5] = "MWHL";
            data[4] = (char)(event.wheel.y);
            SendData(socket, data, sizeof(data));
            break;
        }
        case SDL_WINDOWEVENT: {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_Window *window = SDL_GetWindowFromID(event.window.windowID);
                if (window) {
                    SDL_SetWindowSize(window, event.window.data1, event.window.data2);
                }
            } else if (event.window.event == SDL_WINDOWEVENT_ENTER) {
                SDL_ShowCursor(SDL_DISABLE);
            } else if (event.window.event == SDL_WINDOWEVENT_LEAVE) {
                SDL_ShowCursor(SDL_ENABLE);
            }
            break;
        }
        default:
            break;
    }
}

void SendData(TCPsocket &socket, const void *data, int len) {
    int sent = SDLNet_TCP_Send(socket, data, len);
    if (sent < len) {
        std::cerr << "Error sending data: " << SDLNet_GetError() << std::endl;
    }
}

