def f(n):
    return (n**n+7*n) % 13


for i in range(13):
    print(i, f(i))
