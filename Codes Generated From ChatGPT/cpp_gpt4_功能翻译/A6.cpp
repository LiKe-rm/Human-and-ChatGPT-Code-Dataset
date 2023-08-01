#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EdgeEffect {
public:
    explicit EdgeEffect(const sf::Color& color) : color(color), finished(false) {}
    void setColor(const sf::Color& newColor) { color = newColor; }
    bool isFinished() const { return finished; }
    void setSize(int height, int width) { rect.setSize(sf::Vector2f(height, width)); }
    void setFinished(bool value) { finished = value; }

    bool draw(sf::RenderTarget& target) {
        if (!finished) {
            rect.setFillColor(color);
            target.draw(rect);
            return true;
        }
        return false;
    }

private:
    sf::Color color;
    bool finished;
    sf::RectangleShape rect;
};

class A6 : public sf::Drawable {
public:
    explicit A6(const sf::Color& color) : edgeEffect(color) {}
    void setColor(const sf::Color& color) { edgeEffect.setColor(color); }
    void setSize(int height, int width) { edgeEffect.setSize(height, width); }
    void setFinished(bool value) { edgeEffect.setFinished(value); }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        if (!edgeEffect.isFinished()) {
            sf::Transform transform;
            transform.translate(static_cast<float>(target.getSize().x), 0.f);
            transform.rotate(90.f, 0.f, 0.f);
            target.draw(edgeEffect, transform);
        }
    }

private:
    EdgeEffect edgeEffect;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "A6 Example");
    window.setFramerateLimit(60);

    A6 a6(sf::Color(171, 70, 44));
    a6.setSize(300, 200);
    a6.setFinished(false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(a6);
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
