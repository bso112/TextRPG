#include "stdafx.h"
#include "Inventory.h"

int CInventory::GetInventorySize()
{
	int size = potions.size() + weapons.size() + gems.size();
	return size;
}