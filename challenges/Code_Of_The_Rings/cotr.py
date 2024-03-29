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

def lowestCost(costs :dict, tmu):
    m = 9999
    res = 0
    for i in costs.keys():
        if costs[i] < m and i not in tmu:
            m = costs[i]
            res = i
    return res

def move(spell, forest, bpos, movepos, letter):
    print(f'letter = {letter}', file=sys.stderr)
    if movepos > bpos:
        for i in range(movepos - bpos):
            spell += '>'
            print(end='>')
            bpos += 1
    elif bpos > movepos:
        for i in range(abs(movepos - bpos)):
            spell += '<'
            print(end='<')
            bpos -= 1

    print(f'forest[{movepos}] = "{forest[movepos]}"', file=sys.stderr)
    m = morp(forest, movepos, letter)
    print(f'morp = {m}', file=sys.stderr)
    if m == 'p':
        while forest[movepos] != letter:
            spell += '+'
            print(end='+')
            forest[movepos] = plus(forest[movepos])
    elif m == 'm':
        while forest[movepos] != letter:
            spell += '-'
            print(end='-')
            forest[movepos] = minus(forest[movepos])

    print(end='.')
    return spell + '.', forest, bpos

def tenMostUsed(magic_phrase):
    char_counts = {}
    for char in magic_phrase:
        if char in char_counts and char != ' ':
            char_counts[char] += 1
        else:
            if char != ' ':
                char_counts[char] = 1

    sorted_counts = sorted(char_counts.items(), key=lambda x: x[1], reverse=True)
    most_found = [pair[0] for pair in sorted_counts][:10]

    return most_found

def findClosestFreeTier(forest, bpos):
    left = right = -1
    for i in range(bpos):
        if i % 3 == 0:
            if forest[i] == ' ':
                left = i
    for i in range(bpos,30):
        if i % 3 == 0:
            if forest[i] == ' ':
                right = i
                break

    if min(left,right) != -1:
        return min(left,right)
    else:
        return max(left,right)

magic_phrase = input()
tmu = tenMostUsed(magic_phrase)
print(f'tmu = {tmu}', file=sys.stderr)

spell = ''

forest = [' ']*30

bpos = 14

i = 0
while i != len(magic_phrase):
    char = magic_phrase[i]
    if char in forest:
        print(f'{char} is in forest', file=sys.stderr)
        movepos = forest.index(char)
    elif char in tmu:
        print(f'{char} is in tmu and need to be set', file=sys.stderr)
        cft = findClosestFreeTier(forest, bpos)
        movepos = cft
    else:
        print(f'{char} is nowhere', file=sys.stderr)
        costs = costOfAll(forest, bpos, char)
        movepos = lowestCost(costs, tmu)
    spell, forest, bpos = move(spell, forest, bpos, movepos, char)
    print(f'spell = {spell}\n\nforest = {forest}\n\nbpos = {bpos}\n\nmovepos = {movepos}\n\n', file=sys.stderr)
    i+=1
print()
