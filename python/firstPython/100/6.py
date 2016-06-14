
n = int(raw_input("Fibonacci sequence size:"))
fibonacci_list = [1,1,2]
if n <= 3:
    print fibonacci_list[0:n]
else:
    while(len(fibonacci_list) < n):
        new = fibonacci_list[-1] + fibonacci_list[-2]
        fibonacci_list.append(new)
    print fibonacci_list
