from collections import defaultdict
import networkx as nx
import os

def parse_input(filename):
    with open(filename, 'r') as file:
        content = file.read().strip()
    
    rules_text, updates_text = content.split('\n\n')
    
    rules = []
    for line in rules_text.split('\n'):
        line = line.strip()
        if line and '|' in line:
            before, after = map(int, line.split('|'))
            rules.append((before, after))
    
    updates = []
    for line in updates_text.split('\n'):
        line = line.strip().rstrip(',') 
        if line:
            pages = [int(x) for x in line.split(',') if x.strip()]
            if pages:  
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

def get_correct_order(pages, rules):
    G = nx.DiGraph()

    page_set = set(pages)
    G.add_nodes_from(page_set)
    
    for before, after in rules:
        if before in page_set and after in page_set:
            G.add_edge(before, after)

    try:
        return list(nx.topological_sort(G))
    except nx.NetworkXUnfeasible:
        return None 

def solve_puzzle_part2(filename):
    rules, updates = parse_input(filename)
    
    incorrect_updates = []
    correct_orders = []
    middle_numbers = []
    
    for update in updates:
        if not is_valid_order(update, rules):
            incorrect_updates.append(update)
            correct_order = get_correct_order(update, rules)
            if correct_order:
                correct_orders.append(correct_order)
                middle_idx = len(correct_order) // 2
                middle_numbers.append(correct_order[middle_idx])
    
    print(f"Found {len(incorrect_updates)} incorrect updates:")
    for i, (incorrect, correct) in enumerate(zip(incorrect_updates, correct_orders)):
        print(f"\nIncorrect: {','.join(map(str, incorrect))}")
        print(f"Correct:   {','.join(map(str, correct))}")
        print(f"Middle number: {middle_numbers[i]}")
    
    total = sum(middle_numbers)
    print(f"\nSum of middle numbers: {total}")
    
    return incorrect_updates, correct_orders, middle_numbers, total

filename = os.path.join("Day5", "input.txt")
incorrect_updates, correct_orders, middle_numbers, total = solve_puzzle_part2(filename)