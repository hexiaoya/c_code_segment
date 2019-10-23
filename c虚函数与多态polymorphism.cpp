/*
��һ���������ָ֮��ָ��һ���������Ķ�����ô͸����ָ�����ֻ�ܵ��û������������ĳ�Ա����
�麯�����̬�ܹ������ָ��ָ����Ӧ����������еĺ���
�򵥵����������vitural�ؼ��ּ���
Ŀ����Ϊ��д��һ�����Ĵ���
�籾���༰�����ѭ��
CShape * pShape[6];
for(int i=0;i<6;i++)
	pShape[i]->display();
***********************************************************************************************
�����Ԥ�ڵ��������������¶���ĳһ����Ա��������ô����ڻ�������аѴ˺�����Ϊvirtual
MFC��������ʮ����Ҫ���麯����
��document�йص�Serialize��������view�йص�OnDraw������
��Ӧ�����Լ���CMyDoc��CMyView�и�д���������⺯����
***********************************************************************************************
ʵ�⣺�����ж���Ϊ�麯������������û�ж����麯����ָ��ָ��ľ��ǻ����еĺ����������
###�����������Ϊ���麯���Ļ����������б��붨��(��д)�麯�����������˵�������ˣ��������ע��Ϊ����
***********************************************************************************************
��������ͬ��ָ����˲�ͬ�ĺ������������ʳ�ΪPolymorphism����˼��the ability to assume many forms(��̬)��
���������ڱ����ڼ��ж�ִ���ĸ�����������ִ��ʱ�����������Ϊ���ڰ󶨻�̬�󶨡����麯���򱻳�Ϊ..
***********************************************************************************************
�ڻ����б�����Ӧ��ӵ��ĳ����ʱ�����Զ���Ϊ�պ���������������������Ϊ��������Ͳ�Ӧ�ñ����ã�����
�������ֱ��뱣��һ��ռ����������c++�ṩ�˴��麯����
virtual void display()=0;
���麯��ֻ��Ϊ������������б����¶��壬ֻ��Ϊ���ṩһ����̬�ӿڡ�
***********************************************************************************************
�麯�����ۣ�
1.������������������¶���һ����Ա��������ô��Ӧ���ڻ�������аѴ˺�����Ϊvirtual
2.�Ե�һָ�����ͬ�������������ʳ�Ϊ��̬
3.���⺯����c++�Ķ�̬�����Լ���̬�󶨵Ĺؼ�
4.�����������е����⺯�������㱻���ã����ǾͲ��ö�������Ӧ����Ϊ���麯����=0����
5.����˵ӵ�д��麯�����ǳ�������Ա���������
6.��������ܲ�������ʵ�壬���ǿ���ӵ��ָ���������ָ���Բ����������ĸ����������
7.���⺯��������ȥ��Ϊ���⺯��������ʡ��virtual�ؼ���
*/

#include <string.h>
#include <iostream>
using namespace std;
class CEmployee //ְԱ
{
private:
	char m_name[30];
public:
	CEmployee();
	CEmployee(const char* nm){strcpy(m_name,nm);}
	//virtual float computePay(){return 0;}  //������
	virtual float computePay()=0;
};
class CWage : public CEmployee //ʱнְԱ��һ��ְԱ
{
private:
	float m_wage;
	float m_hours;
public:
	CWage(const char* nm):CEmployee(nm){m_wage=250.0;m_hours=40.0;}
	void setWage(float wg){m_wage=wg;}
	void setHours(float hrs){m_hours=hrs;}
	virtual float computePay(){return m_wage*m_hours;}	//ע�����ຯ������������
};
class CSales : public CWage //����Ա��һ��ʱнְԱ
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
class CManager :public CEmployee //����Ҳ��һ��ְԱ
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