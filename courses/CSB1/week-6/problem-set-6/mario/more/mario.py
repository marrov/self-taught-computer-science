from cs50 import get_int

def draw_pyramid(h):
  """ Draws a mario pyramid of height h recursively."""
  # Base case
  if h == 1:
    return

  # TODO: Recursive case
  return

if __name__ == "__main__":
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 9:
            break

    print(f'You chose a height of {height}')

    draw_pyramid(height)