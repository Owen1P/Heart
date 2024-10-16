import math
import os
import time


A, B, C = 0, 0, 0

cube_width = 20
width, height = 80, 24  

z_buffer = [0] * (width * height)
buffer = [' '] * (width * height)

background_char = ' '

distance_from_cam = 100

K1 = 40

def calculate_x(i, j, k):
    return j * math.sin(A) * math.sin(B) * math.cos(C) - k * math.cos(A) * math.sin(B) * math.cos(C) \
           + j * math.cos(A) * math.sin(C) + k * math.sin(A) * math.sin(C) + i * math.cos(B) * math.cos(C)

def calculate_y(i, j, k):
    return j * math.cos(A) * math.cos(C) + k * math.sin(A) * math.cos(C) \
           - j * math.sin(A) * math.sin(B) * math.sin(C) + k * math.cos(A) * math.sin(B) * math.sin(C) \
           - i * math.cos(B) * math.sin(C)

def calculate_z(i, j, k):
    return k * math.cos(A) * math.cos(B) - j * math.sin(A) * math.cos(B) + i * math.sin(B)

def calculate_for_surface(cube_x, cube_y, cube_z, ch):
    global buffer, z_buffer, width, height
    x = calculate_x(cube_x, cube_y, cube_z)
    y = calculate_y(cube_x, cube_y, cube_z)
    z = calculate_z(cube_x, cube_y, cube_z) + distance_from_cam

    ooz = 1 / z

    xp = int(width / 2 + K1 * ooz * x * 2)
    yp = int(height / 2 + K1 * ooz * y)

    idx = xp + yp * width
    if 0 <= idx < width * height:
        if ooz > z_buffer[idx]:
            z_buffer[idx] = ooz
            buffer[idx] = ch

def render():
    global buffer
    os.system('cls' if os.name == 'nt' else 'clear')
    for y in range(height):
        line = ''.join(buffer[y * width:(y + 1) * width])
        print(line)

while True:
    buffer = [background_char] * (width * height)
    z_buffer = [0] * (width * height)

    increment = 0.6 
    cube_x = -cube_width
    while cube_x < cube_width:
        cube_y = -cube_width
        while cube_y < cube_width:
            # Front Face
            calculate_for_surface(cube_x, cube_y, -cube_width, '@')
            # Back Face
            calculate_for_surface(cube_x, cube_y, cube_width, '#')
            # Left Face
            calculate_for_surface(-cube_width, cube_y, cube_x, '$')
            # Right Face
            calculate_for_surface(cube_width, cube_y, cube_x, '%')
            # Top Face
            calculate_for_surface(cube_x, -cube_width, cube_y, '^')
            # Bottom Face
            calculate_for_surface(cube_x, cube_width, cube_y, '&')
            cube_y += increment
        cube_x += increment

    render()

    A += 0.05
    B += 0.05
    C += 0.01

    time.sleep(0.02)
