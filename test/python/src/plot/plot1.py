#-*- coding:utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 10, 1000) #start, stop, num
y = np.sin(x)
z = np.cos(x**2)

plt.figure(figsize=(8,4), edgecolor='green')

#label曲线名，$使用latex公式, color曲线颜色， linewidth线宽
plt.plot(x, y, label="$sin(x)$", color='red', linewidth=2)
#第三个参数字符串，b为蓝色，--代表虚线，详见命令plt.plot?
plt.plot(x, z, "b--", label="$cos(x^2)$")
plt.xlabel("Time(s)")
plt.ylabel('nothing')
plt.title("test")
#设置y轴范围
plt.ylim(-1.2, 1.2)
#添加网格
plt.grid()
plt.grid(axis='x')
plt.grid(axis='y')
plt.grid(axis='both')
#显示图示
plt.legend() 
#画图
plt.show()
