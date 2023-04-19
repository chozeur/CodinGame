import sys
import math

def plus(c):
    if c == 'Z':
        return ' '
    elif c == ' ':
        return 'A'
    else:
        return chr(ord(c) + 1)

def minus(c):
    if c == 'A':
        return ' '
    elif c == ' ':
        return 'Z'
    else:
        return chr(ord(c) - 1)

def morp(forest, itpos, letter):

    m = p = 0
    c = forest[itpos]
    while c != letter:
        c = minus(c)
        m+=1
    c = forest[itpos]
    while c != letter:
        c = plus(c)
        p+=1

    return 'p' if p < m else 'm'

def costOfIt(forest, bpos, itpos, letter):
    moveCost = abs(itpos - bpos)
    if moveCost > 15 : moveCost -= 15

    changeCost = 0
    m = p = 0
    c = forest[itpos % 30]
    while c != letter:
        c = minus(c)
        m+=1
    c = forest[itpos % 30]
    while c != letter:
        c = plus(c)
        p+=1
    changeCost = min(m,p)

    # print(f'costOfIt(forest, {bpos}, {itpos}, {letter}) = {moveCost} + {changeCost} + 1 =', moveCost + changeCost + 1, file=sys.stderr)

    return (moveCost + changeCost + 1) # +1 for the '.'

def costOfAll(forest, bpos, letter):
    mapf = {}

    for i in range(len(forest)):
        mapf[i] = costOfIt(forest, bpos, i, letter)

    return mapf

def lowestCost(costs :dict):
    m = 9999
    res = 0
    for i in costs.keys():
        if costs[i] < m:
            m = costs[i]
            res = i
    return res

def move(spell, forest, bpos, movepos, letter):
    # print(f'letter = {letter}', file=sys.stderr)
    if movepos > bpos:
        for i in range(movepos - bpos):
            spell += '>'
            bpos += 1
    elif bpos > movepos:
        for i in range(abs(movepos - bpos)):
            spell += '<'
            bpos -= 1

    # print(f'forest[{movepos}] = "{forest[movepos]}"', file=sys.stderr)
    m = morp(forest, movepos, letter)
    # print(f'morp = {m}', file=sys.stderr)
    if m == 'p':
        while forest[movepos] != letter:
            spell += '+'
            forest[movepos] = plus(forest[movepos])
    elif m == 'm':
        while forest[movepos] != letter:
            spell += '-'
            forest[movepos] = minus(forest[movepos])

    return spell + '.', forest, bpos



magic_phrase = input()

spell = ''

forest = [' ']*30

bpos = 14

i = 0
while i != len(magic_phrase):
    costs = costOfAll(forest, bpos, magic_phrase[i])
    movepos = lowestCost(costs)
    spell, forest, bpos = move(spell, forest, bpos, movepos, magic_phrase[i])
    # print(f'spell = {spell}\n\nforest = {forest}\n\nbpos = {bpos}\n\nmovepos = {movepos}\n\n', file=sys.stderr)
    i+=1
print(spell)
