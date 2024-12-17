from collections import deque
from typing import List, Set, Tuple

def read_input(filename: str) -> List[List[str]]:
    """Read the garden map from input file."""
    with open(filename) as f:
        return [list(line.strip()) for line in f]
    
filename = "Day16/input.txt"
grid = read_input(filename)
    
##             SOUTH    EAST    NORTH     WEST
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
curr_direction = directions[1]
start_position = grid[len(grid) - 2][1]


for i in range(0, len(grid)):
    print(grid[i])

print(start_position)