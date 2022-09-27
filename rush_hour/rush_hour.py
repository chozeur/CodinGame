import sys
import math

class	Point:
	def __init__(self, x, y):
		self.x=x
		self.y=y

class	Car:
	def	__init__(self, inputs):
		self.id=int(inputs[0])
		self.x=int(inputs[1])
		self.y=int(inputs[2])
		self.length=int(inputs[3])
		self.axis=inputs[4]
		self.pos=[]
		self.pos.append([self.x, self.y])
		for i in range(self.length):
			if self.axis=='V':
				self.pos.append([self.x, self.y+1])
			else:
				self.pos.append([self.x+1, self.y])
	def	go(self, dir: str):
		print(self.id, dir)

def	setGrid(cars):
	grid = [[0,0,0,0,0,0],
			[0,0,0,0,0,0],
			[0,0,0,0,0,0],
			[0,0,0,0,0,0],
			[0,0,0,0,0,0],
			[0,0,0,0,0,0]]
	for c in cars:
		grid[c.y][c.x]=1
		for i in range(c.length):
			if c.axis=='V':
				grid[c.y+i][c.x]=1
			else:
				grid[c.y][c.x+i]=1
	return grid

def	printCars(cars):
	for c in cars:
		print("CARS:",file=sys.stderr)
		print("car #", c.id," x=", c.x," y=", c.y,\
		" length=", c.length, " axis=", c.axis, sep='', file=sys.stderr)

def	isFree(x, y, grid):
	if (grid[y][x]==0):
		return True
	else:
		return False

def	whosThere(x, y, cars):
	for c in cars:
		for i in range(c.length):
			if c.pos[i][0]==x and c.pos[i][1]==y:
				return c.id
	return False

n=int(input())  # Number of vehicles
while True:
	for i in range(n):
		inputs=input().split()
		cars=[]
		cars.append(Car(inputs))
	grid=setGrid(cars)
	if isFree(cars[0].x+cars[0].length, cars[0].y, grid):
		cars[0].go("RIGHT")
	else:
		cars[1].go("DOWN")
	#############################
	printCars(cars)
	print("GRID :", grid, file=sys.stderr)
	#############################
	for i in range(n):
		del cars[i]
