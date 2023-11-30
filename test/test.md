程序先声明了一个一级指针p1,然后声明了一个二级指针p2指向p1,
把p1指向新声明的变量b=20,最后输出 **p2 也就是 *p1 也就是 b

程序定义了一个类CD,并定义了它的析构函数~CD(),在CD类对象被销毁时输出C
然后在主函数中定义了CD类对象a,CD类指针b,CD类对象数组,实际上创建了三个对象
最后销毁的时候输出3个C

程序定义了一个Location类,然后在主函数中声明了一个Location类对象数组A并初始化,
然后声明了一个指向A的指针rA,然后对A[3]调用init()函数,用rA调用init()函数,
将A数组中第四个元素变为(7,3),将第一个元素变为(7,8),然后遍历数组用display()函数
将*(rA++)输出,也就是A[i];

程序定义了一个类A,在主函数中声明了x1,x2=3两个对象,x1调用构造函数被初始化为默认值0,
然后用指针p指向x2,然后(*p)也就是x2调用setA()函数将x2更改为8,x1调用setA()函数将x1更改为10

程序定义了类XCF,在主函数中声明了一个对象d1=5,调用了构造函数输出1,然后用d1初始化d2,调用了
复制构造函数输出2,然后用new分配了一个XCF对象的空间,初始化为8,调用构造函数输出1,让pd指向这段空间,
之后delete pd,调用了析构函数输出8,最后程序运行结束调用d1,d2的析构函数输出两个5

程序用指针p想指向类A中的m,但是p的类型不对,应该是int A::*,实际上p指向的是相对于类A的偏移量

程序想用指针P指向类Point的getX()函数,但是P的类型不对,应该是int (Point::*)() const

程序用在arrayOfPoint类中用new关键字开辟了size个Point类的对象大小的空间,
用points指向这段空间,在主函数中声明了arrayOfPoint类的对象u,调用element()函数
返回points索引为index的Point对象的引用,然后调用move()函数将其修改并输出

主函数更改之后无法正常运行,因为当使用pointsArray1初始化pointsArray2时,
由于没有定义复制构造函数,系统会自动生成默认的复制构造函数,即将pointsArray1
的内容深度复制到pointsArray2中,此时pointsArray2中points也指向pointsArray1
中的points所指向的位置,因此当程序结束时,先析构pointsArray2,points指向的空间
已经被回收了,当析构pointsArray1时,delete[] points会出现错误