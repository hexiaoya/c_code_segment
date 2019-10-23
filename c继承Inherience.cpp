#include <stdio.h>
#include <stdlib.h>
class CShape
{
protected:
	int m_color;
public:
	void setcolor(int color){m_color=color;}
};
class CRect : public CShape
{
public:
	void display()
	{
		char color[30];
		sprintf(color,"color %d%d",0,m_color);
		system(color);
		printf("·½");
	}
};
class CCircle : public CShape
{
public:
	void display()
	{
		char color[30];
		sprintf(color,"color %d%d",0,m_color);
		//printf(color);
		system(color);
		printf("Ô²");
	}
};


int main()
{
	CRect rect;
	CCircle circle;
	rect.setcolor(2);
	rect.display();
	_sleep(1000);
	circle.setcolor(9);
	circle.display();
	getchar();
	return 0;
}
