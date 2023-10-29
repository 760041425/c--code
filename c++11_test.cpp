#include <iostream>
#include <stdio.h>
using namespace std;


class ibase
{
public:
    ibase()
    {
    }
    
    ~ibase()
    {
    }
    void p()
    {
        printf("iBase\n");
    }
    virtual void vir()
    {
        printf("iBase vir\n");
    }
private:

};

class ts : public ibase
{
public:
    ts();
    ~ts();
    void p()
    {
        printf("ts \n");
    }
    void vir()
    {
        printf(" vir\n");
    }
private:

};

ts::ts()
{
}

ts::~ts()
{
}


class A    //定义一个类A，类中有3个虚函数
{
public:
    int x;
    int y;
    virtual void f()
    {
        cout << "f() called !" << endl;
    };
    virtual void f1()
    {
        cout << "f1() called !" << endl;
    };
    virtual void f2()
    {
        cout << "f2() called !" << endl;
    };
    
};


class Base1
{
public:
    virtual void A()
    {
        cout << "Base1 A()" << endl;
    }
    virtual void B()
    {
        cout << "Base1 B()" << endl;
    }
    virtual void C()
    {
        cout << "Base1 C()" << endl;
    }
};

class Base2
{
public:
    virtual void D()
    {
        cout << "Base2 D()" << endl;
    }
    virtual void E()
    {
        cout << "Base2 E()" << endl;
    }
};

class Derive : public Base1, public Base2
{
public:
    virtual void A()
    {
        cout << "Derive A()" << endl;    // 覆盖Base1::A()
    }
    virtual void D()
    {
        cout << "Derive D()" << endl;    // 覆盖Base2::D()
    }
    virtual void MyA()
    {
        cout << "Derive MyA()" << endl;
    }
    
};

int main(int argc, char* argv[])
{


    ibase* pI = new ibase();
    pI->p();
    
    auto ts1 = new ts();
    ts1->p();
    ibase* base = new ts();
    base->p();
    base->vir();
    auto p1 = &ts1;
    auto p2 = &p1;
    
    
    
    A* a = new A;
    cout << hex;
    cout << "address of a : " << a << endl;
    cout << "address of vtbl : " << *(int*)(a) << endl;  //&a得到对象a的首地址，强制转换为(int *)，意为将从&a开始的4个字节看作一个整体，而&a就是这个4字节整体的首地址，再通过“*”对这个整体进行解引用，最终得到由这4个字节数据组成的地址，也就是虚表的地址。
    cout << a << endl;
    cout << &a->x << endl; //64位 相差8字节
    
    //https://cloud.tencent.com/developer/article/1599283
    typedef void (*Func)();
    Derive d;
    Base1& b1 = d;
    Base2& b2 = d;
    cout << "Derive对象所占的内存大小为：" << sizeof(d) << endl;
    
    cout << "\n---------第一个虚函数表-------------" << endl;
    long* tmp1 = (long*)&d;              // 获取第一个虚函数表的指针
    long* vptr1 = (long*)(*tmp1);         // 获取虚函数表
    
    Func x1 = (Func)vptr1[0];
    Func x2 = (Func)vptr1[1];
    Func x3 = (Func)vptr1[2];
    Func x4 = (Func)vptr1[3];
    x1();
    x2();
    x3();
    x4(); //派生类自己的虚函数放在第一个虚函数表的后面
    
    cout << "\n---------第二个虚函数表-------------" << endl;
    long* tmp2 = tmp1 + 1;               // 获取第二个虚函数表指针 相当于跳过4个字节
    long* vptr2 = (long*)(*tmp2);
    
    Func y1 = (Func)vptr2[0];
    Func y2 = (Func)vptr2[1];
    y1();
    y2();
    
    //简单的总结一下：
    //
    //    1. 每一个基类都会有自己的虚函数表，派生类的虚函数表的数量根据继承的基类的数量来定。
    //    2. 派生类的虚函数表的顺序，和继承时的顺序相同。
    //    3. 派生类自己的虚函数放在第一个虚函数表的后面，顺序也是和定义时顺序相同。
    //    4. 对于派生类如果要覆盖父类中的虚函数，那么会在虚函数表中代替其位置。
    int nb1 = sizeof(b1);
    int nb2 = sizeof(b2);
    int nd = sizeof(d);
    cout << nb1 << endl;
    cout << nb2 << endl;
    cout << nd << endl;
    return 0;
}