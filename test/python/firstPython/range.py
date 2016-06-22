# -*- coding: UTF-8 -*-

#写一段脚本确认一下python能处理的int, long, float, complex范围
for i in range(1,2147483647):
    if type(i) == type(1):
        continue
    else:
        print i
        break
print 'finished'
