#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <random>

namespace Chess {

    enum class PieceType {
        KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, EMPTY
    };

    enum class Color {
        WHITE, BLACK, NONE
    };

    class Piece {
    public:
        Piece(PieceType type, Color color) : type_(type), color_(color) {}
        PieceType GetType() const { return type_; }
        Color GetColor() const { return color_; }

        char GetPieceSymbol() const {
            switch (type_) {
                case PieceType::KING:
                    return color_ == Color::WHITE ? 'K' : 'k';
                case PieceType::QUEEN:
                    return color_ == Color::WHITE ? 'Q' : 'q';
                case PieceType::ROOK:
                    return color_ == Color::WHITE ? 'R' : 'r';
                case PieceType::BISHOP:
                    return color_ == Color::WHITE ? 'B' : 'b';
                case PieceType::KNIGHT:
                    return color_ == Color::WHITE ? 'N' : 'n';
                case PieceType::PAWN:
                    return color_ == Color::WHITE ? 'P' : 'p';
                case PieceType::EMPTY:
                default:
                    return '.';
            }
        }

    private:
        PieceType type_;
        Color color_;
    };

    class Position {
    public:
        Position(int row, int col) : row_(row), col_(col) {}
        int GetRow() const { return row_; }
        int GetCol() const { return col_; }

    private:
        int row_;
        int col_;
    };

    class Board {
    public:
        Board() {
            srand(static_cast<unsigned>(time(0)));
            ResetBoard();
        }

        void ResetBoard() {
            board_ = std::vector<std::vector<std::shared_ptr<Piece>>>(8, std::vector<std::shared_ptr<Piece>>(8));
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (row == 0 || row == 7) {
                        Color color = row == 0 ? Color::WHITE : Color::BLACK;
                        if (col == 0 || col == 7) {
                            board_[row][col] = std::make_shared<Piece>(PieceType::ROOK, color);
                        } else if (col == 1 || col == 6) {
                            board_[row][col] = std::make_shared<Piece>(PieceType::KNIGHT, color);
                        } else if (col == 2 || col == 5) {
                            board_[row][col] = std::make_shared<Piece>(PieceType::BISHOP, color);
                        } else if (col == 3) {
                            board_[row][col] = std::make_shared<Piece>(PieceType::QUEEN, color);
                        } else {
                            board_[row][col] = std::make_shared<Piece>(PieceType::KING, color);
                        }
                    } else if (row == 1 || row == 6) {
                        Color color = row == 1 ? Color::WHITE : Color::BLACK;
                        board_[row][col] = std::make_shared<Piece>(PieceType::PAWN, color);
                    } else {
                        board_[row][col] = std::make_shared<Piece>(PieceType::EMPTY, Color::NONE);
                    }
                }
            }
        }

        std::shared_ptr<Piece> GetPiece(const Position& pos) const {
            return board_[pos.GetRow()][pos.GetCol()];
        }

        void MovePiece(const Position& from, const Position& to) {
            board_[to.GetRow()][to.GetCol()] = board_[from.GetRow()][from.GetCol()];
            board_[from.GetRow()][from.GetCol()] = std::make_shared<Piece>(PieceType::EMPTY, Color::NONE);
        }

        void PrintBoard() const {
            for (const auto& row : board_) {
                for (const auto& piece : row) {
                    std::cout << piece->GetPieceSymbol() << ' ';
                }
                std::cout << std::endl;
            }
        }

        Position RandomMovablePiece() const {
            std::vector<Position> movablePieces;
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (board_[row][col]->GetType() != PieceType::EMPTY) {
                        movablePieces.push_back(Position(row, col));
                    }
                }
            }
            if (movablePieces.empty()) {
                throw std::runtime_error("No movable pieces found.");
            }
            return movablePieces[rand() % movablePieces.size()];
        }

    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> board_;
    };
} // namespace Chess

int main() {
    try {
        Chess::Board board;
        board.PrintBoard();
        Chess::Position from(1, 0);
        Chess::Position to(2, 0);
        board.MovePiece(from, to);
        std::cout << std::endl;
        board.PrintBoard();

        Chess::Position randomMovablePiece = board.RandomMovablePiece();
        std::cout << "Random movable piece: (" << randomMovablePiece.GetRow() << ", " << randomMovablePiece.GetCol() << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;

}
