from cs50 import get_int


def draw_pyramid(h, htotal):
    """Draws a mario pyramid of height h recursively."""
    if h == 1:
        # Base case
        print(' ' * (htotal - h) + '#' + '  ' + '#')
        return
    else:
        # Recursive case
        draw_pyramid(h - 1, htotal)
        print(' ' * (htotal - h) + '#' * h + '  ' + '#' * h)
        return


if __name__ == "__main__":
    # Ask user for int from 1 to 8
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break

    draw_pyramid(height, height)