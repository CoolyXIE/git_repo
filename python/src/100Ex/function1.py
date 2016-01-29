def ploynomial(x=0, *args, **keys):
    ploy = {}
    if x == 0:
        return 0
    for times, factor in enumerate(args):
        ploy[times] = factor
    for times, factor in keys.iteritems():
        ploy[int(times[1:])] = factor
    return sum(value * x ** key for key, value in ploy.iteritems())




print ploynomial(1, 7, 2, 5, x9=20, x12=21)
