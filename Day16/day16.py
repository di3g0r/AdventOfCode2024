from collections import defaultdict
import heapq

def parse_maze(maze_str):
    return [list(line.strip()) for line in maze_str.strip().split('\n')]

def find_position(maze, char):
    for y in range(len(maze)):
        for x in range(len(maze[0])):
            if maze[y][x] == char:
                return (x, y)
    return None

def solve_reindeer_maze(maze_str):
    # Parse the maze
    maze = parse_maze(maze_str)
    height = len(maze)
    width = len(maze[0])
    
    start = find_position(maze, 'S')
    end = find_position(maze, 'E')
    
    directions = [(1,0), (0,1), (-1,0), (0,-1)]
    
    pq = [(0, (start[0], start[1], 0))]  
    
    best_scores = defaultdict(lambda: float('inf'))
    best_scores[(start[0], start[1], 0)] = 0
    
    while pq:
        score, (x, y, direction) = heapq.heappop(pq)
        
        if (x, y) == end:
            return score
            
        if score > best_scores[(x, y, direction)]:
            continue
            
        for new_direction in range(4):
            turn_cost = 0
            if new_direction != direction:
                turns_needed = min((new_direction - direction) % 4, (direction - new_direction) % 4)
                turn_cost = turns_needed * 1000
            
            dx, dy = directions[new_direction]
            new_x, new_y = x + dx, y + dy
            
            if (0 <= new_x < width and 
                0 <= new_y < height and 
                maze[new_y][new_x] != '#'):
                
                new_score = score + turn_cost + 1 
                
                if new_score < best_scores[(new_x, new_y, new_direction)]:
                    best_scores[(new_x, new_y, new_direction)] = new_score
                    heapq.heappush(pq, (new_score, (new_x, new_y, new_direction)))
    
    return float('inf')  

with open('Day16/input.txt', 'r') as file:
    maze_input = file.read()


result = solve_reindeer_maze(maze_input)
print(f"The lowest possible score for the reindeer is: {result}")