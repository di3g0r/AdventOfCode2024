import math

def mix(secret_number, given_value):
    return secret_number ^ given_value

def prune(secret_number):
    return ((secret_number % 16777216) + 16777216) % 16777216  # Ensure positive result

def solve(buyers):
    secret_numbers = []
    for initial_number in buyers:
        secret_number = initial_number
        for _ in range(2000):
            r = secret_number * 64
            secret_number = prune(mix(secret_number, r))
            
            r = math.floor(secret_number / 32)
            secret_number = prune(mix(secret_number, r))
            
            r = secret_number * 2048
            secret_number = prune(mix(secret_number, r))
        
        secret_numbers.append(secret_number)
    
    print(secret_numbers)
    print(sum(secret_numbers))

buyers = []
with open('Day22/input.txt', 'r') as file:
    for line in file:
        if line.strip():  
            buyers.append(int(line.strip()))

solve(buyers)