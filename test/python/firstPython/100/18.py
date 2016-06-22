a = int(raw_input("a:"))
n = int(raw_input("n:"))

sum = 0
x = a
for i in range(n):
    sum += x
    if i < n - 1:
        print x,'+',
    else:
        print x,'=',sum
    x = 10 * x + a

