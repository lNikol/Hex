A sequence of responses, at least one for each test case, separated by whitespace. Possible responses for each test case are as follows:

    BOARD_SIZE - a number from the range <1;11> indicating the size of the board. (sample output - test 1)
    PAWNS_NUMBER - a number from the range <0;121> indicating the number of pawns of both players on the board. (sample output - test 2)
    IS_BOARD_CORRECT - a YES/NO response indicating whether the state of the board is correct, in other words, whether the number of pawns of one player is appropriate relative to the number of pawns of the other player. (sample output - test 3)
    IS_GAME_OVER - a YES RED/YES BLUE/NO response indicating whether (and if so, which) player has ended the game, i.e., whether they have connected two edges of the board with an uninterrupted path of their color. (sample output - test 4)
    IS_BOARD_POSSIBLE - a YES/NO response indicating whether the state of the board is possible. This means that the board is correct and that achieving such a state did not result in overlooking an earlier win by one of the players. (sample output - test 5)
    CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT (...) - a YES/NO response indicating whether one of the players can end the game in N (where N belongs to <1;2>) moves when playing against a naive opponent (making the worst possible moves for themselves). The number of moves N indicates the number of moves by the player for whom we are considering victory. Victory must occur in the Nth move, which means that the player must have the ability to make such a number of moves.
    For example, if we are checking whether the red player can win in N = 2 moves and the current move belongs to the blue player, both players will make two moves. In the case where the current move belongs to the red player, the red player will make two moves and the blue player only one. (sample output - test 6)
    CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT (...) - analogous case to the previous one, with the difference that the player checks whether they can end the game playing against a perfect opponent (making the best possible moves for themselves) in N (where N belongs to <1;2>) moves. (sample output - test 7)

If a player wins in one move, it does not mean that they automatically win in two moves. In the case where they play against a perfect opponent and if they do not make the only move that leads to their victory in their first move, the opponent can block them in the next move (see: interesting case no. 3). We assume that the player always plays optimally to win in the move we are asking about (first or second), and their opponent plays to win as quickly as possible, so if they can win in the first move, they will.

If player X wins in N moves against a perfect opponent Y, then Y never wins against X (in any possible number of moves).

Note!!! - for cases from the third to the seventh, if the state of the board is incorrect (IS_BOARD_CORRECT), the algorithm should always return: NO.

For the last two cases, you can apply the Mini-Max algorithm. For a given position, generate all moves for the first player, and then all responses for their opponent, and so on. This tree can be maximally nested to 4 levels (the case when we consider 2 moves for the player whose move it is not). You must have, of course, an implemented generator of all possible moves generating an array/list of successive game states with an added new pawn and changed current player, and a game end detector (if a player connects both ends of the board). 


**Input example:**

---
<   >
 ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

    ---
 --<   >--
<   >-<   >
 --<   >--
    ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

    ---
 --< r >--
<   >-<   >
 --<   >--
    ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

    ---
 --< b >--
<   >-< r >
 --<   >--
    ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
