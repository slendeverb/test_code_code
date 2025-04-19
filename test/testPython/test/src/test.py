import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import matplotlib

matplotlib.rc("font",family="Sim Hei")

data=pd.read_csv("../resources/csv/weatherHistory.csv")
print(data.shape)
print(data.head())