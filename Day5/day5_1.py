from collections import defaultdict
import networkx as nx

def parse_input(filename):
    with open(filename, 'r') as file:
        sections = file.read().split('\n\n')
    
    rules = []
    for line in sections[0].strip().split('\n'):
        if '|' in line: 
            before, after = map(int, line.split('|'))
            rules.append((before, after))
    
    updates = []
    for line in sections[1].strip().split('\n'):
        if ',' in line:  
            pages = list(map(int, line.split(',')))
            updates.append(pages)
    
    return rules, updates

def is_valid_order(pages, rules):
    G = nx.DiGraph()
    
    page_set = set(pages)
    for before, after in rules:
        if before in page_set and after in page_set:
            G.add_edge(before, after)
    
    try:
        nx.find_cycle(G)
        return False  
    except nx.NetworkXNoCycle:
        pass
    
    page_positions = {page: idx for idx, page in enumerate(pages)}
    
    for before, after in rules:
        if before in page_set and after in page_set:
            if page_positions[before] > page_positions[after]:
                return False
    
    return True

def solve_puzzle(filename):
    rules, updates = parse_input(filename)
    
    valid_updates = []
    middle_numbers = []
    
    for update in updates:
        if is_valid_order(update, rules):
            valid_updates.append(update)
            middle_idx = len(update) // 2
            middle_numbers.append(update[middle_idx])
    
    print(f"Found {len(valid_updates)} valid updates:")
    for update in valid_updates:
        print(f"  {','.join(map(str, update))}")
    print(f"\nMiddle numbers: {middle_numbers}")
    print(f"Sum of middle numbers: {sum(middle_numbers)}")
    
    return valid_updates, middle_numbers, sum(middle_numbers)

filename = r"Day5\input.txt"  
valid_updates, middle_numbers, total = solve_puzzle(filename)