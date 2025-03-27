#include <stdio.h>

typedef void (*Func1)();
typedef void (*Func2)();
typedef void (*Func3)();

// 虚函数表
typedef struct VFunTable {
    Func1 eat;
    Func2 sleep;
    Func3 walk;
} VFunTable;

// 基类
typedef struct base {
    VFunTable vptr;
    const char kind[20];
} Base;

// 派生类
typedef struct derive {
    Base base;
    const char kind[20];
} Derive;

void base_eat() {
    printf("base eat\n");
}

void base_sleep() {
    printf("base sleep\n");
}

void base_walk() {
    printf("base walk\n");
}

void derive_eat() {
    printf("derive eat\n");
}

void derive_sleep() {
    printf("derive sleep\n");
}

void derive_walk() {
    printf("derive walk\n");
}

void init(Base* b, Derive* d) {
    b->vptr.eat = base_eat;
    b->vptr.sleep = base_sleep;
    b->vptr.walk = base_walk;

    d->base.vptr.eat = derive_eat;
    d->base.vptr.sleep = derive_sleep;
    d->base.vptr.walk = derive_walk;
}

int main(void) {
    Base b;
    Derive d;
    init(&b, &d);

    Base* pb = &b;
    Base* pb2 = (Base*)&d;

    pb->vptr.eat();
    pb2->vptr.eat();

    printf("%p\n", pb);
    printf("%p\n", &pb->vptr.walk);
    printf("%p\n", pb2);
    printf("%p\n", &pb2->vptr.walk);

    return 0;
}
// 输出
//  base eat
//  derive eat