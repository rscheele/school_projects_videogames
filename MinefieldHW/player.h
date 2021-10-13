#pragma once

namespace Tmpl8 {

class Surface;

class player
{
public:
	player(void);
	~player(void);
	void Move(int x, int y);
private:
	Surface* m_Screen;
	int xPos;
	int yPos;
};

};