#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cctype>

class SolitaireException : public std::logic_error {
public:
    explicit SolitaireException(const std::string& message) : std::logic_error(message) {}
};

class InvalidInputException : public SolitaireException {
public:
    explicit InvalidInputException(const std::string& message) : SolitaireException(message) {}
};

class InvalidMoveException : public SolitaireException {
public:
    explicit InvalidMoveException(const std::string& message) : SolitaireException(message) {}
};

class Board {
private:
    static const int SIZE = 7;
    char board[SIZE][SIZE];
    int pegs;

    bool isValidField(int row, int col) const {
        return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] != ' ';
    }

public:
    Board() : pegs(32) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if ((i < 2 || i > 4) && (j < 2 || j > 4)) {
                    board[i][j] = ' ';
                } else {
                    board[i][j] = 'o';
                }
            }
        }
        board[3][3] = '.';
    }

    int getPegs() const { return pegs; }

    bool canMove() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] != 'o') continue;
                if (i > 1 && board[i-1][j] == 'o' && board[i-2][j] == '.') return true;
                if (i < SIZE-2 && board[i+1][j] == 'o' && board[i+2][j] == '.') return true;
                if (j > 1 && board[i][j-1] == 'o' && board[i][j-2] == '.') return true;
                if (j < SIZE-2 && board[i][j+1] == 'o' && board[i][j+2] == '.') return true;
            }
        }
        return false;
    }

    void makeMove(int row, int col, char direction) {
        if (!isValidField(row, col)) {
            throw InvalidMoveException("Invalid field selected.");
        }
        if (board[row][col] != 'o') {
            throw InvalidMoveException("No peg at selected position.");
        }

        int dr = 0, dc = 0, mr = 0, mc = 0;
        switch (std::toupper(direction)) {
            case 'U':
                dr = -2; mr = -1;
                break;
            case 'D':
                dr = 2; mr = 1;
                break;
            case 'L':
                dc = -2; mc = -1;
                break;
            case 'R':
                dc = 2; mc = 1;
                break;
            default:
                throw InvalidInputException("Invalid direction.");
        }

        int newRow = row + dr, newCol = col + dc;
        int midRow = row + mr, midCol = col + mc;

        if (!isValidField(newRow, newCol) || !isValidField(midRow, midCol)) {
            throw InvalidMoveException("Move goes to invalid field.");
        }
        if (board[midRow][midCol] != 'o' || board[newRow][newCol] != '.') {
            throw InvalidMoveException("Invalid move: check middle and destination.");
        }

        board[row][col] = '.';
        board[midRow][midCol] = '.';
        board[newRow][newCol] = 'o';
        --pegs;
    }

    void display() const {
        std::cout << "  A B C D E F G\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << i + 1 << ' ';
            for (int j = 0; j < SIZE; ++j) {
                std::cout << (board[i][j] == ' ' ? ' ' : board[i][j]) << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "Pegs remaining: " << pegs << '\n';
    }
};

void parseCommand(const std::string& input, int& row, int& col, char& direction) {
    if (input.length() < 3) {
        throw InvalidInputException("Input too short.");
    }

    char colChar = std::toupper(input[0]);
    if (colChar < 'A' || colChar > 'G') {
        throw InvalidInputException("Invalid column (A-G expected).");
    }
    col = colChar - 'A';

    if (!std::isdigit(input[1])) {
        throw InvalidInputException("Invalid row (1-7 expected).");
    }
    row = input[1] - '1';
    if (row < 0 || row >= 7) {
        throw InvalidInputException("Row out of range (1-7 expected).");
    }

    direction = std::toupper(input[2]);
    if (direction != 'L' && direction != 'R' && direction != 'U' && direction != 'D') {
        throw InvalidInputException("Invalid direction (L, R, U, D expected).");
    }
}

int main() {
    Board board;
    std::string input;
    time_t startTime = time(nullptr);

    std::cout << "Welcome to Solitaire!\n";
    std::cout << "Enter move (e.g., F4L) or 'quit' to exit.\n";

    while (true) {
        board.display();
        std::cout << "Your move: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            std::cout << "Game ended. You quit.\n";
            break;
        }

        try {
            int row, col;
            char direction;
            parseCommand(input, row, col, direction);
            board.makeMove(row, col, direction);

            if (board.getPegs() == 1) {
                board.display();
                std::cout << "Congratulations! You won with one peg remaining!\n";
                break;
            }
            if (!board.canMove()) {
                board.display();
                std::cout << "No more moves possible. You lost with " << board.getPegs() << " pegs remaining.\n";
                break;
            }
        } catch (const SolitaireException& e) {
            std::cout << "Error: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << '\n';
        }
    }

    time_t endTime = time(nullptr);
    std::cout << "Game duration: " << difftime(endTime, startTime) << " seconds.\n";
    return 0;
}
//g++ -o solitaire solitaire.cpp ./solitaire
