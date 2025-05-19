import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import matplotlib

matplotlib.rc('font',family='Microsoft YaHei')

data = pd.read_csv('D:/Tencent Files/QQ Files/Tencent Files/571641990/FileRecv/' \
    '气象信息系统工程/实验/实验1/实验1 2006年至2016年塞格德的气象数据/weatherHistory.csv')

data['Formatted Date'] = pd.to_datetime(
    data['Formatted Date'], 
    format='%Y-%m-%d %H:%M:%S.%f %z',  # 包含时区信息
    utc=True
)
data=data.drop_duplicates(subset=['Formatted Date'],keep='first')

data=data.set_index('Formatted Date').sort_index()

plt.figure(figsize=(15,7))
plt.subplots_adjust(
    left=0.1,      # 左边距
    right=0.9,     # 右边距
    bottom=0.1,    # 底部边距
    top=0.9,       # 顶部边距
    wspace=0.4,    # 水平间距 (子图之间的宽度间隔)
    hspace=0.4     # 垂直间距 (子图之间的高度间隔)
)
plt.subplot(2,2,1)
data['Apparent Temperature (C)'].plot(color=(1.0, 0.4980392156862745, 0.054901960784313725),title='Apparent Temperature (C)')
plt.subplot(2,2,2)
data['Humidity'].plot(color=(0.17254901960784313, 0.6274509803921569, 0.17254901960784313),title='Humidity')
plt.subplot(2,2,3)
data['Wind Speed (km/h)'].plot(color=(0.529, 0.808, 0.922),title='Wind Speed (km/h)')
plt.subplot(2,2,4)
data['Pressure (millibars)'].plot(color=(0.5803921568627451, 0.403921568627451, 0.7411764705882353),title='Pressure (millibars)')
plt.show()