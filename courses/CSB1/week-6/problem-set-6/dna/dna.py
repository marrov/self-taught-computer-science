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
        sequence = [line.rstrip() for line in file]

    # For each of the STRs, compute the longest run of
    # consecutive repeats of the STR in the DNA sequence
    for STR in STRs:

    # TODO: If the STR counts match with any individuals in the CSV file, your
    #       program should print out the name of the matching individual


def (sequence: str, STR: str) -> int:
    """Given both a DNA sequence and an STR as inputs,
    returns the maximum number of times that the STR repeats"""
    return repeats


if __name__ == "__main__":
    main()