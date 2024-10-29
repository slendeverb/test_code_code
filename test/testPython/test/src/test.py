import random

def f(p):
    return p[0]**2-p[0]*4+3

def cal_best(local_best,global_best):
    return local_best<global_best

class Particle:
    def __init__(self,dim) -> None:
        self.dim=dim
        self.position=[random.uniform(-10,10) for _ in range(dim)]
        self.velocity=[random.uniform(-1,1) for _ in range(dim)]
        self.best_position=self.position[:]
        self.best_fitness=float('inf')

    def update_position(self):
        for i in range(len(self.position)):
            self.position[i]+=self.velocity[i]
        
    def update_velocity(self,global_best_position,w,c1,c2):
        for i in range(len(self.velocity)):
            r1=random.uniform(0,1)
            r2=random.uniform(0,1)
            cognitive_component=c1*r1*(self.best_position[i]-self.position[i])
            social_component=c2*r2*(global_best_position[i]-self.position[i])
            self.velocity[i]=w*self.velocity[i]+cognitive_component+social_component

    def evaluate_fitness(self):
        p=[0]*self.dim
        self.best_fitness=f(p)

class PSO:
    def __init__(self,num_particles,dim) -> None:
        self.num_particles=num_particles
        self.dim=dim
        self.particles=[Particle(dim) for _ in range(num_particles)]
        self.global_best_position=[float('inf')]*self.dim
        self.global_best_fitness=float('inf')

    def update_global_best(self):
        for particle in self.particles:
            if cal_best(particle.best_fitness,self.global_best_fitness):
                self.global_best_fitness=particle.best_fitness
                self.global_best_position=particle.best_position[:]

    def optimize(self,max_iter,w,c1,c2):
        for _ in range(max_iter):
            for particle in self.particles:
                pre_best_fitness=particle.best_fitness
                particle.evaluate_fitness()
                if cal_best(particle.best_fitness,pre_best_fitness):
                    particle.best_position=particle.position[:]
            self.update_global_best()
            for particle in self.particles:
                particle.update_velocity(self.global_best_position,w,c1,c2)
                particle.update_position()

pso=PSO(num_particles=100,dim=1)
pso.optimize(max_iter=100,w=0.5,c1=1,c2=2)
print(f'Global best position: {pso.global_best_position}')
print(f'Global best fitness: {pso.global_best_fitness}')