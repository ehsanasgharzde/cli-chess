# Command-Line Chess (C++)

This is a simple command-line chess game implemented in C++. It allows two players to play chess against each other using the command line interface.

## How to Play

1. Compile the Code:
   - Make sure you have a C++ compiler installed on your system.
   - Compile the code using your preferred compiler. For example:
     ```
     g++ main.cpp -o chess
     ```

2. Run the Game:
   - Execute the compiled binary:
     ```
     ./chess
     ```

3. Game Rules:
   - The game enforces standard chess rules, including piece movement, captures, castling, and pawn promotion.
   - Follow the on-screen prompts to input your moves in the format: "sourceRow sourceColumn destinationRow destinationColumn."
   - The game will display the chessboard and update it after each move.
   - The game continues until one player's king is captured (checkmate), and the winning player is announced.

4. Pawn Promotion:
   - When a pawn reaches the opponent's back rank, you'll be prompted to choose a piece for promotion (Rook, Bishop, Queen, Knight).

5. Enjoy the Game:
   - Have fun playing chess with a friend using the command line!

## Files
- `main.cpp`: Contains the C++ source code for the chess game.

## Game Features
- Text-based command-line interface.
- Move validation for all chess pieces (Rook, Knight, Bishop, Queen, King, and Pawn).
- Checks for valid moves, piece captures, and game-ending conditions.
- Pawn promotion when a pawn reaches the opposite end of the board.


Feel free to modify, enhance, or customize the game as you like. Happy gaming!
