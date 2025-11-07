"""
N-Queens Problem - CSP Sprint Challenge
Difficulty: Medium
Interview companies: Google, Amazon, Meta, Apple

Your task: Complete the is_safe() and solve_nqueens() functions
"""

def print_board(board):
    """Prints the chessboard with Q for queens and . for empty"""
    n = len(board)
    for i in range(n):
        for j in range(n):
            if board[i][j] == 1:
                print("Q ", end="")
            else:
                print(". ", end="")
        print()

def initialize_board(n):
    """Creates an n x n board with all 0s"""
    return [[0 for _ in range(n)] for _ in range(n)]

def is_safe(board, row, col):
    """
    TODO: Implement this function!
    
    Check if it's safe to place a queen at board[row][col]
    
    A position is safe if no other queen can attack it:
    1. No queen in the same row (check left side of current row)
    2. No queen in upper left diagonal
    3. No queen in lower left diagonal
    
    Note: We don't need to check right side or other directions
    because we place queens column by column from left to right!
    
    Args:
        board: n x n 2D list (1 = queen, 0 = empty)
        row: row index to check
        col: column index to check
    
    Returns:
        True if safe to place queen, False otherwise
    
    Hints:
    - Check left in same row: loop from col-1 down to 0
    - Check upper left diagonal: row-1, col-1, then row-2, col-2, etc.
    - Check lower left diagonal: row+1, col-1, then row+2, col-2, etc.
    """
    n = len(board)
    
    # TODO: Check row on left side

    for i in range(col-1, -1, -1):
        if board[row][i] == 1:
            return False

    # TODO: Check upper left diagonal
    
    j = col - 1
    i = row - 1
    while j >= 0 and i >= 0:
        if board[i][j] == 1:
            return False
        j -= 1
        i -= 1
    
    # TODO: Check lower left diagonal
    j = col - 1
    i = row + 1
    while j >= 0 and i < n:
        if board[i][j] == 1:
            return False
        j -= 1
        i += 1
    
    return True  # Replace with your logic

def solve_nqueens_util(board, col):
    """
    TODO: Implement this function!
    
    Helper function that uses backtracking to place queens
    
    Algorithm:
    1. Base case: if col >= n, all queens are placed! Return True
    2. Try placing queen in each row of current column:
       a. Check if placement is safe (use is_safe helper)
       b. If safe, place the queen (board[row][col] = 1)
       c. Recursively try to place rest of queens (solve_nqueens_util(board, col+1))
       d. If recursive call succeeds, return True
       e. If recursive call fails, BACKTRACK (board[row][col] = 0)
    3. If all rows tried and none worked, return False
    
    Args:
        board: n x n 2D list
        col: current column we're trying to place a queen in
    
    Returns:
        True if solution found, False otherwise
    """
    n = len(board)
    
    # TODO: Base case - all queens placed
    if col >= n:
        return True
    
    # TODO: Try placing queen in each row of this column
    for row in range(n):
        if is_safe(board, row, col):
            board[row][col] = 1
            if solve_nqueens_util(board, col + 1):
                return True
            board[row][col] = 0  # Backtrack

    # TODO: If no placement worked, return False
    return False


# 4-queens
# solve_nqueens_util(board, 0)
# Goes 0,0, calls solve_nqueens_util(board, 1)


def solve_nqueens(n):
    """
    Main function to solve N-Queens problem
    
    Args:
        n: size of board (n x n)
    
    Returns:
        board with solution, or None if no solution
    """
    board = initialize_board(n)
    
    if solve_nqueens_util(board, 0):
        return board
    else:
        return None

def count_all_solutions(board, col, count=[0]):
    """
    BONUS: Count all possible solutions
    Modify this to find ALL solutions instead of just one
    """
    n = len(board)
    
    if col >= n:
        count[0] += 1
        print(f"\nSolution #{count[0]}:")
        print_board(board)
        return
    
    for row in range(n):
        if is_safe(board, row, col):
            board[row][col] = 1
            count_all_solutions(board, col + 1, count)
            board[row][col] = 0  # Backtrack

# Test cases
if __name__ == "__main__":
    # Test N=4
    print("Solving 4-Queens problem...")
    print("="*30)
    solution = solve_nqueens(4)
    
    if solution:
        print("\nSolution found!")
        print_board(solution)
    else:
        print("\nNo solution exists")
    
    # Test N=8 (classic problem)
    print("\n" + "="*30)
    print("Solving 8-Queens problem...")
    print("="*30)
    solution = solve_nqueens(8)
    
    if solution:
        print("\nSolution found!")
        print_board(solution)
    else:
        print("\nNo solution exists")
    
    # BONUS: Find all solutions for N=4
    print("\n" + "="*30)
    print("BONUS: All solutions for 4-Queens:")
    print("="*30)
    board = initialize_board(4)
    count = [0]
    count_all_solutions(board, 0, count)
    print(f"\nTotal solutions: {count[0]}")

"""
Expected output for N=4 (one possible solution):
. Q . .
. . . Q
Q . . .
. . Q .

Expected output for N=8 (one possible solution):
Q . . . . . . .
. . . . Q . . .
. . . . . . . Q
. . . . . Q . .
. . Q . . . . .
. . . . . . Q .
. Q . . . . . .
. . . Q . . . .

Total solutions for N=4: 2
"""
