#pragma once

#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <crtdbg.h> // _CrtDumpMemoryLeaks() ����ϱ�����

#include "Character.h"
#include "Monster.h"
#include "factory.cpp"
#include "BattleManager.h"
#include "Parser.h"
#include "Shop.h"



#if _DEBUG 
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__) 
#endif // ���࿡�� �޸� ������ ������ �˷���. 

