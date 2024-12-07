def find_loop_positions(grid):
    grid = [list(row) for row in grid]
    rows, cols = len(grid), len(grid[0])
    
    directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
    
    def get_start_position():
        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == '^':
                    return (i, j)
        return None
    
    def simulate_path(obstruction_pos=None):
        test_grid = [row[:] for row in grid]
        if obstruction_pos:
            test_grid[obstruction_pos[0]][obstruction_pos[1]] = '#'
            
        current_pos = get_start_position()
        current_dir = 0
        
        path = []
        visited_states = set()  
        
        while current_pos:
            state = (current_pos[0], current_pos[1], current_dir)
            
            if state in visited_states:
                return True
            
            visited_states.add(state)
            path.append(current_pos)
            
            next_pos = (
                current_pos[0] + directions[current_dir][0],
                current_pos[1] + directions[current_dir][1]
            )
            
            if (next_pos[0] < 0 or next_pos[0] >= rows or 
                next_pos[1] < 0 or next_pos[1] >= cols):
                return False
                
            if test_grid[next_pos[0]][next_pos[1]] == '#':
                current_dir = (current_dir + 1) % 4
            else:
                current_pos = next_pos
        
        return False
    
    start_pos = get_start_position()
    original_path = set()
    current_pos = start_pos
    current_dir = 0
    
    while current_pos:
        original_path.add(current_pos)
        next_pos = (
            current_pos[0] + directions[current_dir][0],
            current_pos[1] + directions[current_dir][1]
        )
        
        if (next_pos[0] < 0 or next_pos[0] >= rows or 
            next_pos[1] < 0 or next_pos[1] >= cols):
            break
            
        if grid[next_pos[0]][next_pos[1]] == '#':
            current_dir = (current_dir + 1) % 4
        else:
            current_pos = next_pos
    
    loop_positions = set()
    for pos in original_path:
        if grid[pos[0]][pos[1]] not in {'^', '#'}: 
            if simulate_path(pos):
                loop_positions.add(pos)
    
    print(len(loop_positions))
    return len(loop_positions)


with open('Day6\input.txt', 'r') as file:
    grid = [line.strip() for line in file]

find_loop_positions(grid)