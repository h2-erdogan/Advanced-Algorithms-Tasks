from itertools import product

capital_letters = {'A', 'B', 'C', 'D', 'E'}
lowercase_letters = {'a', 'b', 'c', 'd', 'e'}
digits = {'1', '2', '3', '4', '5'}
special_symbols = {'$', '&', '%'}

# Combine all characters into one set
all_chars = capital_letters | lowercase_letters | digits | special_symbols

def is_valid_password(password):
    """Check if the password meets all given criterias."""
    capital_count = sum(1 for c in password if c in capital_letters)
    special_count = sum(1 for c in password if c in special_symbols)
    
    # Must include at least one character from each set
    if not any(c in capital_letters for c in password):
        return False
    if not any(c in lowercase_letters for c in password):
        return False
    if not any(c in digits for c in password):
        return False
    if not any(c in special_symbols for c in password):
        return False

    if password[0] not in (capital_letters | lowercase_letters):
        return False

    if capital_count > 2:
        return False

    if special_count > 2:
        return False

    return True

def generate_passwords(length):
    
    if length < 4: 
        print("Password length must be at least 4.")
        return

    valid_passwords = []
    index = 1

    # Generate all possible combinations of given length
    for password_tuple in product(all_chars, repeat=length):
        password = ''.join(password_tuple)

        if is_valid_password(password):
            valid_passwords.append(f"{index} {password}")
            index += 1

    # Save generated passwords to file
    with open("task1.2/generated_passwords.txt", "w") as file:
        file.write("\n".join(valid_passwords))

    print(f"Generated {len(valid_passwords)} valid passwords. Saved to 'generated_passwords.txt'.")

if __name__ == "__main__":
    try:
        length = int(input("Enter password length: "))
        generate_passwords(length)
    except ValueError:
        print("Please enter a valid integer for password length.")
