import matplotlib
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

matplotlib.rc('font',family='Microsoft YaHei')

date=['2020-1-1','2020-2-2','2020-3-3','2020-4-4','2020-5-5','2020-6-6','2020-7-7','2020-8-8','2020-9-9']
temperature=[6,10,15,20,24,28,34,36,26]
wetness=range(1,10)
x=pd.DataFrame({'日期':date,'气温':temperature,'湿度':wetness})
# print(x.head(),x.tail(),sep='\n')
x=x[(x['气温']>10) & (x['气温']<30)]
# x.to_excel('../resources/data.xlsx',index=False)
print(x)

x=[range(1,13),[np.random.randn() for _ in range(0,12)]]
plt.figure()
plt.title('每月随机值')
plt.xlabel('月份')
plt.ylabel('值')
plt.bar(x[0],x[1],color='orange')
# plt.show()

lv = [1, 2, 2, 3, 3, 4, 2, 3, 3, 3, 3]
num = [122, 111, 222, 444, 555, 555, 333, 666, 666, 777, 888]
df = pd.DataFrame({'lv': lv, 'num': num})
df=df.groupby('lv').agg(
    mean=('num','mean')
)
df=df.sort_values('mean',ascending=False)
print(df)