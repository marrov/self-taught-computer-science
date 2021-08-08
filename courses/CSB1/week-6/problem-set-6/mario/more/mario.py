from cs50 import get_int

def draw_pyramid(h):
    """Draws a mario pyramid of height h recursively."""
    if h == 1: # Base case
        print('#')
        return
    else: # Recursive case
        draw_pyramid(h - 1)
        print('#' * h)
        return

if __name__ == "__main__":
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break

    print(f'You chose a height of {height}')
    draw_pyramid(height)