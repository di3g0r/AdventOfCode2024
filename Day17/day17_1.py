import re

with open('Day17/input.txt', 'r') as file:
    lines = file.readlines()

register_a = int(lines[0].split(':')[1].strip())
register_b = int(lines[1].split(':')[1].strip())
register_c = int(lines[2].split(':')[1].strip())

program_line = lines[4].split(':')[1].strip()
program_list = [int(x) for x in program_line.split(',')]
print(register_a)
print(program_list)
def get_combo_operand(number):
    if number <= 3:
        return number
    elif number == 4:
        return register_a
    elif number == 5:
        return register_b
    elif number == 6:
        return register_c
    else:
        return 0
    
pointer = 0
final_output = []

while pointer < len(program_list):
    actual_instruction = program_list[pointer]
    actual_operand = program_list[pointer+1]
    combo = get_combo_operand(actual_operand)

    #adv
    if actual_instruction == 0:
        register_a = register_a // (2 ** combo)
    
    #bxl
    elif actual_instruction == 1:
        register_b = register_b ^ actual_operand

    #bst
    elif actual_instruction == 2:
        register_b = combo % 8

    #jnz
    elif actual_instruction == 3:
        if register_a != 0:
            pointer = actual_operand
            continue

    #bxc
    elif actual_instruction == 4:
        register_b = register_b ^ register_c

    #out
    elif actual_instruction == 5:
        value = combo % 8
        final_output.append(value)

    #bdv
    elif actual_instruction == 6:
        register_b = register_a // (2 ** combo)

    #cdv
    elif actual_instruction == 7:
        register_c = register_a // (2 ** combo)
    
    pointer += 2

print(final_output)
print(','.join(map(str, final_output)))