def parse_input(filename):
    """Parse the input file to get the map and movement instructions."""
    with open(filename) as f:
        sections = f.read().split('\n\n')
    grid = sections[0].split('\n')
    moves = ''.join(sections[1].split()) 
    return grid, moves

def find_robot():
    """Find the initial position of the robot (@) in the grid."""
    for r in range(len(grid)):
        for c in range(len(grid[0])):
            if grid[r][c] == '@':
                return r, c
    return None

def simulate_movement():
    r, c = find_robot()
    grid_list = [list(row) for row in grid]  
    
    for move in moves:
        dr = -1 if move == '^' else 1 if move == 'v' else 0
        dc = -1 if move == '<' else 1 if move == '>' else 0
        
        targets = [(r, c)] 
        cr, cc = r, c 
        go = True
        
        while True:
            cr += dr
            cc += dc
            char = grid_list[cr][cc]
            
            if char == '#': 
                go = False
                break
            elif char == 'O':  
                targets.append((cr, cc))
                continue
            elif char == '.':  
                break
        
        if not go:  
            continue
            
        grid_list[r][c] = '.' 
        grid_list[r + dr][c + dc] = '@' 
        
        for br, bc in targets[1:]:
            grid_list[br + dr][bc + dc] = 'O'
        
        r += dr
        c += dc
    
    return [''.join(row) for row in grid_list]

def calculate_gps_sum(final_grid):
    """Calculate the sum of GPS coordinates for all boxes."""
    total = 0
    for r in range(len(final_grid)):
        for c in range(len(final_grid[0])):
            if final_grid[r][c] == 'O':
                total += (100 * r + c)
    return total

grid, moves = parse_input("Day15\input.txt")

final_grid = simulate_movement()

result = calculate_gps_sum(final_grid)
print(f"The sum of all boxes' GPS coordinates is: {result}")