def track_guard_path(grid):
    start_pos = None
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == '^':
                start_pos = (i, j)
                break
        if start_pos:
            break
    
    if not start_pos:
        return 0
    
    grid = [list(row) for row in grid]
    row_len, col_len = len(grid), len(grid[0])
    
    directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
    current_dir = 0  
    
    visited = set()
    current_pos = start_pos
    visited.add(current_pos)
    
    while True:
        next_pos = (
            current_pos[0] + directions[current_dir][0],
            current_pos[1] + directions[current_dir][1]
        )
        
        if (next_pos[0] < 0 or next_pos[0] >= row_len or 
            next_pos[1] < 0 or next_pos[1] >= col_len):
            break
            
        if grid[next_pos[0]][next_pos[1]] == '#':
            current_dir = (current_dir + 1) % 4
        else:
            current_pos = next_pos
            visited.add(current_pos)
    
    return len(visited)

def print_path(grid, visited):
    grid_copy = [list(row) for row in grid]
    for i, j in visited:
        if grid_copy[i][j] not in {'^', '#'}:
            grid_copy[i][j] = 'X'
    return [''.join(row) for row in grid_copy]

with open('Day6\input.txt', 'r') as file:
    grid = [line.strip() for line in file]
result = track_guard_path(grid)
print(f"Number of distinct positions visited: {result}")
