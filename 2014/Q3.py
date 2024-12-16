from math import comb

def nth_password(n):
    characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    num_chars = len(characters)
    
    # Step 1: Determine the length of the password
    length = 1
    while n > comb(num_chars, length):
        n -= comb(num_chars, length)
        length += 1
    
    # Step 2: Construct the nth password
    password = ""
    current_index = 0
    
    for _ in range(length):
        for i in range(current_index, num_chars):
            count = comb(num_chars - (i + 1), length - 1)
            if n > count:
                n -= count
            else:
                password += characters[i]
                current_index = i + 1
                length -= 1
                break
    
    return password

# Example usage
n = int(input("Enter n: "))
print(nth_password(n))
