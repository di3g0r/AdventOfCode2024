def find_xmas_occurrences(grid):
    rows = len(grid)
    cols = len(grid[0])
    count = 0
    
    directions = [
        [-1, -1], [-1, 0], [-1, 1],  # Up-left, Up, Up-right
        [0, -1],           [0, 1],    # Left, Right
        [1, -1],  [1, 0],  [1, 1]     # Down-left, Down, Down-right
    ]
    
    def check_word(row, col, d_row, d_col):
        """Check if XMAS starts at position [row,col] in direction [d_row,d_col]"""
        word = "XMAS"
        
        if not (0 <= row + d_row * 3 < rows and 0 <= col + d_col * 3 < cols):
            return False
            
        for i, char in enumerate(word):
            if grid[row + d_row * i][col + d_col * i] != char:
                return False
        return True
    
    for row in range(rows):
        for col in range(cols):
            for d_row, d_col in directions:
                if check_word(row, col, d_row, d_col):
                    count += 1
    
    return count

with open('Day4\input.txt', 'r') as file:
    grid = [line.strip() for line in file.readlines()]

result = find_xmas_occurrences(grid)
print(f"Found {result} occurrences of XMAS")