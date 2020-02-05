#include "stdafx.h"
#include "Bufitem.h"
#include "Parser.h"

void CBufItem::PrintGemInfo()
{
	CParser parser;
	parser.PrintFile(GFX_PATH);
	cout << "이름: " << name << endl;
	cout << "공격력: " << attackBuf << endl;
	cout << "최대체력: " << maxHealthBuf << endl;
	char arr[16] = "";
	parser.ElementToString(element, arr);
	cout << "속성: " << arr << endl;
	cout << "가치: " << price << endl;
	cout << description << endl;


}