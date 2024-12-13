def weekday(year, month, day):
    offset =0
    for y in range(1,year):
        if y% 400 == 0 or y%4 == 0 and y % 100 != 0:
            offset += 366
        else:
            offset += 365
    if year % 400 == 0 or year % 4 == 0 and year % 100 != 0:
        t=[0,31,28,31,30,31,30,31,31,30,31,30]
    else:
        t=[0,31,29,31,30,31,30,31,31,30,31,30]
    for m in range(month):
        offset += t[m]
    offset += day
    res =['日','一','二','三','四','五','六']
    return res[(1+offset)%7]