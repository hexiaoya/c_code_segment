/*
以一个基础类别之指针指向一个衍生类别的对象，那么透过该指针你就只能调用基础类别所定义的成员函数
虚函数与多态能够让这个指针指向相应的衍生类别中的函数
简单的如此例加上vitural关键字即可
目的是为了写出一氧化的代码
如本例亦及下面的循环
CShape * pShape[6];
for(int i=0;i<6;i++)
	pShape[i]->display();
***********************************************************************************************
如果你预期的衍生类别可能重新定义某一个成员函数，那么你就在基础类别中把此函数设为virtual
MFC中有两个十分重要的虚函数：
与document有关的Serialize函数和与view有关的OnDraw函数。
你应该在自己的CMyDoc和CMyView中改写这两个虚拟函数。
***********************************************************************************************
实测：基类中定义为虚函数，衍生类中没有定义虚函数，指针指向的就是基类中的函数不会出错
###但是如果定义为纯虚函数的话，衍生类中必须定义(重写)虚函数，否则出错（说不明白了，下面代码注释为例）
***********************************************************************************************
我们以相同的指令唤起了不同的函数，这种性质称为Polymorphism，意思是the ability to assume many forms(多态)。
编译器不在编译期间判断执行哪个函数而是在执行时期评估，这称为后期绑定或动态绑定。非虚函数则被称为..
***********************************************************************************************
在基类中本来不应该拥有某动作时，可以定义为空函数，不过并不高明，因为这个函数就不应该被调用，我们
不定义又必须保留一块空间给他，所以c++提供了纯虚函数：
virtual void display()=0;
纯虚函数只是为了在衍生类别中被重新定义，只是为了提供一个多态接口。
***********************************************************************************************
虚函数结论：
1.如果期望衍生类中重新定义一个成员函数，那么就应该在基础类别中把此函数设为virtual
2.以单一指令换气不同函数，这种性质称为多态
3.虚拟函数是c++的多态性质以及动态绑定的关键
4.如果抽象类别中的虚拟函数不打算被调用，我们就不该定义它，应该设为纯虚函数加=0即可
5.可以说拥有纯虚函数的是抽象类别，以别与具象类别
6.抽象类别不能产生对象实体，但是可以拥有指向抽象类别的指针以操作抽象类别的各个衍生类别
7.虚拟函数衍生下去仍为虚拟函数，可以省略virtual关键词
*/

#include <string.h>
#include <iostream>
using namespace std;
class CEmployee //职员
{
private:
	char m_name[30];
public:
	CEmployee();
	CEmployee(const char* nm){strcpy(m_name,nm);}
	//virtual float computePay(){return 0;}  //不高明
	virtual float computePay()=0;
};
class CWage : public CEmployee //时薪职员是一种职员
{
private:
	float m_wage;
	float m_hours;
public:
	CWage(const char* nm):CEmployee(nm){m_wage=250.0;m_hours=40.0;}
	void setWage(float wg){m_wage=wg;}
	void setHours(float hrs){m_hours=hrs;}
	virtual float computePay(){return m_wage*m_hours;}	//注释这类函数看编译现象
};
class CSales : public CWage //销售员是一种时薪职员
{
private:
	float m_comm;
	float m_sale;
public:
	CSales(const char* nm):CWage(nm){m_comm=m_sale=0.0;}
	void setCommission(float comm){m_comm=comm;}
	void setSales(float sale){m_sale=sale;}
	virtual float computePay(){return m_comm*m_sale+CWage::computePay();}
};
class CManager :public CEmployee //经理也是一种职员
{
private:
	float m_salary;
public:
	CManager(const char* nm) : CEmployee(nm) {m_salary=15000.0;}
	void setSalary(float salay){m_salary=salay;}
	virtual float computePay(){return m_salary;}
};
void main()
{
	CManager aManager("m");
	CSales aSales("s");
	CWage aWager("w");
	CEmployee* pemp;
	pemp=&aManager;
	cout << pemp->computePay() << endl;
	getchar();
}