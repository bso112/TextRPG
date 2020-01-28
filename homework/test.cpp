#include <iostream>

using namespace std;

void printFile(char fileName[30])
{
	FILE* fp;
	errno_t err = fopen_s(&fp, fileName, "rt");

	if (0 == err)
	{
		char ch = 0;
		while (true)
		{
			int cnt = fread(&ch, sizeof(char), 1, fp);
			if (1 > cnt)
				break;
			cout << ch;

		}
		fclose(fp);
	}

	cout << '\n';
}

void main()
{

	printFile("../slime.txt");
	
}

