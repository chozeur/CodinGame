import sys
import math

class Point:
    def __init__(self, x, y):
        self.x=x
        self.y=y

class Car:
    def __init__(self, inputs):
        self.id=int(inputs[0])
        self.x=int(inputs[1])
        self.y=int(inputs[2])
        self.length=int(inputs[3])
        self.axis=inputs[4]

def setGrid(cars):
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

def printCars(cars):
    for c in cars:
        print("CARS:",file=sys.stderr)
        print("car #",c.id," x=",c.x," y=",c.y,\
        " length=",c.length," axis=",c.axis,sep='',file=sys.stderr)

n=int(input())  # Number of vehicles
cars=[]
while True:
    for i in range(n):
        inputs = input().split()
        cars.append(Car(inputs))
    grid=setGrid(cars)
    printCars(cars)
    print("GRID :",grid,file=sys.stderr)