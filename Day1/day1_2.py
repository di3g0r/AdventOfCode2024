def create_lists():
    list1 = []
    list2 = []
    with open("Day1\input_problem1.txt") as f:
        for line in f:
            item1,item2 = map(int,line.split())
            list1.append(item1)
            list2.append(item2)

    return [list1, list2]

def merge(arr, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid

    L = [0] * n1
    R = [0] * n2

    for i in range(n1):
        L[i] = arr[left + i]
    for j in range(n2):
        R[j] = arr[mid + 1 + j]

    i = 0  
    j = 0 
    k = left  

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1

def merge_sort(arr, left, right):
    if left < right:
        mid = (left + right) // 2

        merge_sort(arr, left, mid)
        merge_sort(arr, mid + 1, right)
        merge(arr, left, mid, right)

def count_frequencies(numbers):
    frequencies = {}
    for num in numbers:
        if num in frequencies:
            frequencies[num] += 1
        else:
            frequencies[num] = 1
    return frequencies

def main():
    lists = create_lists()
    list1, list2 = lists[0], lists[1]

    len_lists = len(list1) -1

    merge_sort(list1, 0, len_lists)
    merge_sort(list2, 0, len_lists)

    dic = count_frequencies(list2)
    print(dic)

    total = 0

    for i in range(0, len_lists+1):
        #print(list1[i], " - ", list2[i], "= ", abs(list1[i] - list2[i]))
        actual = list1[i]
        print(actual)
        if actual in dic:
            total += actual * dic[actual]

    print(total)
    return total
    #print(total)

    
main()