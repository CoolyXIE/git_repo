#-*- coding:utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt


x = np.arange(0, 5, 0.1)
# plot返回一个列表，通过line,获取其第一个Line2D元素
line, = plt.plot(x, x*x) 
# 调用Line2D对象的set_*方法设置属性值，设置取消反锯齿效果
line.set_antialiased(False)

#同时绘制两条曲线，lines是一个有两个Line2D对象的list
lines = plt.plot(x, np.sin(x), x, np.cos(x)) 

#同时配置多个Line2D对象的属性值
plt.setp(lines, color='r', linewidth=2.0)

#通过get_方法，或者plt.getp函数获取对象的属性值
lines[0].get_linewidth()
#getp只能对一个对象 操作
plt.getp(line, 'color')
# plt.show()

#get current figure
f = plt.gcf()
#figure对象的axes属性,得到的是AxesSubplot对象列表
print plt.getp(f, 'axes')
#get current axesSubplot
plt.gca()










