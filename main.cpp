#include <iostream>
#include "Player.h"
#include "funtion.h"
#include <Windows.h>
using namespace std;
int main() {
	init();//初始化并开始一盘新游戏
	CMD c;
	while (1) {
		c = Get_CMD();
		Deal_with(c);
		if (c == ESC) {
			HWND wnd = GetHWnd();
			if (MessageBox(wnd, _T("Are you sure to quit？"), _T("Notice"), MB_YESNO | MB_ICONQUESTION) == IDYES)
				Quit();
		}
	}
	return 0;
}