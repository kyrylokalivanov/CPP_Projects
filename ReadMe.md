# CPP_Projects

A collection of C++ projects developed to showcase skills in game programming and data structure implementation. This repository contains various projects, primarily built using standard C++ (C++17 or later), with a focus on practical applications, including classic games and fundamental data structures for coursework assignments.

## Description

This is a repository that serves as a portfolio of C++ projects created to demonstrate proficiency in C++ programming. Each project is housed in its own subdirectory and includes a dedicated `README.md` file with specific details about its functionality, setup, and usage. The projects cover a range of topics, including:

- Console-based game development (Chess, Solitaire).
- Data structure implementations (Singly Linked List, Queue, Stack).
- Arithmetic operations with rational numbers.

The repository is designed to be a centralized hub for exploring, compiling, and running these C++ projects.

## Requirements

To build and run the projects in this repository, you need:

- **C++ Compiler** (supporting C++17 or later, e.g., g++, MSVC, Clang).
- **CMake** (version 3.10 or later) for building projects.
- **IDE** (recommended: Visual Studio 2022, CLion, or Visual Studio Code) or a terminal for compilation.
- **Operating System**: Windows, macOS, or Linux.
- **Dependencies**:
  - Standard C++ library (included with the compiler).
  - Check individual project `README.md` files for additional dependencies, if any.

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/kyrylokalivanov/CPP_Projects.git
   ```
2. **Navigate to a Project**:
   - Each project is in its own subdirectory (e.g., `Chess`).
   - Change to the desired project directory:
     ```bash
     cd CPP_Projects/Chess
     ```
3. **Compile the Project**:
   - Compile the source files using `g++`:
     ```bash
     g++ -std=c++17 main.cpp -o Chess
     ```
   - Refer to the project’s `README.md` for specific compilation instructions if multiple source files or additional flags are required.
4. **Run the Executable**:
   - Execute the compiled program:
     ```bash
     ./Chess
     ```
   - On Windows, use:
     ```bash
     Chess.exe
     ```

## Usage

Each project has its own usage instructions detailed in its respective `README.md` file. Generally:

1. Navigate to the project directory (e.g., `ChessProject/Chess`).
2. Build the project using CMake and a compatible compiler (see Installation).
3. Run the executable to interact with the program (e.g., play the Chess game or test the Rational Numbers library).
4. Refer to the project’s `README.md` for specific inputs, outputs, or interactions.

### Projects Overview

- **Chess**:
  - A console-based Chess game implementing standard rules, including piece movements, captures, and checkmate detection.
  - Demonstrates object-oriented programming with classes for pieces and the game board.
  - See `Chess/README.md` for details.

- **Rational Numbers**:
  - A library for arithmetic operations on rational numbers (fractions), with support for addition, subtraction, multiplication, and division.
  - Includes fraction simplification and error handling.
  - See `RationalNumbers/README.md` for details.

- **Singly Linked List, Queue, and Stack**:
  - Template-based implementations of a Singly Linked List, Queue, and Stack with standard operations.
  - Focuses on efficient memory management and generic programming.
  - See `LinkedListQueueStack/README.md` for details.

- **Solitaire**:
  - A console-based Klondike Solitaire card game with tableau piles, foundation piles, and a draw pile.
  - Implements standard Solitaire rules and user interaction.
  - See `Solitaire/README.md` for details.

## License

This projects are for educational purposes and does not include a specific license. Feel free to use and modify the code for learning or personal projects.
