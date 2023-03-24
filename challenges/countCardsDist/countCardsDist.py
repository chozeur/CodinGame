def isCards(s):
    for i in s:
        if i not in ['2','3','4','5','6','7','8','9','T','J','Q','K','A']:
            return False
    return True


def revealedCards(cards):
    map = { '2':0,'3':0,'4':0,
            '5':0,'6':0,'7':0,
            '8':0,'9':0,'T':0,
            'J':0,'Q':0,'K':0,'A':0}
    
    for i in cards:
        for j in i:
            map[j] += 1

    return map

def probCards(c, rev):
    map = { '2':0,'3':0,'4':0,
            '5':0,'6':0,'7':0,
            '8':0,'9':0,'T':0,
            'J':0,'Q':0,'K':0,'A':0}

    for i in ['2','3','4','5','6','7','8','9','T','J','Q','K','A']:
        map[i] = (4 - rev[i]) / (52 - c)

    return map


stream_of_consciousness = input()
bust_threshold = int(input())
if bust_threshold == 10:
    bust_threshold = 'T'


consc = stream_of_consciousness.split('.')
cards = []
for i in consc:
    if isCards(i):
        cards.append(i)

cardCount = 0
for i in cards:
    cardCount += len(i)

revCards = revealedCards(cards)

probC = probCards(cardCount, revCards)

power = {'2':0,'3':1,'4':2,'5':3,'6':4,'7':5,'8':6,'9':7,'T':8,'J':9,'Q':10,'K':11,'A':-12}

res = 0.0
for i in ['2','3','4','5','6','7','8','9','T','J','Q','K','A']:
    if power[i] < power[str(bust_threshold)]:
        res += probC[i]
print(round(res * 100),end='%')
