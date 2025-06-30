#include <iostream>
#include <vector>
#include <memory>
#include <string>

enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };
enum class Color { WHITE, BLACK };

class Piece;

// pattern singelton ()
class ChessGame {
private:
    static ChessGame* instance;
    std::vector<std::vector<char>> board;
    Color currentTurn;
    bool whiteKingMoved, whiteLeftRookMoved, whiteRightRookMoved;
    bool blackKingMoved, blackLeftRookMoved, blackRightRookMoved;
    int lastPawnDoubleMoveY; // en persant

    ChessGame() : currentTurn(Color::WHITE), whiteKingMoved(false), whiteLeftRookMoved(false), whiteRightRookMoved(false),
    blackKingMoved(false), blackLeftRookMoved(false), blackRightRookMoved(false), lastPawnDoubleMoveY(-1) {
        board = std::vector<std::vector<char>>(8, std::vector<char>(8, '.'));
        initializeBoard();
    }

public:
    static ChessGame& getInstance() {
        if (!instance) instance = new ChessGame();
        return *instance;
    }

    Color getCurrentTurn() const {
        return currentTurn;
    }

    void initializeBoard() {
        board[0] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' }; // czarne figury
        for (int i = 0; i < 8; i++) board[1][i] = 'p'; // czarne pionki
        for (int i = 2; i < 6; i++) for (int j = 0; j < 8; j++) board[i][j] = '.'; // puste
        for (int i = 0; i < 8; i++) board[6][i] = 'P'; // białe pionki
        board[7] = { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }; // białe figury
    }

    void displayBoard() {
        std::cout << "  a b c d e f g h\n";
        for (int i = 0; i < 8; i++) {
            std::cout << 8 - i << " ";
            for (char cell : board[i]) {
                std::cout << cell << " ";
            }
            std::cout << 8 - i << std::endl;
        }
        std::cout << "  a b c d e f g h\n";
    }

    bool isCheck(Color kingColor) {
        int kingX = -1, kingY = -1;
        char kingSymbol = kingColor == Color::WHITE ? 'K' : 'k';
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == kingSymbol) {
                    kingX = i;
                    kingY = j;
                    break;
                }
            }
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] != '.' && (kingColor == Color::WHITE ? islower(board[i][j]) : isupper(board[i][j]))) {
                    if (isValidMove(i, j, kingX, kingY, board)) return true;
                }
            }
        }
        return false;
    }

    bool isCheckmate(Color kingColor) {
        if (!isCheck(kingColor)) return false;
        for (int fromX = 0; fromX < 8; fromX++) {
            for (int fromY = 0; fromY < 8; fromY++) {
                if (board[fromX][fromY] != '.' && (kingColor == Color::WHITE ? isupper(board[fromX][fromY]) : islower(board[fromX][fromY]))) {
                    for (int toX = 0; toX < 8; toX++) {
                        for (int toY = 0; toY < 8; toY++) {
                            if (isValidMove(fromX, fromY, toX, toY, board)) {
                                char temp = board[toX][toY];
                                char piece = board[fromX][fromY];
                                board[toX][toY] = piece;
                                board[fromX][fromY] = '.';
                                bool stillCheck = isCheck(kingColor);
                                board[fromX][fromY] = piece;
                                board[toX][toY] = temp;
                                if (!stillCheck) return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board) const;

    bool makeMove(int fromX, int fromY, int toX, int toY) {
        if (!isValidMove(fromX, fromY, toX, toY, board)) return false;

        char piece = board[fromX][fromY];
        // spawdzamie roszady
        if (piece == 'K' && std::abs(toY - fromY) == 2) {
            if (isCheck(Color::WHITE)) return false;
            if (toY == 6 && !whiteKingMoved && !whiteRightRookMoved) { // krótka roszada
                board[7][6] = 'K';
                board[7][5] = 'R';
                board[7][4] = '.';
                board[7][7] = '.';
                whiteKingMoved = true;
                whiteRightRookMoved = true;
            } else if (toY == 2 && !whiteKingMoved && !whiteLeftRookMoved) { // długa roszada
                board[7][2] = 'K';
                board[7][3] = 'R';
                board[7][4] = '.';
                board[7][0] = '.';
                whiteKingMoved = true;
                whiteLeftRookMoved = true;
            } else {
                return false;
            }
        } else if (piece == 'k' && std::abs(toY - fromY) == 2) {
            if (isCheck(Color::BLACK)) return false;
            if (toY == 6 && !blackKingMoved && !blackRightRookMoved) { // krótka roszada
                board[0][6] = 'k';
                board[0][5] = 'r';
                board[0][4] = '.';
                board[0][7] = '.';
                blackKingMoved = true;
                blackRightRookMoved = true;
            } else if (toY == 2 && !blackKingMoved && !blackLeftRookMoved) { // długa roszada
                board[0][2] = 'k';
                board[0][3] = 'r';
                board[0][4] = '.';
                board[0][0] = '.';
                blackKingMoved = true;
                blackLeftRookMoved = true;
            } else {
                return false;
            }
        } else {
            // sprawdzamy czy
            char temp = board[toX][toY];
            board[toX][toY] = piece;
            board[fromX][fromY] = '.';
            bool inCheck = isCheck(currentTurn);
            board[fromX][fromY] = piece;
            board[toX][toY] = temp;
            if (inCheck) return false;

            // en passant (Bicie w przelocie)
            if ((piece == 'P' || piece == 'p') && std::abs(toY - fromY) == 1 && board[toX][toY] == '.' && toY == lastPawnDoubleMoveY) {
                int pawnX = (piece == 'P') ? toX + 1 : toX - 1;
                board[pawnX][toY] = '.';
            }

            // sprawdzamy podwójny ruch pionka
            if ((piece == 'P' && fromX == 6 && toX == 4) || (piece == 'p' && fromX == 1 && toX == 3)) {
                lastPawnDoubleMoveY = toY;
            } else {
                lastPawnDoubleMoveY = -1;
            }

            // dla roszady
            if (piece == 'K') whiteKingMoved = true;
            if (piece == 'k') blackKingMoved = true;
            if (piece == 'R' && fromX == 7 && fromY == 0) whiteLeftRookMoved = true;
            if (piece == 'R' && fromX == 7 && fromY == 7) whiteRightRookMoved = true;
            if (piece == 'r' && fromX == 0 && fromY == 0) blackLeftRookMoved = true;
            if (piece == 'r' && fromX == 0 && fromY == 7) blackRightRookMoved = true;

            // robimy ruch
            board[toX][toY] = piece;
            board[fromX][fromY] = '.';
        }

        // sprawdzamy szach i mat
        Color opponent = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        if (isCheck(opponent)) {
            std::cout << (opponent == Color::WHITE ? "White is in check!\n" : "Black is in check!\n");
            if (isCheckmate(opponent)) {
                std::cout << "Checkmate! " << (opponent == Color::WHITE ? "Black wins!\n" : "White wins!\n");
                return false; // koniec gry
            }
        }

        // czieniamy róch tylko jeżeli gra nie skończona
        currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
        return true;
    }
};

// pattern strategy
class MoveStrategy {
public:
    virtual bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame& game) = 0;
    virtual ~MoveStrategy() = default;
};

class KingMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame& game) override {
        int dx = std::abs(toX - fromX);
        int dy = std::abs(toY - fromY);
        // sprawdzamy czy
        auto boardCopy = board;
        boardCopy[toX][toY] = board[fromX][fromY];
        boardCopy[fromX][fromY] = '.';
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (boardCopy[i][j] != '.' && (color == Color::WHITE ? islower(boardCopy[i][j]) : isupper(boardCopy[i][j]))) {
                    if (game.isValidMove(i, j, toX, toY, boardCopy)) return false;
                }
            }
        }
        // Обычный ход короля
        if (dx <= 1 && dy <= 1 && (dx > 0 || dy > 0)) {
            return board[toX][toY] == '.' || (color == Color::WHITE ? islower(board[toX][toY]) : isupper(board[toX][toY]));
        }
        // Рокировка
        if (dx == 0 && dy == 2 && fromX == (color == Color::WHITE ? 7 : 0)) {
            if (toY == 6 && board[fromX][7] == (color == Color::WHITE ? 'R' : 'r')) { // krótka roszada
                return board[fromX][5] == '.' && board[fromX][6] == '.';
            }
            if (toY == 2 && board[fromX][0] == (color == Color::WHITE ? 'R' : 'r')) { // długa roszada
                return board[fromX][1] == '.' && board[fromX][2] == '.' && board[fromX][3] == '.';
            }
        }
        return false;
    }
};

class QueenMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame&) override {
        int dx = std::abs(toX - fromX);
        int dy = std::abs(toY - fromY);
        if (dx == 0 || dy == 0 || dx == dy) {
            int stepX = (toX == fromX) ? 0 : (toX > fromX ? 1 : -1);
            int stepY = (toY == fromY) ? 0 : (toY > fromY ? 1 : -1);
            int x = fromX + stepX, y = fromY + stepY;
            while (x != toX || y != toY) {
                if (board[x][y] != '.') return false;
                x += stepX;
                y += stepY;
            }
            return board[toX][toY] == '.' || (color == Color::WHITE ? islower(board[toX][toY]) : isupper(board[toX][toY]));
        }
        return false;
    }
};

class RookMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame&) override {
        if (fromX != toX && fromY != toY) return false;
        int stepX = (toX == fromX) ? 0 : (toX > fromX ? 1 : -1);
        int stepY = (toY == fromY) ? 0 : (toY > fromY ? 1 : -1);
        int x = fromX + stepX, y = fromY + stepY;
        while (x != toX || y != toY) {
            if (board[x][y] != '.') return false;
            x += stepX;
            y += stepY;
        }
        return board[toX][toY] == '.' || (color == Color::WHITE ? islower(board[toX][toY]) : isupper(board[toX][toY]));
    }
};

class BishopMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame&) override {
        int dx = std::abs(toX - fromX);
        int dy = std::abs(toY - fromY);
        if (dx != dy) return false;
        int stepX = toX > fromX ? 1 : -1;
        int stepY = toY > fromY ? 1 : -1;
        int x = fromX + stepX, y = fromY + stepY;
        while (x != toX && y != toY) {
            if (board[x][y] != '.') return false;
            x += stepX;
            y += stepY;
        }
        return board[toX][toY] == '.' || (color == Color::WHITE ? islower(board[toX][toY]) : isupper(board[toX][toY]));
    }
};

class KnightMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame&) override {
        int dx = std::abs(toX - fromX);
        int dy = std::abs(toY - fromY);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
};

class PawnMoveStrategy : public MoveStrategy {
public:
    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, Color color, const ChessGame&) override {
        int direction = (color == Color::WHITE) ? -1 : 1;
        int startRow = (color == Color::WHITE) ? 6 : 1;
        // 1
        if (fromY == toY && toX == fromX + direction && board[toX][toY] == '.') return true;
        // 2
        if (fromX == startRow && fromY == toY && toX == fromX + 2 * direction && board[toX][toY] == '.' && board[fromX + direction][toY] == '.') return true;
        // bicie
        if (std::abs(toY - fromY) == 1 && toX == fromX + direction && board[toX][toY] != '.' && (color == Color::WHITE ? islower(board[toX][toY]) : isupper(board[toX][toY]))) return true;
        // bicie w przelioci
        if (std::abs(toY - fromY) == 1 && toX == fromX + direction && board[toX][toY] == '.' && board[fromX][toY] == (color == Color::WHITE ? 'p' : 'P')) {
            return true;
        }
        return false;
    }
};

class Piece {
protected:
    PieceType type;
    Color color;
    std::unique_ptr<MoveStrategy> moveStrategy;

public:
    Piece(PieceType t, Color c, std::unique_ptr<MoveStrategy> strategy)
    : type(t), color(c), moveStrategy(std::move(strategy)) {}

    bool isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board, const ChessGame& game) {
        return moveStrategy->isValidMove(fromX, fromY, toX, toY, board, color, game);
    }

    char getSymbol() const {
        switch (type) {
            case PieceType::KING: return color == Color::WHITE ? 'K' : 'k';
            case PieceType::QUEEN: return color == Color::WHITE ? 'Q' : 'q';
            case PieceType::ROOK: return color == Color::WHITE ? 'R' : 'r';
            case PieceType::BISHOP: return color == Color::WHITE ? 'B' : 'b';
            case PieceType::KNIGHT: return color == Color::WHITE ? 'N' : 'n';
            case PieceType::PAWN: return color == Color::WHITE ? 'P' : 'p';
            default: return '.';
        }
    }
};

// pattern Factory
class PieceFactory {
public:
    virtual std::unique_ptr<Piece> createPiece(Color color) = 0;
    virtual ~PieceFactory() = default;
};

class KingFactory : public PieceFactory {
public:
    std::unique_ptr<Piece> createPiece(Color color) override {
        return std::make_unique<Piece>(PieceType::KING, color, std::make_unique<KingMoveStrategy>());
    }
};

class QueenFactory : public PieceFactory {
public:
    std::unique_ptr<Piece> createPiece(Color color) override {
        return std::make_unique<Piece>(PieceType::QUEEN, color, std::make_unique<QueenMoveStrategy>());
    }
};

class RookFactory : public PieceFactory {
public:
    std::unique_ptr<Piece> createPiece(Color color) override {
        return std::make_unique<Piece>(PieceType::ROOK, color, std::make_unique<RookMoveStrategy>());
    }
};

class BishopFactory : public PieceFactory {
public:
    std::unique_ptr<Piece> createPiece(Color color) override {
        return std::make_unique<Piece>(PieceType::BISHOP, color, std::make_unique<BishopMoveStrategy>());
    }
};

class KnightFactory : public PieceFactory {
public:
    std::unique_ptr<Piece> createPiece(Color color) override {
        return std::make_unique<Piece>(PieceType::KNIGHT, color, std::make_unique<KnightMoveStrategy>());
    }
};

class PawnFactory : public PieceFactory {
public:
    std::unique_ptr<Piece> createPiece(Color color) override {
        return std::make_unique<Piece>(PieceType::PAWN, color, std::make_unique<PawnMoveStrategy>());
    }
};

// sprawdzamy isValidMove po Piece i MoveStrategy
bool ChessGame::isValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<char>>& board) const {
    if (fromX < 0 || fromX >= 8 || fromY < 0 || fromY >= 8 || toX < 0 || toX >= 8 || toY < 0 || toY >= 8)
        return false;

    char piece = board[fromX][fromY];
    if (piece == '.') return false;

    if ((currentTurn == Color::WHITE && !isupper(piece)) || (currentTurn == Color::BLACK && !islower(piece)))
        return false;

    if (board[toX][toY] != '.' && ((isupper(piece) && isupper(board[toX][toY])) || (islower(piece) && islower(board[toX][toY]))))
        return false;

    std::unique_ptr<PieceFactory> factory;
    if (piece == 'K' || piece == 'k') factory = std::make_unique<KingFactory>();
    else if (piece == 'Q' || piece == 'q') factory = std::make_unique<QueenFactory>();
    else if (piece == 'R' || piece == 'r') factory = std::make_unique<RookFactory>();
    else if (piece == 'B' || piece == 'b') factory = std::make_unique<BishopFactory>();
    else if (piece == 'N' || piece == 'n') factory = std::make_unique<KnightFactory>();
    else if (piece == 'P' || piece == 'p') factory = std::make_unique<PawnFactory>();
    else return false;

    auto p = factory->createPiece(isupper(piece) ? Color::WHITE : Color::BLACK);
    return p->isValidMove(fromX, fromY, toX, toY, board, *this);
}

ChessGame* ChessGame::instance = nullptr;

int main() {
    ChessGame& game = ChessGame::getInstance();
    game.displayBoard();

    while (true) {
        std::cout << (game.getCurrentTurn() == Color::WHITE ? "White's turn" : "Black's turn") << ": ";
        std::string move;
        std::cin >> move;

        // parsing ruchu
        if (move == "O-O" || move == "O-O-O") {
            int fromX = (game.getCurrentTurn() == Color::WHITE) ? 7 : 0;
            int toX = fromX;
            int toY = (move == "O-O") ? 6 : 2;
            if (game.makeMove(fromX, 4, toX, toY)) {
                game.displayBoard();
            } else {
                std::cout << "Invalid castling!\n";
            }
            continue;
        }

        if (move.length() != 4) {
            std::cout << "Invalid input format! Use e2e4 style.\n";
            continue;
        }

        int fromY = move[0] - 'a';
        int fromX = 8 - (move[1] - '0');
        int toY = move[2] - 'a';
        int toX = 8 - (move[3] - '0');

        if (!game.makeMove(fromX, fromY, toX, toY)) {
            if (game.isCheckmate(game.getCurrentTurn() == Color::WHITE ? Color::BLACK : Color::WHITE)) {
                break; // gra już skończona w makeMove
            }
            std::cout << "Invalid move!\n";
            continue;
        }
        game.displayBoard();
    }

    return 0;
}
