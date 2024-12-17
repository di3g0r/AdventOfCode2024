from collections import defaultdict
import heapq

def find_min_score_and_paths(maze):
    height = len(maze)
    width = len(maze[0])
    
    start = None
    end = None
    for y in range(height):
        for x in range(width):
            if maze[y][x] == 'S':
                start = (x, y)
            elif maze[y][x] == 'E':
                end = (x, y)
    
    directions = [(1,0), (0,1), (-1,0), (0,-1)]
    
    scores = defaultdict(lambda: float('inf'))
    scores[(start[0], start[1], 0)] = 0  
    
    queue = [(0, start[0], start[1], 0, {start})]
    optimal_paths = []
    min_score = float('inf')
    
    while queue:
        score, x, y, facing, path = heapq.heappop(queue)
        
        if (x, y) == end:
            if score < min_score:
                min_score = score
                optimal_paths = [path]
            elif score == min_score:
                optimal_paths.append(path)
            continue
            
        if score > min_score:
            continue
        
        for new_dir in range(4):
            turn_cost = 0
            if new_dir != facing:
                turns = min((new_dir - facing) % 4, (facing - new_dir) % 4)
                turn_cost = turns * 1000
            
            dx, dy = directions[new_dir]
            new_x = x + dx
            new_y = y + dy
            new_pos = (new_x, new_y)
            
            if (0 <= new_x < width and 
                0 <= new_y < height and 
                maze[new_y][new_x] != '#'):
                
                new_score = score + turn_cost + 1
                state = (new_x, new_y, new_dir)
                
                if new_score <= min_score and new_score <= scores[state]:
                    scores[state] = new_score
                    new_path = path | {new_pos}
                    heapq.heappush(queue, (new_score, new_x, new_y, new_dir, new_path))
    
    optimal_tiles = set()
    for path in optimal_paths:
        optimal_tiles.update(path)
    
    return min_score, optimal_tiles

def solve_maze(maze_str):
    maze = [list(line.strip()) for line in maze_str.strip().split('\n')]
    
    min_score, optimal_tiles = find_min_score_and_paths(maze)
    
    visual = [row[:] for row in maze]
    for x, y in optimal_tiles:
        if visual[y][x] not in 'SE':
            visual[y][x] = 'O'
    
    print("\nMaze with optimal paths marked (O):")
    for row in visual:
        print(''.join(row))
    
    return len(optimal_tiles)

example1 = """
###############
#.......#....E#
#.#.###.#.###.#
#.....#.#...#.#
#.###.#####.#.#
#.#.#.......#.#
#.#.#####.###.#
#...........#.#
###.#.#####.#.#
#...#.....#.#.#
#.#.#.###.#.#.#
#.....#...#.#.#
#.###.#.#.#.#.#
#S..#.....#...#
###############
"""

example2 = """
#################
#...#...#...#..E#
#.#.#.#.#.#.#.#.#
#.#.#.#...#...#.#
#.#.#.#.###.#.#.#
#...#.#.#.....#.#
#.#.#.#.#.#####.#
#.#...#.#.#.....#
#.#.#####.#.###.#
#.#.#.......#...#
#.#.###.#####.###
#.#.#...#.....#.#
#.#.#.#####.###.#
#.#.#.........#.#
#.#.#.#########.#
#S#.............#
#################
"""

result1 = solve_maze(example1)
print(f"Example 1 tiles: {result1}")
assert result1 == 45, f"Example 1 failed: expected 45, got {result1}"

result2 = solve_maze(example2)
print(f"Example 2 tiles: {result2}")
assert result2 == 64, f"Example 2 failed: expected 64, got {result2}"

with open('Day16/input.txt', 'r') as file:
    result = solve_maze(file.read())
print(f"\nNumber of tiles that are part of optimal paths: {result}")