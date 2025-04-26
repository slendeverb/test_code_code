import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import matplotlib

matplotlib.rc("font",family="Microsoft YaHei")

data = pd.read_csv("D:/Tencent Files/QQ Files/Tencent Files/571641990/FileRecv/" \
    "气象信息系统工程/实验/实验1/实验1 2006年至2016年塞格德的气象数据/weatherHistory.csv")

print(data)

plt.figure(figsize=(10,6))

data.drop_duplicates(subset=["Formatted Date"],inplace=True)
data.sort_values(by="Formatted Date",inplace=True)

plt.plot(data["Formatted Date"][0:100],data["Apparent Temperature (C)"][0:100],color="blue",label="温度")

plt.xlabel("日期")
plt.ylabel("温度")
plt.title("塞格德2006年至2016年温度变化")
plt.legend()
plt.show()