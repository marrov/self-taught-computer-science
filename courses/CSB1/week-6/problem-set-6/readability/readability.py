def main():
    # TODO: get text as string from user
    text = get_text()

    # TODO: Calculate the Coleman-Liau index of the text
    cli = compute_cli(text)

    # TODO: print the grade-level readability of the text
    print_readability(cli)

def get_text(text):
    return

def compute_cli(text):
    # TODO: count letters in text
    n_letters = count_letters(text)

    # TODO: count words in text
    n_words = count_words(text)

    # TODO: count sentences in text
    n_sentences = count_sentences(string text)

    return

def count_letters(text):
    return

def count_words(text):
    return

def count_sentences(string text):
    return

def print_readability(cli):
    return

if __name__ == "__main__":
    main()