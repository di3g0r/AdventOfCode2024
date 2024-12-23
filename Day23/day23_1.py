from collections import defaultdict

pairs = [l.split('-') for l in open("Day23\input.txt").read().splitlines()]
print(pairs)

graph = defaultdict(list)
t_nodes = set()
for lhs, rhs in pairs:
    graph[lhs].append(rhs)
    graph[rhs].append(lhs)
    if lhs[0] == 't':
        t_nodes.add(lhs)
    if rhs[0] == 't':
        t_nodes.add(rhs)

triples = []
#for n0 in graph.keys():
for n0 in t_nodes:
    for n1 in graph[n0]:
        for n2 in graph[n1]:
            triple = {n0, n1, n2}
            if len(triple) == 3 and n2 in graph[n0] and triple not in triples:
                triples.append(triple)

for triple in triples:
    print('-'.join(sorted(triple)))
print(len(triples))