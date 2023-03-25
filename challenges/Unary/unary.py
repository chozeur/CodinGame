import sys
import math

msg = input()

bits = ''
for i in msg:
    t = format(ord(i), 'b')
    if len(t) != 7:
        t = (7 - len(t)) * '0' + t
    bits += t

i = 0
while i < len(bits):
    c = 0
    while i < len(bits) and bits[i] == '0':
        c+=1
        i+=1
    if c:
        print(end='00 ')
    while c:
        print(end='0')
        c-=1
        if c == 0 and i < len(bits):
            print(end=' ')
    while i < len(bits) and bits[i] == '1':
        c+=1
        i+=1
    if c:
        print(end='0 ')
    while c:
        print(end='0')
        c-=1
        if c == 0 and i < len(bits):
            print(end=' ')

