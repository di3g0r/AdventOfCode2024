with open("Day10\input.txt") as fin:
    grid = fin.read().strip().split("\n")
n = len(grid)
dd = [[0, 1], [1, 0], [0, -1], [-1, 0]]

def in_grid(i, j):
    return (0 <= i < n) and (0 <= j < n)

def score(i, j):
    if grid[i][j] != "0":
        return 0
    
    ans = 0
    stack = [(i, j)]
    visited = set([(i, j)])  # Add initial position to visited
    
    while stack:
        curi, curj = stack.pop()
        cur = int(grid[curi][curj])
        
        if cur == 9:
            ans += 1
            continue
            
        for di, dj in dd:
            ii, jj = curi + di, curj + dj
            
            if not in_grid(ii, jj):
                continue
                
            # Skip if we've already visited this position
            if (ii, jj) in visited:
                continue
                
            nbr = int(grid[ii][jj])
            if nbr != cur + 1:
                continue
                
            visited.add((ii, jj))  # Add new position to visited
            stack.append((ii, jj))
            
    return ans

ans = 0
for i in range(n):
    for j in range(n):
        ans += score(i, j)
print(ans)