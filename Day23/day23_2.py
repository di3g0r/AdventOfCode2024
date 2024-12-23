from collections import defaultdict

pairs = [l.split('-') for l in open("Day23\input.txt").read().splitlines()]
print(pairs)

graph = defaultdict(set)
for lhs, rhs in pairs:
    graph[lhs].add(rhs)
    graph[rhs].add(lhs)

groups = []
for n0 in graph.keys():
    for n1 in graph[n0]:
        pair = {n0, n1}
        if pair not in groups:
            groups.append(pair)

for n0, conns in graph.items():
    for group in groups:
        if len(conns & group) == len(group):
            group.add(n0)

for group in groups:
    print('-'.join(sorted(group)))
print(len(groups))
mlen = max(len(group) for group in groups)
print(mlen)
print('\n'.join(set(','.join(sorted(group)) for group in groups if len(group) == mlen)))