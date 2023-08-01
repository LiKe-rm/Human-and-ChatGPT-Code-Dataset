#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Timer.H>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int BLOCK_SIZE = 10;
const int INITIAL_SNAKE_LENGTH = 5;
const int SNAKE_SPEED = 50;

class Pixel : public Fl_Box {
public:
    Pixel(int x, int y, Fl_Color color) : Fl_Box(x, y, BLOCK_SIZE, BLOCK_SIZE) {
        this->color(color);
    }
};

class Piece {
public:
    Piece(int x, int y, Fl_Color color) : x_(x), y_(y), color_(color) {}
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    void set_x(int x) { x_ = x; }
    void set_y(int y) { y_ = y; }
    Fl_Color get_color() const { return color_; }
private:
    int x_;
    int y_;
    Fl_Color color_;
};

class Snake {
public:
    Snake(int x, int y, Fl_Color color) : direction_(FL_RIGHT) {
        for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i) {
            pieces_.push_back(Piece(x - i * BLOCK_SIZE, y, color));
        }
    }
    const std::vector<Piece>& get_pieces() const { return pieces_; }
    void add_piece(int x, int y, Fl_Color color) { pieces_.push_back(Piece(x, y, color)); }
    void remove_piece() { pieces_.pop_back(); }
    int get_direction() const { return direction_; }
    void set_direction(int direction) { direction_ = direction; }
    bool is_intersecting_with_screen() const {
        int x = pieces_.front().get_x();
        int y = pieces_.front().get_y();
        return x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT;
    }
    bool is_intersecting_with_self() const {
        int x = pieces_.front().get_x();
        int y = pieces_.front().get_y();
        for (size_t i = 1; i < pieces_.size(); ++i) {
            if (pieces_[i].get_x() == x && pieces_[i].get_y() == y) {
                return true;
            }
        }
        return false;
    }
    void update() {
        int x = pieces_.front().get_x();
        int y = pieces_.front().get_y();
        switch (direction_) {
            case FL_RIGHT:
                add_piece(x + BLOCK_SIZE, y, FL_RED);
                break;
            case FL_LEFT:
                add_piece(x - BLOCK_SIZE, y, FL_BLUE);
                break;
            case FL_UP:
                add_piece(x, y - BLOCK_SIZE, FL_GREEN);
                break;
            case FL_DOWN:
                add_piece(x, y + BLOCK_SIZE, FL_YELLOW);
                break;
        }
        remove_piece();
    }
private:
    std::vector<Piece> pieces_;
    int direction_;
};

void handle(Fl_Widget* widget, void* data) {
    Snake* snake = (Snake*)data;
    int key = Fl::event_key();
    if (key == FL_Right && snake->get_direction() != FL_LEFT) {
        snake->set_direction(FL_RIGHT);
    } else if (key == FL_Left&& snake->get_direction() != FL_RIGHT) {
    snake->set_direction(FL_LEFT);
    } else if (key == FL_Up && snake->get_direction() != FL_DOWN) {
    snake->set_direction(FL_UP);
    } else if (key == FL_Down && snake->get_direction() != FL_UP) {
    snake->set_direction(FL_DOWN);
    }
}

void game_loop(void* data) {
    Fl_Widget* widget = (Fl_Widget*)data;
    Snake* snake = (Snake*)widget->user_data();
    snake->update();
    if (snake->is_intersecting_with_screen() || snake->is_intersecting_with_self()) {
        Fl::remove_timeout(game_loop, widget);
        return;
    }
    widget->redraw();
    Fl::repeat_timeout(1.0 / SNAKE_SPEED, game_loop, widget);
}

int main(int argc, char** argv) {
    Fl_Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    Snake snake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, FL_RED);
    for (const auto& piece : snake.get_pieces()) {
        Pixel* pixel = new Pixel(piece.get_x(), piece.get_y(), piece.get_color());
        window.add(pixel);
    }
    window.show();
    Fl::add_timeout(1.0 / SNAKE_SPEED, game_loop, &window);
    window.user_data(&snake);
    window.callback(handle, &snake);
    return Fl::run();
}
