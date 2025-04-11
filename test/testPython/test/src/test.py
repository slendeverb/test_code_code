import pandas as pd
import numpy as np

x=pd.Series(data=[1,2,3,4],index=['a','b','c','d'],name="test")
print(x.mean())

y=x.to_numpy()
print(y,type(y))