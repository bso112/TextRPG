#include "stdafx.h"
#include "Bufitem.h"
#include "Parser.h"

void CBufItem::PrintGemInfo()
{
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << "�̸�: " << name << endl;
	cout << "���ݷ�: " << attackBuf << endl;
	cout << "�ִ�ü��: " << maxHealthBuf << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "�Ӽ�: " << arr << endl;
	cout << "��ġ: " << price << endl;
	cout << description << endl;


}