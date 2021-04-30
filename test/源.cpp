#include <iostream>
using namespace std;

int main()
{
	int clja[4];
	clja[100] = 3;
	clja[109] = 4;
	clja[200] = 5;
	clja[0] = 6;
	//clja[9999] = 10;

	cout << clja[100]<<" "<<clja[109]<<" "<<clja[200]<<" "<<clja[0];
}