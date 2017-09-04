#include <windows.h>
#include "UIApp.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdline,
	int iCmdshow)
{
	AflGetUIApp()->SetMainInstance(hInstance);
	AflGetUIApp()->Start();
	AflGetUIApp()->Join();

	return 0;
}