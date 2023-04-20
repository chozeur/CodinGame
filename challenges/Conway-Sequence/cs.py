import sys

r = int(input())
l = int(input())

if l==1:exit(print(r))

prev = []
prev.append(r)
line = []

while l - 1:
    line = []
    prevIn = 0
    while prevIn < len(prev):
        count = 0
        tmp = prevIn
        while tmp < len(prev) and prev[tmp] == prev[prevIn]:
            count+=1
            tmp+=1
        line.append(count)
        line.append(prev[prevIn])
        prevIn+=count
    prev = line
    l-=1

t=0
for i in line:
    if t:print(end=' ')
    print(end=str(i))
    t=1
