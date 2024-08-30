import csv
import sys


def main():
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
    else:
        # read files into variable
        data = []
        seq = open(sys.argv[2], 'r').read()
        with open(sys.argv[1], 'r') as db:
            r = csv.DictReader(db)
            for row in r:
                data.append(row)
        # make list of the database keys we need to scan
        substr = list(data[0].keys())
        substr.pop(0)  # remove 'name'
        namee = "No match"  # store name of chosen one
        # make list of the matched nums
        longstr = []
        for i in range(len(substr)):
            longstr.append(longest_match(seq, substr[i]))
        # scan people for who is the chosen person
        for ppl in data:
            count = 0
            for i in range(len(substr)):
                if (int(ppl[substr[i]]) == int(longstr[i])):
                    count += 1
                if (count == len(substr)):
                    namee = ppl['name']
        print(namee)
    return


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
