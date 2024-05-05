#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
struct tagClass
{
	int m;
	string* subject;
	double* totalAve;
	int n;
};
struct tagStudent
{
	int id = 0;
	string name;
	int* score = 0;
	double ave = 0;
	int rank = 0;
};
typedef tagClass Class;
typedef tagStudent Student;
void drawHr(int n)
{
	int i;
	for (i = 0; i < n; i++)
		cout << "-";
	cout << endl;
	cout << endl;
}
void readStructure(ifstream& file, Class& myclass)
{
	file >> myclass.m;
	int m = myclass.m;
	int j;
	myclass.subject = new string[m];
	myclass.totalAve = new double[m];
	for (j = 0; j < m; j++)
	{
		file >> myclass.subject[j];
	}
}
void readScore(ifstream& file, Class& myclass, Student*& students)
{
	file >> myclass.n;
	int n = myclass.n;
	int m = myclass.m;
	int i;
	int j;
	students = new Student[n];
	for (j = 0; j < n; j++)
		students[j].score = new int[m];
	for (i = 0; i < n; i++)
	{
		file >> students[i].id;
		file >> students[i].name;
		for (j = 0; j < m; j++)
			file >> students[i].score[j];
	}
}

void drawbarchart(Class& myclass, Student*& students)
{
	int n = myclass.n;
	int m = myclass.m;
	int i;
	int j;
	int nHr = 145;
	cout << "\tRange\t\tcount" << endl;
	drawHr(nHr);
	int total = 0;
	for (i = 0; i < n; i++)
	{

		if (90 <= students[i].ave && students[i].ave <= 100)
			total++;
	}
	cout << "\t90~100\t" << total << "\t";
	for (int i = 0; i < total; i++)
	{
		cout << "*";
	}
	cout << endl;


	int num = 90;
	for (int j = 0; j < 9; j++)
	{
		int total = 0;
		for (i = 0; i < n; i++)
		{

			if ((num - 10) <= students[i].ave && students[i].ave < num)
				total++;
		}
		cout << "\t" << num - 10 << "~" << num << "\t" << total << "\t";
		for (int i = 0; i < total; i++)
		{
			cout << "*";
		}
		cout << endl;
		num = num - 10;
	}
}
void show(Class& myclass, Student*& students)
{
	int n = myclass.n;
	int m = myclass.m;
	int i;
	int j;
	int nHr = 145;
	cout << "id\tname\t";
	for (j = 0; j < m; j++)
		cout << myclass.subject[j] << "\t";
	cout << "average\trank" << endl;
	drawHr(nHr);
	for (i = 0; i < n; i++)
	{
		cout << students[i].id << "\t";
		cout << students[i].name << "\t";
		for (j = 0; j < m; j++)
			cout << setw(3) << students[i].score[j] << "\t";
		cout << fixed << setw(5) << setprecision(1) << students[i].ave << "\t" << setw(4) << students[i].rank << endl;
	}
	drawHr(nHr);
	cout << "\tAverage\t";
	for (j = 0; j < m; j++)
		cout << setw(5) << setprecision(1) << myclass.totalAve[j] << "\t";
	cout << endl;
	drawHr(nHr);

	drawbarchart(myclass, students);
}
void computeAve(Class& myclass, Student*& students)
{
	int m = myclass.m;
	int n = myclass.n;
	int i;
	int j;
	for (j = 0; j < m; j++)
		myclass.totalAve[j] = 0;
	for (i = 0; i < n; i++)
	{
		students[i].ave = 0;
		for (j = 0; j < m; j++)
		{
			students[i].ave += students[i].score[j];
			myclass.totalAve[j] += students[i].score[j];
		}
		students[i].ave /= m;
	}
	for (j = 0; j < m; j++)
		myclass.totalAve[j] /= n;
}
void computeRank(Class& myclass, Student*& students)
{
	int i;
	int j;
	for (i = 0; i < myclass.n; i++)
	{
		students[i].rank = 0;
		for (j = 0; j < myclass.n; j++)
			if (students[i].ave <= students[j].ave) students[i].rank++;
	}
}
void swapWithNext(int i, Student*& students)
{
	struct tagStudent temp;
	temp = students[i];
	students[i] = students[i + 1];
	students[i + 1] = temp;
}
void sort(Class& myclass, Student*& students)
{
	int n = myclass.n;
	int i;
	int j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = n - 2; j >= i; j--)
		{
			if (students[j].ave < students[j + 1].ave)
			{
				swapWithNext(j, students);
			}
		}
	}
}
void free(Class& myclass, Student*& students)
{
	int i;
	for (i = 0; i < myclass.n; i++)
		delete[] students[i].score;
	delete[] students;
	delete[] myclass.subject;
	delete[] myclass.totalAve;
}

void demo2()
{
	Class myclass;
	Student* students;
	ifstream file;
	file.open("data.txt");
	readStructure(file, myclass);
	readScore(file, myclass, students);
	file.close();
	computeAve(myclass, students);
	computeRank(myclass, students);
	sort(myclass, students);
	show(myclass, students);
	free(myclass, students);
}
int main()
{
	demo2();
	return 0;
}