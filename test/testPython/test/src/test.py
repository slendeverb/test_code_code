from math import floor
import time
from matplotlib import pyplot as plt
import numpy as np

class TSP:
    def __init__(self,data,max_gen=100000,pop_size=100,cross_prob=0.8,muta_prob=0.02,select_prob=0.8):
        self.max_gen=max_gen
        self.pop_size=pop_size
        self.cross_prob=cross_prob
        self.muta_prob=muta_prob
        self.select_prob=select_prob

        self.data=data
        self.city_num=len(data)
        self.matrix_distance=self.matrix_dis()

        self.select_num=max(floor(self.pop_size*self.select_prob+0.5),2)
        self.parent=np.array([0]*self.pop_size*self.city_num).reshape(self.pop_size,self.city_num)
        self.child_select=np.array([0]*self.select_num*self.city_num).reshape(self.select_num,self.city_num)

        self.fitness=np.zeros(self.pop_size)

    def matrix_dis(self):
        res=np.zeros((self.city_num,self.city_num))
        for i in range(self.city_num):
            for j in range(i+1,self.city_num):
                res[i,j]=np.linalg.norm(self.data[i,:]-self.data[j,:])
                res[j,i]=res[i,j]
        return res

    def rand_parent(self):
        rand_pa=np.array(range(self.city_num))
        for i in range(self.pop_size):
            np.random.shuffle(rand_pa)
            self.parent[i,:]=rand_pa
            self.fitness[i]=self.cal_fitness(rand_pa)

    def cal_fitness(self,one_path):
        res=0
        for i in range(self.city_num-1):
            res+=self.matrix_distance[one_path[i],one_path[i+1]]
        res+=self.matrix_distance[one_path[-1],one_path[0]]
        return res
    
    def output_path(self,one_path):
        res=str(one_path[0]+1)+'-->'
        for i in range(1,self.city_num):
            res+=str(one_path[i]+1)+'-->'
        res+=str(one_path[0]+1)
        print(res)

    def select_child(self):
        fit=1./(self.fitness)
        cumsum_fit=np.cumsum(fit)
        pick=cumsum_fit[-1]/self.select_num*(np.random.rand()+np.array(range(self.select_num)))
        i,j=0,0
        idx=[]
        while i<self.pop_size and j<self.select_num:
            if cumsum_fit[i]>=pick[j]:
                idx.append(i)
                j+=1
            else:
                i+=1
        self.child_select=self.parent[idx,:]

    def cross_child(self):
        if self.select_num%2==0:
            num=range(0,self.select_num,2)
        else:
            num=range(0,self.select_num-1,2)
        for i in num:
            if self.cross_prob>=np.random.rand():
                self.child_select[i,:],self.child_select[i+1,:]=self.intercross(self.child_select[i,:],self.child_select[i+1,:])

    def intercross(self,ind_a,ind_b):
        r1=np.random.randint(self.city_num)
        r2=np.random.randint(self.city_num)

        while r2==r1:
            r2=np.random.randint(self.city_num)
        left,right=min(r1,r2),max(r1,r2)
        ind_a1=ind_a.copy()
        ind_b1=ind_b.copy()
        for i in range(left,right+1):
            ind_a2=ind_a.copy()
            ind_b2=ind_b.copy()
            ind_a[i]=ind_b1[i]
            ind_b[i]=ind_a1[i]
            x=np.argwhere(ind_a==ind_a[i])
            y=np.argwhere(ind_b==ind_b[i])

            if len(x)==2:
                ind_a[x[x!=i]]=ind_a2[i]
            if len(y)==2:
                ind_b[y[y!=i]]=ind_b2[i]
        return ind_a,ind_b
    
    def mutation_child(self):
        for i in range(self.select_num):
            if np.random.rand()<=self.muta_prob:
                r1=np.random.randint(self.city_num)
                r2=np.random.randint(self.city_num)
                while r2==r1:
                    r2=np.random.randint(self.city_num)
                self.child_select[i,[r1,r2]]=self.child_select[i,[r2,r1]]

    def reverse_child(self):
        for i in range(self.select_num):
            r1=np.random.randint(self.city_num)
            r2=np.random.randint(self.city_num)
            while r2==r1:
                r2=np.random.randint(self.city_num)
            left,right=min(r1,r2),max(r1,r2)
            sel=self.child_select[i,:].copy()
            sel[left:right+1]=self.child_select[i,left:right+1][::-1]
            if self.cal_fitness(sel)<self.cal_fitness(self.child_select[i,:]):
                self.child_select[i,:]=sel

    def iterate(self):
        idx=np.argsort(self.fitness)[::-1]
        self.parent[idx[:self.select_num],:]=self.child_select

def plt_draw():
    res=path_short.parent[0]
    x0=x[res]
    y0=y[res]
    fig,ax=plt.subplots()
    ax.scatter(x,y,linewidths=0.1)
    for i,txt in enumerate(range(1,len(data)+1)):
        ax.annotate(str(txt),(x[i],y[i]))
    for i in range(len(data)-1):
        plt.quiver(x0[i],y0[i],x0[i+1]-x0[i],y0[i+1]-y0[i],color='r',width=0.005,angles='xy',scale=1,scale_units='xy')
    plt.quiver(x0[-1],y0[-1],x0[0]-x0[-1],y0[0]-y0[-1],color='r',width=0.005,angles='xy',scale=1,scale_units='xy')
    plt.pause(1)
    plt.close()

f=open("D:/Tencent Files/QQ Files/Tencent Files/571641990/FileRecv/人工智能导论/实验/实验2/41-202283290199-施延枫/input.txt","r")
lines=f.readlines()
f.close()
data=[]
for line in lines:
    line=line.strip().split()[1:]
    line=list(map(int,line))
    data.append(line)
data=np.array(data).reshape(-1,2)
x=data[:,0]
y=data[:,1]

path_short=TSP(data)
path_short.rand_parent()

plt_draw()
print(f'初始染色体的路程: {str(path_short.fitness[0])}')

for i in range(path_short.max_gen):
    path_short.select_child()
    path_short.cross_child()
    path_short.mutation_child()
    path_short.reverse_child()
    path_short.iterate()

    for j in range(path_short.pop_size):
        path_short.fitness[j]=path_short.cal_fitness(path_short.parent[j,:])

    idx=path_short.fitness.argmin()
    if (i+1)%20==0:
        timestamp=time.time()
        formatted_time=time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(timestamp))
        print(formatted_time)
        print(f'第{str(i+1)}代后的最短路程: {str(path_short.fitness[idx])}')
        print(f'第{str(i+1)}代后的最优路径: ')
        path_short.output_path(path_short.parent[idx,:])

plt_draw()