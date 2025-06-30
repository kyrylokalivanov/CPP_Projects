# Chess Game

## Project Description

This project is a console-based chess game written in C++ (C++11 standard), designed for two players to play in a text-based interface. The game implements the core rules of chess, including movements for all pieces (king, queen, rook, bishop, knight, pawn), short and long castling, en passant capture, and detection of check and checkmate. Players input moves using algebraic notation (e.g., `e2e4` or `O-O` for castling). The chessboard is displayed in the console using a text-based format with coordinates (a-h, 1-8). The program is designed with object-oriented programming principles and design patterns, ensuring modularity and extensibility.

The project was developed as part of an object-oriented programming course, with the goal of creating a functional chess game that emphasizes the use of design patterns and correct implementation of chess rules.

## Design Patterns

### Explicit Design Patterns

1. **Singleton (ChessGame)**  
   The `ChessGame` class is implemented as a singleton, ensuring a single instance of the game exists. This provides global access to the game state and turn management through the `getInstance()` method.

2. **Factory Method (PieceFactory)**  
   The abstract `PieceFactory` class and its derived classes (`KingFactory`, `QueenFactory`, `RookFactory`, `BishopFactory`, `KnightFactory`, `PawnFactory`) are used to create chess pieces based on their type and color. This pattern enhances flexibility when adding new piece types.

3. **Strategy (MoveStrategy)**  
   The `MoveStrategy` interface defines the movement rules for chess pieces, with derived classes (`KingMoveStrategy`, `QueenMoveStrategy`, `RookMoveStrategy`, `BishopMoveStrategy`, `KnightMoveStrategy`, `PawnMoveStrategy`) implementing specific movement logic for each piece type. This pattern separates movement logic from piece representation.

### Implicit Design Patterns

1. **Template Method (ChessGame::makeMove)**  
   The `makeMove` method acts as a template, defining the general algorithm for executing a move: validating the move, performing the move, checking for check/checkmate, and switching turns. Specific steps are delegated to other methods, such as `isValidMove` and `isCheck`.

2. **Adapter (Piece)**  
   The `Piece` class adapts a general piece interface (`isValidMove`) to different movement strategies (`MoveStrategy`), enabling uniform handling of all piece types.

## File Structure

- **chess.cpp**: The main source file containing the complete implementation of the chess game, including the game logic, piece movement strategies, and console-based user interface.

- **Diagramma.png**: The diagram of classes in chess.cpp.

## Usage

1. Compile the program using a C++11-compliant compiler (e.g., `g++ -std=c++11 chess.cpp -o chess`).
2. Run the executable (`./chess` on Unix-like systems or `chess.exe` on Windows).
3. The game displays the initial chessboard and prompts the current player (White or Black) for a move.
4. Enter moves in algebraic notation (e.g., `e2e4` for moving a piece from e2 to e4, or `O-O` for short castling, `O-O-O` for long castling).
5. The game validates the move, updates the board, checks for check/checkmate, and alternates turns until checkmate occurs or the game is interrupted.

## Requirements

- C++11-compliant compiler (e.g., GCC, Clang, MSVC)
- Standard C++ library

## Notes

- The game currently supports only the core chess rules and does not implement advanced features like stalemate detection, threefold repetition, or pawn promotion.
- The console-based interface uses ASCII characters to represent pieces (uppercase for White, lowercase for Black).
- The program is designed for modularity, making it easy to extend with additional features or a graphical interface.

## License

This project is for educational purposes and does not include a specific license. Feel free to use and modify the code for learning or personal projects.
