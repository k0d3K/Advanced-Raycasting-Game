#!/bin/env python3

from PIL import ImageFont, ImageDraw, Image
from sys import argv
from os import system, curdir, path

ALPHA="""!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~"""
N_PER_ROW=16

if len(argv) != 3:
	print("Usage:", argv[0], "<font_name> <chr_size_in_pixel>")
	exit(1)
font = argv[1]
chr_size = int(argv[2])
out_name = "font.png"

x_size = N_PER_ROW * chr_size
y_size = chr_size * (1 + len(ALPHA) // N_PER_ROW)

image = Image.new(mode='RGB', size=(x_size, y_size), color="cyan")
imageFont = ImageFont.truetype(font, chr_size)

draw = ImageDraw.Draw(image)

x = 0
y = 0
for c in ALPHA:
	draw.text((x * chr_size + chr_size // 2, y * chr_size + chr_size // 2), c, font=imageFont, anchor="mm", align="center")
	x += 1
	if x == N_PER_ROW:
		x = 0
		y += 1

while x != N_PER_ROW:
	draw.rectangle(((x * chr_size, y * chr_size), ((x + 1) * chr_size, (y + 1) * chr_size)), "black")
	x += 1

#ImageDraw.floodfill(image, xy=(0,0), value=(0,255,255), thresh=100, border=(255, 255, 255))

image.save(out_name)
# system(path.join(curdir, "bmp_convert.py") + ' ' + out_name)