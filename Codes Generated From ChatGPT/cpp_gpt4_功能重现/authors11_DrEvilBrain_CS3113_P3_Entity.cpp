#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
    Entity(glm::vec2 position, glm::vec2 size, GLuint texture, GLfloat velocity)
        : Position(position), Size(size), Texture(texture), Velocity(velocity)
    {
    }

    bool CheckCollision(Entity &other)
    {
        bool collisionX = Position.x + Size.x >= other.Position.x &&
            other.Position.x + other.Size.x >= Position.x;
        bool collisionY = Position.y + Size.y >= other.Position.y &&
            other.Position.y + other.Size.y >= Position.y;
        return collisionX && collisionY;
    }

    void CheckCollisionX(Entity &other)
    {
        if (CheckCollision(other))
        {
            if (Velocity > 0)
            {
                Position.x = other.Position.x - Size.x;
            } else
            {
                Position.x = other.Position.x + other.Size.x;
            }
        }
    }

    void CheckCollisionY(Entity &other)
    {
        if (CheckCollision(other))
        {
            if (Velocity > 0)
            {
                Position.y = other.Position.y - Size.y;
            } else
            {
                Position.y = other.Position.y + other.Size.y;
            }
        }
    }

    void Update()
    {
        // Update the entity's position, animation, collision state, etc.
    }

    void DrawSprite(GLuint shaderProgram, GLuint VAO, const glm::mat4 &projection, const glm::mat4 &view)
    {
        // Prepare transformations
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(Position, 0.0f));
        model = glm::scale(model, glm::vec3(Size, 1.0f));

        // Set the shader uniforms
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, Texture);

        // Render the entity
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glm::vec2 Position;
    glm::vec2 Size;
    GLuint Texture;
    GLfloat Velocity;
};

int main()
{
    // Set up your game loop, OpenGL context, etc.

    // Create a sample entity
    Entity player(glm::vec2(100.0f, 100.0f), glm::vec2(32.0f, 32.0f), 0 /* texture ID */, 200.0f /* velocity */);

    // Create another entity to collide with
    Entity obstacle(glm::vec2(150.0f, 100.0f), glm::vec2(32.0f, 32.0f), 0 /* texture ID */, 0.0f /* velocity */);

    // In the game loop:
    while (true /* game is running */)
    {
        // Update the player's position
        player.Update();

        // Check for collisions
        player.CheckCollisionX(obstacle);
        player.CheckCollisionY(obstacle);

        // Render the player
        player.DrawSprite(/* shaderProgram, VAO, projection, view */);

            // Render the obstacle
        obstacle.DrawSprite(/* shaderProgram, VAO, projection, view */);

        // Swap the buffers, handle input, etc.
    }

    // Clean up resources and exit
    return 0;
}

