import random

MAXNUMBER = 99 #Максимальная граница чисел
MINNUMBER = 10 #Минимальная граница чисел

def func(n):
    result = []
    listLength = random.sample(range(1,n + 5),n) #Генерирую список случайных неповторяющихся длин списков размера n
    for tmpLength in listLength:
        #Создаю и заполняю n списков случайными числами
        result.append([random.randint(MINNUMBER,MAXNUMBER) for j in range(tmpLength)])

    for i, tmpList in enumerate(result):
        if i % 2 == 0:
            tmpList.sort(reverse = False) #Списки с четным номером сортирую по возрастанию
        else:
            tmpList.sort(reverse = True) #Списки с нечетным номером сортирую по убыванию

    return result
   
n = int(input())
result = func(n)

for i in result: #Вывожу списки, каждый с новой строки
    print(i)
