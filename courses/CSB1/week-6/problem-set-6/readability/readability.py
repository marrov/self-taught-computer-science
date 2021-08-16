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

    # Count letters in text
    n_letters = len(re.findall('[A-Za-z]', text))

    # Count words in text
    n_words = len(re.findall('[ ]', text)) + 1

    # Count sentences in text
    n_sentences = len(re.findall('[.!?]', text))

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