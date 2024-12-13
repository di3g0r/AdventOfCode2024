from collections import deque

def solve(filename: str) -> int:
    # Read input
    with open(filename) as f:
        grid = [list(line.strip()) for line in f]
    

    directions = [(-1, 0), (0, -1), (1, 0), (0, 1)]
    
    outer_corners = [0, 0, 0, 1, 0, 0, 1, 2, 0, 1, 0, 2, 1, 2, 2, 4]
    

    check_inner_corners = [
        [(-1,-1), (-1,1), (1,-1), (1,1)],  
        [(1,-1), (1,1)],                    
        [(-1,1), (1,1)],                  
        [(1,1)],                         
        [(-1,-1), (-1,1)],             
        [],                            
        [(-1,1)],                        
        [],                           
        [(-1,-1), (1,-1)],              
        [(1,-1)],                       
        [],                               
        [],                             
        [(-1,-1)],                        
        [],                                
        [],                              
        []                              
    ]
    
    output = 0
    visited = set()
    rows, cols = len(grid), len(grid[0])
    
    for row in range(rows):
        for col in range(cols):
            if (row, col) in visited:
                continue
                
            plant = grid[row][col]
            area = 0
            corners = 0
            queue = [(row, col)]
            
            while queue:
                current_row, current_col = queue.pop(0)
                if (current_row, current_col) in visited:
                    continue
                    
                visited.add((current_row, current_col))
                area += 1
                
                corner_type = 0
                for i, (dr, dc) in enumerate(directions):
                    new_row, new_col = current_row + dr, current_col + dc
                    if (new_row < 0 or new_col < 0 or 
                        new_row >= rows or new_col >= cols or 
                        grid[new_row][new_col] != plant):
                        corner_type += (1 << i)
                    elif (new_row, new_col) not in visited:
                        queue.append((new_row, new_col))
                
                outer_corner_count = outer_corners[corner_type]
                
                inner_corner_count = 0
                for dr, dc in check_inner_corners[corner_type]:
                    new_row, new_col = current_row + dr, current_col + dc
                    if (new_row < 0 or new_col < 0 or 
                        new_row >= rows or new_col >= cols):
                        continue
                    if grid[new_row][new_col] != plant:
                        inner_corner_count += 1
                
                corners += outer_corner_count + inner_corner_count
            
            price = area * corners
            output += price
    
    return output

print(f"Total price: {solve('Day12\input.txt')}")