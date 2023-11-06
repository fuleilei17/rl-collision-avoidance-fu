import matplotlib.pyplot as plt
import numpy as np

# 读取数据
data_0 = np.genfromtxt('data_0.txt', delimiter='\t', dtype=float)
data_1 = np.genfromtxt('data_1.txt', delimiter='\t', dtype=float)
data_2 = np.genfromtxt('data_2.txt', delimiter='\t', dtype=float)
data_3 = np.genfromtxt('data_3.txt', delimiter='\t', dtype=float)
data_4 = np.genfromtxt('data_4.txt', delimiter='\t', dtype=float)
data_5 = np.genfromtxt('data_5.txt', delimiter='\t', dtype=float)

# 创建画布和子图
fig, ax = plt.subplots()

# 绘制机器人轨迹
ax.plot(data_0[:,1], data_0[:,0], label='Robot 0')
ax.plot(data_1[:,1], data_1[:,0], label='Robot 1')
ax.plot(data_2[:,1], data_2[:,0], label='Robot 2')
ax.plot(data_3[:,1], data_3[:,0], label='Robot 3')
ax.plot(data_4[:,1], data_4[:,0], label='Robot 4')
ax.plot(data_5[:,1], data_5[:,0], label='Robot 5')

# 添加图例和标题
ax.legend()
ax.set_title('Robot Trajectories')

# 显示图像
plt.show()
