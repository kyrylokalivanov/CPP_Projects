Project description

The project is a console chess game written in C++ (C++11 standard) that allows two players to play in text mode. The game implements the basic rules of chess, including the movements of all pieces (king, queen, rook, bishop, knight, pawn), short and long castling, en passant, and checking and checkmating. Users enter moves in algebraic notation (e.g., e2e4 or O-O for castling). The chessboard is displayed in the console in text format, with field markings (a-h, 1-8). The program was designed using the object-oriented paradigm and design patterns, which ensures modularity and expandability.

The project was created as part of an object-oriented programming course. Its goal was to create a functional chess game with an emphasis on the use of design patterns and the correct implementation of the rules of the game.
Design patterns
Explicit design patterns

Singleton (ChessGame)
The ChessGame class is a singleton, providing a single instance of the game. It allows global access to the chessboard state and turn management through the getInstance() method.
    Factory Method (PieceFactory)
        The abstract PieceFactory class and its derivatives (KingFactory, QueenFactory, RookFactory, BishopFactory, KnightFactory, PawnFactory) are used to create chess pieces depending on their type and color. This pattern increases flexibility when adding new pieces.
    Strategy (MoveStrategy)
        The MoveStrategy interface defines the rules for moving pieces, and the derived classes (KingMoveStrategy, QueenMoveStrategy, RookMoveStrategy, BishopMoveStrategy, KnightMoveStrategy, PawnMoveStrategy) implement specific logic for each piece. This pattern separates the movement logic from the representation of the pieces.

Implicit design patterns

Template Method (ChessGame::makeMove)
The makeMove method acts as a template, defining the general algorithm for executing a move: validity check, move execution, check/checkmate check, turn change. It delegates individual steps to other methods, such as isValidMove and isCheck.
    Adapter (Piece)
        The Piece class adapts the general interface of a piece (the isValidMove method) to different movement strategies (MoveStrategy), enabling uniform handling of pieces.
