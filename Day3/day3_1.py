total = 0

with open('Day3/input.txt', 'r') as file:
    text = file.read()
    for i in range(len(text)):
        if i >= 3 and text[i] == '(' and text[i-3:i] == "mul":
            next_chars = ""
            j = i + 1
            while j < len(text) and text[j].isdigit() and len(next_chars) < 3:
                next_chars += text[j]
                j += 1
            if next_chars:  
                if text[j] == ',':
                    second_chars = ""
                    k = j + 1
                    while k < len(text) and text[k].isdigit() and len(second_chars) < 3:
                        second_chars += text[k]
                        k += 1
                    if second_chars and k < len(text):
                        if text[k] == ")":
                            total += int(next_chars) * int(second_chars)

print(total)