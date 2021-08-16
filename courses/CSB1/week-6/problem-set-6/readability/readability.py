import re
from cs50 import get_string


def main():
    # Get text as string from user
    text = get_string("Text: ")

    # TODO: Calculate the Coleman-Liau index of the text
    cli = compute_cli(text)

    # TODO: print the grade-level readability of the text
    print_readability(cli)


def compute_cli(text):
    """Calculate the Coleman-Liau index"""

    # TODO: n_letters = regex expression

    # TODO: n_words = regex expression

    # TODO: n_sentences = regex expression

    return 0


def print_readability(cli):
    """Print out the grade level based on the CL index"""

    if cli < 1:
        print("Before Grade 1")
    elif (cli > 16):
        print("Grade 16+")
    else:
        print(f"Grade {cli}")

if __name__ == "__main__":
    main()