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


class A    //����һ����A��������3���麯��
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
        cout << "Derive A()" << endl;    // ����Base1::A()
    }
    virtual void D()
    {
        cout << "Derive D()" << endl;    // ����Base2::D()
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
    cout << "address of vtbl : " << *(int*)(a) << endl;  //&a�õ�����a���׵�ַ��ǿ��ת��Ϊ(int *)����Ϊ����&a��ʼ��4���ֽڿ���һ�����壬��&a�������4�ֽ�������׵�ַ����ͨ����*�������������н����ã����յõ�����4���ֽ�������ɵĵ�ַ��Ҳ�������ĵ�ַ��
    cout << a << endl;
    cout << &a->x << endl; //64λ ���8�ֽ�
    
    //https://cloud.tencent.com/developer/article/1599283
    typedef void (*Func)();
    Derive d;
    Base1& b1 = d;
    Base2& b2 = d;
    cout << "Derive������ռ���ڴ��СΪ��" << sizeof(d) << endl;
    
    cout << "\n---------��һ���麯����-------------" << endl;
    long* tmp1 = (long*)&d;              // ��ȡ��һ���麯�����ָ��
    long* vptr1 = (long*)(*tmp1);         // ��ȡ�麯����
    
    Func x1 = (Func)vptr1[0];
    Func x2 = (Func)vptr1[1];
    Func x3 = (Func)vptr1[2];
    Func x4 = (Func)vptr1[3];
    x1();
    x2();
    x3();
    x4(); //�������Լ����麯�����ڵ�һ���麯����ĺ���
    
    cout << "\n---------�ڶ����麯����-------------" << endl;
    long* tmp2 = tmp1 + 1;               // ��ȡ�ڶ����麯����ָ�� �൱������4���ֽ�
    long* vptr2 = (long*)(*tmp2);
    
    Func y1 = (Func)vptr2[0];
    Func y2 = (Func)vptr2[1];
    y1();
    y2();
    
    //�򵥵��ܽ�һ�£�
    //
    //    1. ÿһ�����඼�����Լ����麯������������麯������������ݼ̳еĻ��������������
    //    2. ��������麯�����˳�򣬺ͼ̳�ʱ��˳����ͬ��
    //    3. �������Լ����麯�����ڵ�һ���麯����ĺ��棬˳��Ҳ�ǺͶ���ʱ˳����ͬ��
    //    4. �������������Ҫ���Ǹ����е��麯������ô�����麯�����д�����λ�á�
    int nb1 = sizeof(b1);
    int nb2 = sizeof(b2);
    int nd = sizeof(d);
    cout << nb1 << endl;
    cout << nb2 << endl;
    cout << nd << endl;
    return 0;
}