import random

def swap(arr, a, b):
    tmp = arr[a]
    arr[a] = arr[b]
    arr[b] = tmp

def getPivot(arr, begin, end):
    
    pick = arr[end]
    pivot = begin-1
    for i in range(begin, end):
        if arr[i] < pick:
            pivot+=1
            swap(arr, i, pivot)
    swap(arr, pivot+1, end)
    return pivot+1

def quicksort(arr, begin, end):
    
    if (begin < end):
        pivot = getPivot(arr, begin, end)
        
        quicksort(arr, begin, pivot-1);
        quicksort(arr, pivot+1, end);
    
    
    


n = 10
x = [random.randrange(100) for i in range(n)]
print(x)
quicksort(x, 0, n-1)
print(x)