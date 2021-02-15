import random

MAXNUMBER = 99
MINNUMBER = 10

def func(n):
    result = []
    listLength = random.sample(range(1,n + 5),n)
    for tmpLength in listLength:
        result.append([random.randint(MINNUMBER,MAXNUMBER) for j in range(tmpLength)])

    for i, tmpList in enumerate(result):
        if i % 2 == 0:
            tmpList.sort(reverse = False)
        else:
            tmpList.sort(reverse = True)
    
    return result

    
n = int(input())
result = func(n)
for i in result:
    print(i)
