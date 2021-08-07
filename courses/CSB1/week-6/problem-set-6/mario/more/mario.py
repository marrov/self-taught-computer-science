from cs50 import get_int

while True:
  height = get_int("Height: ")
  if height >= 1 and height <= 9:
    break

draw_pyramid(height)


def draw_pyramid(h):
  """ Draws a mario pyramid of height h recursively."""
  # Base case
  if h == 1:
    return
  
  # TODO: Recursive case
  return

