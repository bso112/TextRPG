#include <iostream>

using namespace std;


int stringToInt(char arr[])
{
	//���ڿ�->���� �Ľ�
	int result = 0;
	int len = strlen(arr);

	for (int i = 0; i < len; ++i)
	{
		int tmp = arr[i] - '0';
		result += (int)(tmp * (pow((double)10, (double)len-i-1)));
	}

	// 1  1 
	// 2  10
	// 3  100
	// 10�� 0���� 1 / 1���� 10 ...

	return result;
}

void main()
{
	cout << stringToInt("1546");
} 

