def nextOne(n):
    r = 0
    for i in str(n):
        r += int(i)**2
    return r

def isHappy(n) -> bool:
    tmp = []
    while n not in tmp:
        tmp.append(n)
        n = nextOne(n)
    return True if n == 1 else False

n = int(input())
for i in range(n):
    x = input()
    print(x,':)'if isHappy(x)else':(')

