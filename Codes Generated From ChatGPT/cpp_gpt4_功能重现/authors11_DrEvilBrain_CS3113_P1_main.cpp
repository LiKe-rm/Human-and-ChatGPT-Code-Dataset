#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 着色器代码
const std::string vertexShaderCode = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec2 uv;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(position, 1.0f);
        TexCoord = uv;
    }
)";

const std::string fragmentShaderCode = R"(
    #version 330 core
    in vec2 TexCoord;

    out vec4 color;

    uniform sampler2D ourTexture;

    void main()
    {
        color = texture(ourTexture, TexCoord);
    }
)";

GLuint LoadShader(const std::string &shaderCode, GLenum shaderType)
{
    GLuint shaderId = glCreateShader(shaderType);
    const char *shaderSource = shaderCode.c_str();
    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error: Shader compilation failed\n"
                  << infoLog << std::endl;
    }

    return shaderId;
}

GLuint CreateShaderProgram(const std::string &vertexShaderCode, const std::string &fragmentShaderCode)
{
    GLuint vertexShader = LoadShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = LoadShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error: Program linking failed\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint LoadTexture(const std::string &imagePath)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
    }

    stbi_image_free(data    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

bool Initialize(SDL_Window *&window, SDL_GLContext &context)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Simple 2D Scene", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        return false;
    }

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
        return false;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void ProcessInput(bool &running)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Update(float deltaTime, glm::mat4 &model)
{
    static float angle = 0.0f;
    angle += deltaTime * 90.0f;
    model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Render(SDL_Window *window, GLuint shaderProgram, GLuint VAO, GLuint texture, const glm::mat4 &model)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}

void Shutdown(SDL_Window *window, SDL_GLContext context)
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_GLContext context;

    if (!Initialize(window, context))
    {
        std::cerr << "Initialization failed" << std::endl;
        return 1;
    }

    GLuint shaderProgram = CreateShaderProgram(vertexShaderCode, fragmentShaderCode);
    GLuint texture = LoadTexture("path/to/your/texture/image.png");

    GLfloat vertices[] = {
        // Positions         // Texture Coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    bool running = true;
    Uint32 lastTime = SDL_GetTicks();

    glm::mat4 model = glm::mat4(1.0f);

    while (running)
    {
        ProcessInput(running);

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        Update(deltaTime, model);
        Render(window, shaderProgram, VAO, texture, model);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);

    Shutdown(window, context);

    return 0;
}


