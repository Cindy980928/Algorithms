#include <ctime>
#include <cmath>
#include <iostream>  
#include <algorithm>
using namespace std;

#define INF 65535    // ���޴����
#define RANGE 100.0    // �������귶ΧΪ[-100,100]


typedef struct Point
{// ��ά�����ϵĵ�Point
	double x;
	double y;
}Point;

double Distance(Point a, Point b)
{//ƽ�������������֮��ľ��빫ʽ����
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool compareX(Point a, Point b)
{//�Զ�������������սṹ���е�x��Ա������������
	return a.x < b.x;
}

bool compareY(Point a, Point b)
{//�Զ�������������սṹ���е�y��Ա������������
	return a.y < b.y;
}

float ClosestPair(Point points[], int length, Point &a, Point &b)
{// ��������Լ�¼�����������¼��a��b��
	double distance;                   
	double d1, d2;                     
	int i = 0, j = 0, k = 0, x = 0;    
	Point a1, b1, a2, b2;              //����ָ�������Ӽ�����С���

	if (length < 2)
		return INF;    
	else if (length == 2)
	{//���Ӽ����ȵ���2��ֱ�ӷ��ظ�����ľ���
		a = points[0];
		b = points[1];
		distance = Distance(points[0], points[1]);
	}
	else
	{//�Ӽ����ȴ���3�����з������
		Point *s1 = new Point[length];     
		Point *s2 = new Point[length];

		sort(points, points + length, compareX);    
		double mid = points[(length - 1) / 2].x;    
		for (i = 0; i < length / 2; i++)
			s1[i] = points[i];
		for (int j = 0, i = length / 2; i < length; i++)
			s2[j++] = points[i];

		d1 = ClosestPair(s1, length / 2, a1, b1);             //���������벿���Ӽ��������  
		d2 = ClosestPair(s2, length - length / 2, a2, b2);    //��������Ұ벿���Ӽ��������  

		if (d1 < d2) 
		{ distance = d1; a = a1; b = b1; }            
		else
		{ distance = d2; a = a2; b = b2; }

		Point *s3 = new Point[length];

		for (i = 0, k = 0; i < length; i++)                        //ȡ������2�Ŀ�ȵ����е�Թ�k��    
			if (abs(points[i].x - mid) <= distance)
				s3[k++] = points[i];

		sort(s3, s3 + k, compareY);                                       // ��y����������ڵĵ㼯��

		for (i = 0; i < k; i++)
		{
			if (s3[j].x - mid >= 0)                                             // ֻ�ж���ಿ�ֵĵ�
				continue;
			x = 0;
			for (j = i + 1; j <= i + 6 + x && j < k; j++)            //ֻ�����������ӵĵ�6������бȽ�
			{
				if (s3[j].x - mid < 0)
				{//  ����i����λ��mid�����ֻ���ж���mid�ұߵ�j�㼴��
					x++;
					continue;
				}
				if (Distance(s3[i], s3[j]) < distance)
				{//�����ָ��ߵ��������С����֪��С���룬���¼�þ��������
					distance = Distance(s3[i], s3[j]);
					a = s3[i];
					b = s3[j];
				}
			}
		}
	}
	return distance;
}

void SetPoints(Point *points, int length)
{//��������Ե�����points�еĶ�ά����г�ʼ��
	srand(unsigned(time(NULL)));
	for (int i = 0; i < length; i++)
	{
		points[i].x = (rand() % int(RANGE)) - RANGE;
		points[i].y = (rand() % int(RANGE)) - RANGE;
	}
}

int main()
{
	int num;            //������ɵĵ�Ը���
	Point a, b;            //������
	double diatance;    //��Ծ���

	cout << "�������ά��Ը���:";
	cin >> num;
	if (num < 2)
		cout << "��������ڵ���2�ĵ��������" << endl;
	else
	{
		cout << endl << "������ɵ�" << num << "����ά������£�" << endl;
		Point *points = new Point[num];

		SetPoints(points, num);
		for (int i = 0; i < num; i++)
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
		diatance = ClosestPair(points, num, a, b);
		

		cout << endl << "������Ϊ��" << "(" << a.x << "," << a.y << ")��" << "(" << b.x << "," << b.y << ")" << endl << "�����Ծ���Ϊ��" << diatance << endl;
	}
	system("pause");
}