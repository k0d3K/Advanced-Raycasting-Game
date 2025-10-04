#!/bin/python3

from sys import argv
import random

DENSITY = 0.05
E_WIDTH_VARIATION = (0.4, 0.8)
E_HEIGHT_VARIATION = (0.3, 0.7)

if len(argv) != 3:
	print("Usage:", argv[0], "<file_with_existing_ma> <name_of_entity>")
	exit(1)

ENTITY_IND = argv[2]

with open(argv[1], "rt") as map_f:
	rl = [l.rstrip() for l in map_f.readlines()]

map_ = rl[rl.index("MAP") + 1:]
height = len(map_)
width = max([len(s) for s in map_])
print("\n".join(map_))
print("width=", width, ", height=",height, sep='')

n_to_generate = int(DENSITY * width * height)
sample = random.sample(range(0, width * height), n_to_generate)

i = 0
for n in sample:
	x, y = n % width, n // width
	if map_[y][x] == '0':
		i += 1
		print(ENTITY_IND, x + 0.5, y + 0.5, round(random.uniform(*E_HEIGHT_VARIATION), 1), round(random.uniform(*E_HEIGHT_VARIATION), 1))
print("n enemies:", i)