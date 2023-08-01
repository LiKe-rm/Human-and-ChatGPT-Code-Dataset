#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Timer.H>
#include <FL/fl_draw.H>
#include <vector>
#include <cstdlib>
#include <ctime>

const int cellSize = 20;
const int numRows = 20;
const int numCols = 20;

struct Pixel {
    int x, y;
    Fl_Color color;

    Pixel(int x, int y, Fl_Color color) : x(x), y(y), color(color) {}

    void draw() const {
        fl_color(color);
        fl_rectf(x * cellSize, y * cellSize, cellSize, cellSize);
    }
};

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Piece {
    int x, y;
    Direction direction;

    Piece(int x, int y, Direction direction) : x(x), y(y), direction(direction) {}

    void move() {
        switch (direction) {
            case UP: y--; break;
            case DOWN: y++; break;
            case LEFT: x--; break;
            case RIGHT: x++; break;
        }
    }
};

struct Snake {
    std::vector<Piece> pieces;
    Direction newDirection;

    Snake() {
        pieces.push_back(Piece(numCols / 2, numRows / 2, RIGHT));
        newDirection = RIGHT;
    }

    void move() {
        pieces.insert(pieces.begin(), Piece(pieces[0].x, pieces[0].y, newDirection));
        pieces[0].move();
        pieces.pop_back();
    }

    void changeDirection(Direction direction) {
        if ((pieces[0].direction == UP || pieces[0].direction == DOWN) && (direction == LEFT || direction == RIGHT)) {
            newDirection = direction;
        }
        if ((pieces[0].direction == LEFT || pieces[0].direction == RIGHT) && (direction == UP || direction == DOWN)) {
            newDirection = direction;
        }
    }

    bool checkCollision() const {
        if (pieces[0].x < 0 || pieces[0].x >= numCols || pieces[0].y < 0 || pieces[0].y >= numRows) {
            return true;
        }
        for (size_t i = 1; i < pieces.size(); ++i) {
            if (pieces[0].x == pieces[i].x && pieces[0].y == pieces[i].y) {
                return true;
            }
        }
        return false;
    }
};

class SnakeWindow : public Fl_Window {
    Fl_Timer timer;
    Snake snake;
    Pixel food;

public:
    SnakeWindow(int width, int height, const char *title) :
        Fl_Window(width, height, title), timer(200, timerCallback, this),
        food(rand() % numCols, rand() % numRows, FL_RED) {
        color(FL_WHITE);
        timer.start();
        srand(time(0));
    }

    int handle(int event) {
        if (event == FL_KEYDOWN) {
            switch (Fl::event_key()) {
                case FL_Up: snake.changeDirection(UP); break;
                case FL_Down: snake.changeDirection(DOWN); break;
                case FL_Left: snake.changeDirection(LEFT); break;
                case FL_Right: snake.changeDirection(RIGHT); break;
            }
        }
        return Fl_Window::handle(event);
    }

    void draw() override {
        Fl_Window::draw();
        food.draw();
        for (const Piece &piece : snake.pieces) {
            Pixel(piece.x, piece.y, FL_BLACK).draw();
        }
    }

    static void timerCallback(void *data) {
        SnakeWindow *window = static_cast<SnakeWindow *>(data);
        window->update();
    }

    void update() {
        snake.move();
        if (snake.checkCollision()) {
            timer.stop();
            fl_message("Game Over! Score: %lu", snake.pieces.size());
            return;
        }
        if (snake.pieces[0].x == food.x && snake.pieces[0].y == food.y) {
            snake.pieces.push_back(Piece(food.x, food.y, snake.pieces.back().direction));
            food.x = rand() % numCols;
            food.y = rand() % numRows;
        }
        redraw();
        timer.start();
    }
};

int main(int argc, char **argv) {
    Fl::lock();
    SnakeWindow window(cellSize * numCols, cellSize * numRows, "Snake Game");
    window.show(argc, argv);
    return Fl::run();
}
