from datetime import datetime

def search(x, liste):
    i = 0
    j = len(liste) - 1
    if x > liste[-1] + liste[-2] or x < liste[0] + liste[1]:
        return -1
    while(liste[i] + liste[j] != x):
        if i == j:
            return -2
        if liste[i] + liste[j] < x:
            i += 1
        elif liste[i] + liste[j] > x:
            j -= 1
    return [liste[i], liste[j]]

#print(search(8, [1, 3, 4, 5, 6]))
n = 1000
##before = datetime.utcnow()
#print(search(n-1 + n-2, list(range(n))))
#print(datetime.utcnow() - before)
#print(search(n-1 + n, list(range(n))))
print(search(7, [1, 2, 3, 7]))
