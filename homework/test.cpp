#include <iostream>
#include <vector>
using namespace std;

typedef struct tagPotion
{
	int id = 0;
}POTION;

typedef struct tagInventory
{
	vector<POTION*> potions;

}INVENTORY;

typedef struct tagChracter
{

	INVENTORY *inventory;

}CHARACTER;


CHARACTER* MakeCharacter()
{
	CHARACTER* c = new CHARACTER;
	c->inventory = new INVENTORY;
	return c;
}

void main()
{
	
	CHARACTER* c = MakeCharacter();

	POTION* p = new POTION;
	c->inventory->potions.push_back(p);

	int size = c->inventory->potions.size();
	cout << size << endl;
	for (int i = 0; i < size; ++i)
	{
		delete c->inventory->potions[i];
	}
	delete c->inventory;
}





