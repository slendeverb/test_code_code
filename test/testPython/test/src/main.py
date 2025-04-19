# 机器学习
# 实验1
import numpy as np
import matplotlib.pyplot as plt

from matplotlib import font_manager
from matplotlib.font_manager import FontProperties
from sklearn.linear_model import LinearRegression

# 单变量线性回归
x_train=np.array([[6],[8],[10],[14],[18]])
y_train=np.array([[7],[9],[13],[17.5],[18]])

model=LinearRegression()
model.fit(x_train,y_train)
x_predict=np.array([[0],[10],[14],[25]])
y_predict=model.predict(x_predict)

plt.rcParams["font.sans-serif"]="SimHei"
plt.figure()
plt.title("披萨价格与直径数据")
plt.xlabel("直径(英寸)")
plt.ylabel("价格(美元)")
plt.axis((0,25,0,25))
plt.grid(True)
plt.plot(x_train,y_train,"k.")
plt.plot(x_predict,y_predict,"g-")

yr=model.predict(x_train)
for idx,x in enumerate(x_train):
    plt.plot([x,x],[y_train[idx],yr[idx]],"r-")
print(f"残差平方和: {np.mean((yr-y_train)**2):.2f}")

plt.show()

# 多变量线性回归
x_train=np.array([[1,6,2],[1,8,1],[1,10,0],[1,14,2],[1,18,0]])
y_train=np.array([[7],[9],[13],[17.5],[18]])
print(np.dot(np.linalg.inv(np.dot(np.transpose(x_train),x_train)),np.dot(np.transpose(x_train),y_train)))

x_train=np.array([[6,2],[8,1],[10,0],[14,2],[18,0]])
y_train=np.array([[7],[9],[13],[17.5],[18]])
model=LinearRegression()
model.fit(x_train,y_train)
x_test=np.array([[8,2],[9,0],[11,2],[16,2],[12,0]])
y_test=np.array([[11],[8.5],[15],[18],[11]])
predictions=model.predict(x_test)
for i,prediction in enumerate(predictions):
    print(f"Predicted: {prediction}, Target: {y_test[i]}")
print(f"R-squared: {model.score(x_test,y_test):.2f}")
