import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage : python dna.py databases/x.csv sequences/x.txt")
        return 1

    rows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    with open(sys.argv[2], encoding="utf-8") as f:
        read_data = f.read()

    STR = reader.fieldnames[1:]
    str_counts = {}

    for str in STR:
        count = longest_match(read_data, str)
        str_counts[str] = count

    for row in rows:
        match = True
        for str in str_counts:
            if int(row[str]) != str_counts[str]:
                match = False
                break
        if match:
            print(row['name'])
            break

    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
