#include "LiveBaseWindow.h"
#include "resource.h"

CLiveBaseWindow::CLiveBaseWindow()
{
}

CLiveBaseWindow::~CLiveBaseWindow()
{
}

void CLiveBaseWindow::Init()
{
	CDuiBaseWindow::Init();
	SetIcon(IDI_ICON_KHB);
}