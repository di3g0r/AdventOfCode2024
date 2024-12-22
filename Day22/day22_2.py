def step(num):
    num = (num ^ (num * 64)) % 16777216
    num = (num ^ (num // 32)) % 16777216
    num = (num ^ (num * 2048)) % 16777216
    return num

seq_to_total = {}

with open('Day22/input.txt', 'r') as file:
    for line in file:
        num = int(line)
        seen = set()
        prev = num % 10
        diffs = []
        for _ in range(2000):
            num = step(num)
            diffs.append(prev - num % 10)
            prev = num % 10
            if len(diffs) >= 4:
                seq = tuple(diffs)
                diffs.pop(0)
                if seq in seen: continue
                seen.add(seq)
                if seq not in seq_to_total: seq_to_total[seq] = 0
                seq_to_total[seq] += num % 10
                

print(max(seq_to_total.values()))
    
       

