#include "Player.h"
void Player::update_score() {
	//���ǵ���һ�εķ���
	setfillcolor(0x1e2227);
	solidrectangle(315, 205, 415, 230);
	//�����ǰ����
	settextcolor(0xffffff);
	TCHAR s[12];
	_stprintf(s, _T("%10d"), score);  // �Ƚ�������ʽ�����Ϊ�ַ���
	outtextxy(270, 205, s);			   //�����ǰ����
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