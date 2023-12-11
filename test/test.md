将Rectangle类继承Point类的方式改为公有继承class Rectangle:public Point
在initRectangle(x,y,w,h)函数中加上initPoint(x,y)

派生类构造函数的调用顺序是
1. 按照基类在继承声明列表中的次序，分别执行它们的构造函数
2. 按照在类中定义的顺序，对派生类中新增成员进行初始化
3. 执行派生类构造函数的函数体
析构的顺序与构造相反

D的调用是正确的，因为Derived类中的print()函数把Base类中的print()函数覆盖了
直接访问无法访问到Base类中的print()函数