#include <iostream>
using namespace std;
template <class T> 
T power(T base,int exponent)	// <class T> 表示T是一种类型，而这种类型将在调用此函数时才给予
{
	T result=base;
	if(exponent==0) return (T)1;
	if(exponent<0) return (T)0;
	while(--exponent) result *=base;
	return result;
}
template <class T>
class CThree
{
public:
	CThree(T t1,T t2,T T3);
	T Min();
	T Max();
private:
	T a,b,c;
};
template <class T>
CThree<T>::CThree(T t1,T t2,T t3) :
	a(t1),b(t2),c(t3)
{
	return;
}
template <class T>
T CThree<T>::Max()
{
	T temp;
	temp=a>b?a:b;
	return temp>c?temp:c;
}
template <class T>
T CThree<T>::Min()
{
	T temp;
	temp=a<b?a:b;
	return temp<c?temp:c;
}
int main()
{
	int i=power(5,4);
	long l=power(1000L,3);
	long double d=power(1e5,2);
	cout << "i=" << i << endl;
	cout << "l=" << l << endl;
	cout << "d=" << d << endl;
	CThree<int> ci(2,4,1);
	CThree<float> cf(3.5,2.6,1);
	cout << "int min " << ci.Min() << endl;
	cout << "int max " << ci.Max() << endl;
	cout << "float min " << cf.Min() << endl;
	cout << "float max " << cf.Max() << endl;

	getchar();
	return 0;
}