def is_safe_report(levels):
    """
    Check if a report is safe based on the rules:
    1. All levels must be either increasing or decreasing
    2. Adjacent levels must differ by at least 1 and at most 3
    """
    if len(levels) < 2:
        return True
    
    differences = [levels[i+1] - levels[i] for i in range(len(levels)-1)]
    
    expected_sign = 1 if differences[0] > 0 else -1
    
    for diff in differences:
        if (diff > 0 and expected_sign < 0) or (diff < 0 and expected_sign > 0):
            return False
    
        if diff == 0:
            return False
            
        if abs(diff) < 1 or abs(diff) > 3:
            return False
    
    return True

def is_safe_with_dampener(levels):
    """
    Check if a report is safe, either naturally or by removing one level using
    the Problem Dampener.
    """

    if is_safe_report(levels):
        return True
        

    for i in range(len(levels)):
        dampened_levels = levels[:i] + levels[i+1:]
        if is_safe_report(dampened_levels):
            return True
            
    return False

def count_safe_reports(filename):
    """Read reports from file and count how many are safe with Problem Dampener."""
    safe_count = 0
    
    try:
        with open(filename, 'r') as file:
            for line in file:
                line = line.strip()
                if line:
                    levels = [int(x) for x in line.split()]
                    if is_safe_with_dampener(levels):
                        safe_count += 1
    except FileNotFoundError:
        print(f"Error: Could not find file '{filename}'")
        return None
    except ValueError:
        print("Error: File contains invalid data format")
        return None
        
    return safe_count

# Run the analysis
result = count_safe_reports('Day2\input.txt')
if result is not None:
    print(f"Number of safe reports: {result}")