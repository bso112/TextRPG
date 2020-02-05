#include "stdafx.h"
#include "Potion.h"
#include "Parser.h"


void CPotion::printPotionInfo()
{
	CParser parser;
	cout << "\n\n";
	cout << name << '\n';
	parser.PrintFile(GFX_PATH);
	cout << '\n';
	cout << "ȸ����: " << healAmount << '\n';
	cout << description << '\n';
	cout << "����: " << price << '\n';
	cout << "==========================================================================================" << endl;
}
