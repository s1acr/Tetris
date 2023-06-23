#include "Player.h"
void Player::update_score() {
	//覆盖掉上一次的分数
	setfillcolor(0x1e2227);
	solidrectangle(315, 205, 415, 230);
	//输出当前分数
	settextcolor(0xffffff);
	TCHAR s[12];
	_stprintf(s, _T("%10d"), score);  // 先将分数格式化输出为字符串
	outtextxy(270, 205, s);			   //输出当前分数
}
void Player::plus_score(int combo) {
	switch (combo) { 
		case 1:
			score += 10;
			Beep(523, 500);
			break;
		case 2: 
			score += 30;
			Beep(698, 500);
			break;
		case 3:
			score += 60;
			Beep(880, 500);
			break;
		case 4:
			score += 100;
			Beep(1046, 500);
			break;
	}
}
void Player::clear_score() {
	score = 0;
}