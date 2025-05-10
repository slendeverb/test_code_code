import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import matplotlib

matplotlib.rc("font",family="Microsoft YaHei")

# pd.set_option('display.max_row',None)
# pd.set_option('display.max_column',None)

data = pd.read_csv("D:/Tencent Files/QQ Files/Tencent Files/571641990/FileRecv/" \
    "气象信息系统工程/实验/实验1/实验1 2006年至2016年塞格德的气象数据/weatherHistory.csv")

print(data)

data.drop_duplicates(subset=["Formatted Date"],inplace=True)
data.sort_values(by="Formatted Date",inplace=True)

date_list:list[str]=[]
for x in data["Formatted Date"].values:
    assert(type(x) == str)
    pos=x.find("-")
    date_list.append(x[pos+1:pos+3])

start_pos=0
end_pos=data.__len__()
print(end_pos)
# plt.figure(figsize=(10,6))
# plt.plot(date_list[start_pos:end_pos],data["Apparent Temperature (C)"][start_pos:end_pos],'.',color="blue",label="体感温度")
# plt.xlabel("日期")
# plt.ylabel("温度")
# plt.title("塞格德2006年至2016年体感温度变化")
# plt.legend()
# plt.show()