from collections import Counter
from sys import argv

def solve(word1, word2, word3):
    letter_map = dict(Counter(word1 + word2 + word3))

    solution = [None]
    letter_map_keys = sorted(letter_map.keys())
    combo(letter_map, letter_map_keys, 0, [0,1,2,3,4,5,6,7,8,9], word1, word2, word3, solution)

    return solution[0]

def combo(letter_map, letter_map_keys, letter_map_idx, remaining_nums, word1, word2, word3, solution):
    if solution[0]:
        return
        
    if len(letter_map_keys) == letter_map_idx:
        if check(letter_map, word1, word2, word3):
            solution[0] = dict(letter_map)
        return

    for num in list(remaining_nums):
        if solution[0]:
            return
        
        remaining_nums.remove(num)
        letter_map[letter_map_keys[letter_map_idx]] = num

        combo(letter_map, letter_map_keys, letter_map_idx+1, remaining_nums, word1, word2, word3, solution)
        
        letter_map[letter_map_keys[letter_map_idx]] = -1
        remaining_nums.append(num)

def check(letter_map, word1, word2, word3):
    word1 = list(word1)
    word2 = list(word2)
    word3 = list(word3)

    word1.reverse()
    word2.reverse()
    word3.reverse()

    i = 0
    j = 0
    k = 0
    carry = 0

    while i < len(word1) and j < len(word2):
        n1 = letter_map[word1[i]]
        n2 = letter_map[word2[j]]
        n3 = letter_map[word3[k]]
        i += 1
        j += 1
        k += 1

        val = n1 + n2 + carry

        carry = 0
        if val > 9:
            carry = 1
            val %= 10

        if val != n3:
            return False

    while i < len(word1):
        n1 = letter_map[word1[i]]
        n3 = letter_map[word3[k]]
        i += 1
        k += 1
    
        val = n1 + carry
    
        carry = 0
        if val > 9:
            carry = 1
            val %= 10
    
        if val != n3:
            return False

    while j < len(word2):
        n2 = letter_map[word2[j]]
        n3 = letter_map[word3[k]]
        j += 1
        k += 1
    
        val = n2 + carry
    
        carry = 0
        if val > 9:
            carry = 1
            val %= 10
    
        if val != n3:
            return False
        
    if carry:
        if k == len(word3):
            return False
        if letter_map[word3[k]] != 1:
            return False
    else:
        if k < len(word3):
            return False
            
    return True

if __name__ == "__main__":
    try:
        word1 = argv[1]
        word2 = argv[2]
        word3 = argv[3]
        print(solve(word1, word2, word3))
    except:
        print("Usage: python3 auf.py word1 word2 word3")
