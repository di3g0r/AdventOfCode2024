from collections import deque
from typing import List, Set, Tuple

def read_input(filename: str) -> List[List[str]]:
    """Read the garden map from input file."""
    with open(filename) as f:
        return [list(line.strip()) for line in f]

def find_regions(garden: List[List[str]]) -> List[Set[Tuple[int, int]]]:
    """Find all regions in the garden using BFS."""
    rows, cols = len(garden), len(garden[0])
    visited = set()
    regions = []
    
    def get_neighbors(r: int, c: int) -> List[Tuple[int, int]]:
        """Get valid neighboring cells with same plant type."""
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        neighbors = []
        plant = garden[r][c]
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if (0 <= nr < rows and 0 <= nc < cols and 
                garden[nr][nc] == plant):
                neighbors.append((nr, nc))
        return neighbors
    
    for r in range(rows):
        for c in range(cols):
            if (r, c) not in visited:
                region = set()
                queue = deque([(r, c)])
                plant_type = garden[r][c]
                
                while queue:
                    curr_r, curr_c = queue.popleft()
                    if (curr_r, curr_c) not in visited:
                        visited.add((curr_r, curr_c))
                        region.add((curr_r, curr_c))
                        
                        for nr, nc in get_neighbors(curr_r, curr_c):
                            if (nr, nc) not in visited:
                                queue.append((nr, nc))
                                
                regions.append(region)
    
    return regions

def calculate_perimeter(region: Set[Tuple[int, int]], garden: List[List[str]]) -> int:
    """Calculate the perimeter of a region."""
    perimeter = 0
    plant_type = garden[next(iter(region))[0]][next(iter(region))[1]]
    
    for r, c in region:
        for dr, dc in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nr, nc = r + dr, c + dc
            if (nr < 0 or nr >= len(garden) or 
                nc < 0 or nc >= len(garden[0]) or
                garden[nr][nc] != plant_type):
                perimeter += 1
                
    return perimeter

def calculate_total_price(filename: str) -> int:
    """Calculate the total price of fencing all regions."""
    garden = read_input(filename)
    regions = find_regions(garden)
    total_price = 0
    
    for region in regions:
        area = len(region)
        perimeter = calculate_perimeter(region, garden)
        price = area * perimeter
        total_price += price
        
    return total_price

result = calculate_total_price('Day12\input.txt')
print(f"Total price of fencing: {result}")