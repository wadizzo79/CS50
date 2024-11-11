from cs50 import get_float

while True:
    cents = get_float("Change: ")
    cents = round(cents * 100)
    if cents > 0:
        break


def calculate_quarters(cents):
    quarters = 0
    while cents >= 25:
        quarters += 1
        cents -= 25

    return quarters


def calculate_dimes(cents):
    dimes = 0
    while cents >= 10:
        dimes += 1
        cents -= 10

    return dimes


def calculate_nickels(cents):
    nickels = 0
    while cents >= 5:
        nickels += 1
        cents -= 5

    return nickels


def calculate_pennies(cents):
    pennies = 0
    while cents >= 1:
        pennies += 1
        cents -= 1

    return pennies


quarters = calculate_quarters(cents)
cents -= (quarters * 25)

dimes = calculate_dimes(cents)
cents -= (dimes * 10)

nickels = calculate_nickels(cents)
cents -= (nickels * 5)

pennies = calculate_pennies(cents)
cents -= (pennies * 1)

change = quarters + dimes + nickels + pennies
print(change)
