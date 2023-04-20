import sys

cardVal = { '2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,
            '9':9,'10':10,'J':11,'Q':12,'K':13,'A':14
}

deckP1 = [input()[0] for _ in range(int(input()))]
for i in range(len(deckP1)):
    if deckP1[i] == '1':deckP1[i] += '0'
deckP2 = [input()[0] for _ in range(int(input()))]
for i in range(len(deckP2)):
    if deckP2[i] == '1':deckP2[i] += '0'

rnd = 0

drop1 = []
drop2 = []

while len(deckP1) and len(deckP2):
    print('\ndeckP1',deckP1,'\ndeckP2',deckP2,sep='\n',file=sys.stderr)

    drop1.append(deckP1[0])
    deckP1.pop(0)
    drop2.append(deckP2[0])
    deckP2.pop(0)
    if cardVal[drop1[len(drop1)-1]] == cardVal[drop2[len(drop2)-1]]:
        if len(deckP1)<3 or len(deckP2)<3:
            print('PAT')
            exit()
        for _ in range(3):
            drop1.append(deckP1[0])
            deckP1.pop(0)
            drop2.append(deckP2[0])
            deckP2.pop(0)
        continue
    if cardVal[drop1[len(drop1)-1]] > cardVal[drop2[len(drop2)-1]]:
        for _ in range(len(drop1)):
            deckP1.append(str(drop1[0]))
            drop1.pop(0)
        for _ in range(len(drop2)):
            deckP1.append(str(drop2[0]))
            drop2.pop(0)
    else:
        for _ in range(len(drop1)):
            deckP2.append(drop1[0])
            drop1.pop(0)
        for _ in range(len(drop2)):
            deckP2.append(drop2[0])
            drop2.pop(0)
    rnd+=1

if len(deckP1):print('1',rnd)
else:print('2',rnd)
