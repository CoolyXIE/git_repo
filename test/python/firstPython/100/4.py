# -*- coding: UTF-8 -*-


def is_leap_year(year):
    if year%100 == 0:
        if year % 400 == 0:
            return True
        else:
            return False
    else:
        if year % 4 == 0:
            return True
        else:
            return False



year = int(raw_input("year:"))
month = int(raw_input("month:"))
day = int(raw_input("day:"));

month_days_dict = {1:31,3:31,5:31,7:31,8:31,10:31,12:31,4:30,6:30,9:30,11:30}

num = 0
for m in range(1, month):
    if (m == 2):
        if is_leap_year(year):
            num = num + 29
        else:
            num = num + 28
    else:
        num = num + month_days_dict[m]

num = num + day
print "total days:",num








