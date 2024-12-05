def find_xmas_patterns(grid):
    rows = len(grid)
    cols = len(grid[0])
    count = 0
    
    def check_mas(row, col, d_row, d_col):
        """Check if MAS or SAM starts at position [row,col] in direction [d_row,d_col]"""
        if not (0 <= row + d_row * 2 < rows and 0 <= col + d_col * 2 < cols):
            return False
            
        # Check forward (MAS)
        forward = (
            grid[row][col] == 'M' and
            grid[row + d_row][col + d_col] == 'A' and
            grid[row + d_row * 2][col + d_col * 2] == 'S'
        )
        
        # Check backward (SAM)
        backward = (
            grid[row][col] == 'S' and
            grid[row + d_row][col + d_col] == 'A' and
            grid[row + d_row * 2][col + d_col * 2] == 'M'
        )
        
        return forward or backward

    for row in range(1, rows-1):  
        for col in range(1, cols-1):
            if grid[row][col] == 'A':  
                top_left = check_mas(row-1, col-1, 1, 1)
                bottom_right = check_mas(row-1, col-1, 1, 1)
                top_right = check_mas(row-1, col+1, 1, -1)
                bottom_left = check_mas(row-1, col+1, 1, -1)
                
                if (top_left or bottom_right) and (top_right or bottom_left):
                    count += 1
    
    return count

with open('Day4\input.txt', 'r') as file:
    grid = [line.strip() for line in file.readlines()]

result = find_xmas_patterns(grid)
print(f"Found {result} X-MAS patterns")