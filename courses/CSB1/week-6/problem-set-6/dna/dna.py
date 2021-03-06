# Simulate DNA matching

import csv
import sys


def main():

    # Check for correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Open the CSV file and read into memory as dictionary
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Put STRs from the database column names as
    STRs = list(database[0])[1:]

    # Open the DNA sequence and read into memory as list
    with open(sys.argv[2], "r") as file:
        sequence = file.readline()

    # For each of the STRs, compute the longest run of
    # consecutive repeats of the STR in the DNA sequence
    max_reps = []
    for STR in STRs:
        max_reps.append(max_STR_repeats(sequence, STR))

    # If the STR counts match with any individuals in the CSV file,
    # print out the name of the matching individual
    reps_dict = dict(zip(STRs, max_reps))

    for idx in range(len(database)):
        bool_list = []
        for STR in STRs:
            if int(database[idx][STR]) == reps_dict[STR]:
                bool_list.append(True)
            else:
                bool_list.append(False)

        if all(bool_list) == True:
            print(f"{database[idx]['name']}")
            return

    print("No match")
    return


def max_STR_repeats(sequence: str, STR: str) -> int:
    """Given both a DNA sequence and an STR as inputs,
    returns the maximum number of times that the STR repeats"""

    # Initialize list of number of repeats by position
    repeats = [0] * len(sequence)

    # For each position of the sequence, compute the repeats
    for idx in range(len(sequence)):
        # Exit loop if no repeats are possible
        if idx + len(STR) == len(sequence):
            break

        # Check if STR in sequence and update repeats counter
        while STR == sequence[idx + repeats[idx] * len(STR): len(STR) + idx + repeats[idx] * len(STR)]:
            repeats[idx] += 1

    return max(repeats)


if __name__ == "__main__":
    main()