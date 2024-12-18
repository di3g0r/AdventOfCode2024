def read_program(file_path):
    """Reads the program and initial registers from the input file."""
    with open(file_path, 'r') as file:
        lines = file.read().strip().splitlines()

    # Debug: Show the lines read from the file
    print("Lines read from file:", lines)

    # Parse initial register values
    registers = {}
    for line in lines[:3]:
        key, value = line.split(': ')
        registers[key] = int(value)
    
    # Skip any blank lines and find the program line
    program = []
    for line in lines[3:]:
        if line.strip():  # Skip blank lines
            print("Program line before processing:", line)  # Debug: Show raw program line
            program_str = line.replace("Program: ", "").strip()
            program = [int(num) for num in program_str.split(',') if num]
            break  # Exit the loop once we find the program line

    # Debug: Show parsed program
    print("Parsed program:", program)

    return registers, program





def execute_program(registers, program):
    """Executes the 3-bit computer program."""
    A, B, C = registers["Register A"], registers["Register B"], registers["Register C"]
    output = []
    ip = 0  # Instruction pointer

    while ip < len(program):
        opcode = program[ip]
        operand = program[ip + 1] if ip + 1 < len(program) else None

        if opcode == 0:  # adv
            denominator = 2 ** resolve_combo_operand(operand, A, B, C)
            A //= denominator
        elif opcode == 1:  # bxl
            B ^= operand
        elif opcode == 2:  # bst
            B = resolve_combo_operand(operand, A, B, C) % 8
        elif opcode == 3:  # jnz
            if A != 0:
                ip = operand
                continue
        elif opcode == 4:  # bxc
            B ^= C
        elif opcode == 5:  # out
            output.append(resolve_combo_operand(operand, A, B, C) % 8)
        elif opcode == 6:  # bdv
            denominator = 2 ** resolve_combo_operand(operand, A, B, C)
            B = A // denominator
        elif opcode == 7:  # cdv
            denominator = 2 ** resolve_combo_operand(operand, A, B, C)
            C = A // denominator
        
        # Increment instruction pointer
        ip += 2

    return ','.join(map(str, output))


def resolve_combo_operand(operand, A, B, C):
    """Resolves the value of a combo operand."""
    if operand <= 3:
        return operand
    elif operand == 4:
        return A
    elif operand == 5:
        return B
    elif operand == 6:
        return C
    else:
        raise ValueError("Invalid combo operand")


# Main logic
input_file = "Day17/input.txt"
registers, program = read_program(input_file)
result = execute_program(registers, program)
print(registers)
print(program)
print(result)
