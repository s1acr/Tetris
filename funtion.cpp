#include "funtion.h"
DWORD oldtime = 0;
Player p1;
void init() {
	initgraph(480, 545);
	srand((unsigned)time(NULL));  //��ʼ�����������
	setbkcolor(BKCOLOR);		  //���ñ���ɫ
	setbkmode(TRANSPARENT);		  // ����ͼ�����ı���ɫΪ͸��
	cleardevice();				  //�õ�ǰ����ɫ����

	// ��ʾ����˵��
	setcolor(0xffffff);
	settextstyle(15, 0, _T("Bold"));
	outtextxy(295, 130, _T("next block"));

	outtextxy(300, 355, _T("operations:"));
	outtextxy(300, 380, _T("up:    trotate"));
	outtextxy(300, 405, _T("left�� move left"));
	outtextxy(300, 430, _T("right��move right"));
	outtextxy(300, 455, _T("down�� move down"));
	outtextxy(300, 480, _T("space��quick sink"));
	outtextxy(300, 505, _T("ESC��  quit"));
	outtextxy(300, 200, _T("scores:"));
	// ��������ԭ��
	setorigin(20, 20);

	// ������Ϸ���߽�
	rectangle(-1, -1, WIDTH * UNIT + 2, HEIGHT * UNIT + 2);
	rectangle((WIDTH + 1) * UNIT, 0, (WIDTH + 5) * UNIT, 4 * UNIT);
	p1.update_score();
	New_Game();
}
void New_Game() {
	srand((unsigned)time(NULL));  //��ʼ�����������
	setfillcolor(BKCOLOR);
	solidrectangle(0, 0, WIDTH * UNIT, HEIGHT * UNIT);
	memset(blocks_maps, 0, sizeof(blocks_maps));
	p1.clear_score();
	p1.update_score();
	next_block.id = rand() % 7;
	next_block.direction = rand() % 4;
	next_block.x = 11;
	next_block.y = 0;
	New_Block();
}
bool Check_Block(BLOCK block) {
	int d = block.get_nowTB();	//��ȡ��16���ƴ洢�ĵ�ǰ����˹�������Ϣ
	for (int i = 0; i < 16; i++, d <<= 1) {
		if (d & 0x8000) {  //ȡ��ÿһλ����Ϊ1�����λ�÷���
			int ux = block.x + i % 4;
			int uy = block.y + i / 4;
			if (ux < 0 || ux >= WIDTH || uy >= HEIGHT)	//���겻�Ϸ�
				return false;
			if (uy >= 0 &&
				blocks_maps[ux][uy] == 1)  //����Ϸ�����λ���з�������Ҳ����
				return false;
		}
	}
	return true;
}
void Edit_UnitBlock(int x, int y, COLORREF col, Editmode mode) {
	int right = (x + 1) * UNIT;
	int bottom = (y + 1) * UNIT;
	int left = right - UNIT;
	int top = bottom - UNIT;
	switch (mode) {
		case DRAW:
			setlinecolor(0xc0c0c0);	
			roundrect(left, top, right, bottom, 8, 8);
			setfillcolor(col);
			solidroundrect(left + 2, top + 2, right - 2, bottom - 2, 5, 5);
			break;
		case CLEAR:
			setfillcolor(BKCOLOR);
			solidrectangle(left, top, right, bottom);
			break;
		case FIX:
			setlinecolor(0x000000);	
			roundrect(left, top, right, bottom, 8, 8);
			setfillcolor(col);
			solidroundrect(left + 2, top + 2, right - 2, bottom - 2, 5, 5);
			break;
		default: break;
	}
}
void Edit_Block(BLOCK block, Editmode mode) {
	int d = block.get_nowTB();	//��ȡ��16���ƴ洢�ĵ�ǰ����˹�������Ϣ
	for (int i = 0; i < 16; i++, d <<= 1) {
		if (d & 0x8000) {  //ȡ��ÿһλ����Ϊ1����Ƹ�λ�÷���
			int ux = block.x + i % 4;
			int uy = block.y + i / 4;
			if (uy >= 0)
				Edit_UnitBlock(ux, uy, block.get_nowcol(), mode);
		}
	}
}
void Avoid_Repeat() {
	int id = next_block.id;
	next_block.T_Blocks[id].occurence;
	while (next_block.T_Blocks[id].occurence >= 2) {
		next_block.id = rand() % 7;
		next_block.direction = rand() % 4;
		if (next_block.id == id)
			continue;
	}
	next_block.T_Blocks[id].occurence = 0;
}
void New_Block() {	//�����·��� ����ǰ������Ϊ��һ������ �������ȡ��һ������
	now_block.direction = next_block.direction;
	now_block.id = next_block.id;
	now_block.x = 3, now_block.y = -3;
	next_block.x = 11, next_block.y = 0;
	next_block.id = rand() % 7;
	next_block.direction = rand() % 4;
	Avoid_Repeat();
	int b = now_block.get_nowTB();
	while ((b & 0xF) == 0) {  //�����±�����û�з���ʱ������ ֱ���оֲ���ʾ
		now_block.y++;
		b >>= 4;
	}
	//���Ƶ�ǰ����
	Edit_Block(now_block);
	//����Ԥ��������
	setfillcolor(BKCOLOR);
	solidrectangle((WIDTH + 1) * UNIT + 1, 1, (WIDTH + 5) * UNIT - 1,
				   4 * UNIT - 1);  //������һ�εķ���
	Edit_Block(next_block);
}
CMD Get_CMD() {
	while (1) {
		DWORD newtime = GetTickCount();	 //��ȡ��ʱ��
		if (newtime - oldtime >= 500) {	 //ʱ��������500ms��������һ��
			oldtime = newtime;
			return DOWN;
		}
		if (_kbhit()) {	 //���м��̰������򷵻���
			switch (_getch()) {
				case 'w':
				case 'W': 
					cout << "w" << endl;
					return ROTATE;
				case 's':
				case 'S': 
					cout << "s" << endl;
					return DOWN;
				case 'a':
				case 'A':
					cout << "a" << endl;
					return LEFT;
				case 'd':
				case 'D': 
					cout << "d" << endl;
					return RIGHT;
				case ' ': 
					cout << "space" << endl;
					return SINK;	//�����³�
				case 27: return ESC;	// ESC��
				case 0:	 //��ȡ���ܼ����ļ�ʱ��_getch()��һ�η���0��0xE0���ڶ��η��ض�Ӧ��ֵ��
				case 0xE0:
					switch (_getch()) {
						case 72: return ROTATE;	 //��
						case 80: return DOWN;	 //��
						case 75: return LEFT;	 //��
						case 77: return RIGHT;	 //��
					}
			}
		}
	}
}
void Deal_with(CMD c) {
	switch (c) {
		case ROTATE: 
			CMD_ROTATE(); break;
		case DOWN: CMD_DOWN(); break;
		case LEFT: CMD_LEFT(); break;
		case RIGHT: CMD_RIGHT(); break;
		case SINK: CMD_SINK(); break;
		case ESC: break;
	}
}
void Fix_BLOCK(BLOCK block) {
	int d = block.get_nowTB();	//��ȡ��16���ƴ洢�ĵ�ǰ����˹�������Ϣ
	for (int i = 0; i < 16; i++, d <<= 1) {
		if (d & 0x8000) {  //ȡ��ÿһλ����Ϊ1���Ǹ�λ�÷���
			int ux = block.x + i % 4;
			int uy = block.y + i / 4;
			if (uy <= 0) {	//�̶�����ĸ߶ȳ�����Ϸ����߶�
				Game_Over();
				return;
			}
			else
				blocks_maps[ux][uy] = 1;
		}
	}
}
void Quit() {
	closegraph();
	exit(0);
}
void Game_Over() {
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, _T("GameOver\nRestart��"), _T("Notice"),
				   MB_YESNO | MB_ICONQUESTION) == IDYES)
		New_Game();
	else
		Quit();
}
void Rotate(int dir, int dx) {
	Edit_Block(now_block, CLEAR);
	now_block.direction = dir;
	now_block.x += dx;
	Edit_Block(now_block);
}
void CMD_ROTATE() {
	BLOCK temp = now_block;
	int dx = 0;
	temp.direction++;
	temp.direction %= 4;
	if (Check_Block(temp)) {
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x - 1;
	if (Check_Block(temp)) {
		dx = -1;
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x + 1;
	if (Check_Block(temp)) {
		dx = 1;
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x - 2;
	if (Check_Block(temp)) {
		dx = -2;
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x + 2;
	if (Check_Block(temp)) {
		dx = 2;
		Rotate(temp.direction, dx);
		return;
	}
}
void CMD_DOWN() {
	BLOCK temp = now_block;
	temp.y++;
	if (Check_Block(temp)) {
		Edit_Block(now_block, CLEAR);
		Edit_Block(temp);
		now_block = temp;
	}
	else
		CMD_SINK();
}
void CMD_LEFT() {
	BLOCK temp = now_block;
	temp.x--;
	if (Check_Block(temp)) {
		Edit_Block(now_block, CLEAR);
		now_block = temp;
		Edit_Block(now_block);
	}
}
void CMD_RIGHT() {
	BLOCK temp = now_block;
	temp.x++;
	if (Check_Block(temp)) {
		Edit_Block(now_block, CLEAR);
		now_block = temp;
		Edit_Block(now_block);
	}
}
void CMD_SINK() {
	//������ǰ����
	Edit_Block(now_block, CLEAR);
	BLOCK temp = now_block;
	temp.y++;
	while (Check_Block(temp)) {	 //���Ƶ�ǰ����ֱ������������
		now_block.y++;
		temp.y++;
	}
	//�̶������Ƶ�ǰ����
	Edit_Block(now_block, FIX);
	Fix_BLOCK(now_block);
	//����Ƿ���Ҫ�������У�һ���������4�У�
	bool flag = false;
	bool line[4] = {false};	 //��Ƿ����漰�������Ƿ�����
	int combo = 0;
	for (int i = 0; i < 4; i++) {  //���ϵ��� ��Ǹ����Ƿ�����
		int y = now_block.y + i;
		int cnt = 0;
		for (int x = 0; x < WIDTH; x++) {
			if (blocks_maps[x][y] == 1)
				cnt++;
		}
		if (cnt == WIDTH) {	 //������Ҫ������
			combo++;
			flag = true;
			line[i] = true;
			setfillcolor(LIGHTGREEN);
			setlinecolor(LIGHTGREEN);
			setfillstyle(BS_HATCHED, HS_BDIAGONAL);
			solidrectangle(0, y * UNIT, WIDTH * UNIT, (y + 1) * UNIT);
			setfillstyle(BS_SOLID);
		}
	}
	if (flag) {	
		p1.plus_score(combo);
		Sleep(250);
		IMAGE img;
		for (int i = 0; i < 4; i++) {
			if (line[i]) {	//������Ҫ���������ӵ�ǰ����һ�п�ʼ������һ�б�ɸ��еı�־������ո���
				for (int y = now_block.y + i - 1; y > 0; y--) {
					for (int x = 0; x < WIDTH; x++) {
						blocks_maps[x][y + 1] = blocks_maps[x][y];
						blocks_maps[x][y] = 0;
					}
				}
				getimage(&img, 0, 0, WIDTH * UNIT, (now_block.y + i) * UNIT);
				putimage(0, UNIT, &img);
			}
		}
	}
	p1.update_score();
	//�����·���
	New_Block();
}