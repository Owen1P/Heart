import math
import os
import time

width = 80
height = 24

background_char = ' '
heart_char = '*'

theta = 0.0  #rotation angle

sleep_time = 0.05  #animation speed

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def draw_heart(theta):
    aspect_ratio = 0.5  #terminal aspect ratio
    scale = 10  #heart size

    buffer = [[' ' for _ in range(width)] for _ in range(height)]

    for y in range(-int(height / 2), int(height / 2)):
        for x in range(-int(width / 2), int(width / 2)):
            # Scale and correct the aspect ratio
            x_scaled = x * aspect_ratio / scale
            y_scaled = y / scale

            x_rotated = x_scaled * math.cos(theta) - y_scaled * math.sin(theta)
            y_rotated = x_scaled * math.sin(theta) + y_scaled * math.cos(theta)

            heart_eq = (x_rotated**2 + y_rotated**2 - 1)**3 - x_rotated**2 * y_rotated**3

            if heart_eq <= 0:
                # Map coordinates to buffer indices
                buffer_y = y + int(height / 2)
                buffer_x = x + int(width / 2)
                if 0 <= buffer_x < width and 0 <= buffer_y < height:
                    buffer[buffer_y][buffer_x] = heart_char

    # render the frame
    clear_screen()
    for row in buffer:
        print(''.join(row))

try:
    while True:
        draw_heart(theta)
        theta += 0.1  # Adjust rotation speed
        time.sleep(sleep_time)
except KeyboardInterrupt:
    pass  # stop program w/ Ctrl+C
