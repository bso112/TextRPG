#include <crtdbg.h> // _CrtDumpMemoryLeaks() 사용하기위해
#if _DEBUG 
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__) 
#endif // 몇행에서 메모리 누수가 나는지 알려줌. 
using namespace std;
int main()
{
	int *a = new int; 
	_CrtDumpMemoryLeaks(); // 메모리 누수 체크 
	return 0; 
}