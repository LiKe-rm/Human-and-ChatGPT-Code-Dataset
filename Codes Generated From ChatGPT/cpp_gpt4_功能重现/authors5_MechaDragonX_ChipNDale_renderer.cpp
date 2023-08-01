#include <iostream>
#include <SDL.h>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();
    bool init();
    void clear();
    void present();
    bool processInput(uint8_t keys[16]);

private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    SDL_Texture* texture;
    int screenWidth;
    int screenHeight;

    const uint8_t KEY_MAP[16] = {
        SDLK_x, SDLK_1, SDLK_2, SDLK_3,
        SDLK_q, SDLK_w, SDLK_e, SDLK_a,
        SDLK_s, SDLK_d, SDLK_z, SDLK_c,
        SDLK_4, SDLK_r, SDLK_f, SDLK_v
    };
};

Renderer::Renderer(int width, int height) : screenWidth(width), screenHeight(height), window(nullptr), sdlRenderer(nullptr), texture(nullptr) {}

Renderer::~Renderer() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Renderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
    if (texture == nullptr) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::clear() {
    SDL_RenderClear(sdlRenderer);
}

void Renderer::present() {
    SDL_RenderCopy(sdlRenderer, texture, nullptr, nullptr);
    SDL_RenderPresent(sdlRenderer);
}

bool Renderer::processInput(uint8_t keys[16]) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            for (int i = 0; i < 16; ++i) {
                if (e.key.keysym.sym == KEY_MAP[i]) {
                    keys[i] = e.type == SDL_KEYDOWN ? 1 : 0;
                }
            }
        }
    }
    return true;
}

int main() {
    int screenWidth = 640;
    int screenHeight = 320;

    Renderer renderer(screenWidth, screenHeight);

    if (!renderer.init()) {
        return 1;
    }

    uint8_t keys[16] = {0};

    bool running = true;
    while (running) {
        running = renderer.processInput(keys);

        renderer.clear();
        // Update texture here
        renderer.present();

        SDL_Delay(1000 / 60); // Limit to 60 FPS
    }
    return 0;
}
