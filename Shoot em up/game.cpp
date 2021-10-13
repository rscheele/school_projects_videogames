// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009
#include "game.h"

using namespace Tmpl8;

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_SPACE 57

Surface* explosionImage = new Surface("assets/explosion.png");
Surface* playerImage = new Surface("assets/player.png");
Surface* playerBullet = new Surface("assets/bulletgreen.png");
Surface* enemyBullet = new Surface("assets/bulletred.png");

Sprite player(playerImage,1);
Explosion xplosie;
Playerbullet bullet;
Aliens attacker[3];
Enemybullet ebullet[20];
Towerbullet tbullet[20];

//global variables
float xscreen = 0.0;
float yscreen = 0.0;
float delay = 500.0;
float delay2 = 100.0;

void Game::Init()
{
	score = 0;
	xplosie.Graphic = explosionImage;
	bullet.Graphic = playerBullet;
	bulletactive = false;
	//player values
	rotation = 0.0;
	lives = 3;
	alive = true;
	//setting keys to false
	keyleft = false; keyup = false; keydown = false; keyright = false; keyspace = false;
	//static enemy creation
	m_Turret = new Enemyturret();
	// tile creation
	imagedata = new Surface("assets/tileset.png");
	for (int y = 0; y<8;y++)
		for(int x = 0; x<4;x++)
		{
			Surface* tempTile = new Surface(32,32);
			Tiles* tile = new Tiles(tempTile,x*32,y*32);
			tile->CopyTo(tempTile,imagedata,x*32,y*32);
			tiles.push_back(tile);
		}
	for (int i = 0; i < 20; i++)
	{
		tbullet[i].Graphic = enemyBullet;
		tbullet[i].active = false;
		ebullet[i].Graphic = enemyBullet;
		ebullet[i].active = false;
		delay = 100.0;
	}
	respawntimer = 20.0;
}




void Game::Tick( float a_DT )
{
	for (int i = 0; i <20 ; i++) 
		m_Screen->Clear( 0 );  
	//Tile drawning
	//Tile numbers;
	//Colision walls = 6, 9, 11, 14
	//Corners = 5, 7, 13, 15
	//Background = 0
	// TILE DRAWING:
	//background
	for(int i =0; i< tiles.size();i++)
	{
		for (float y = 0.0; y < 60.0; y++)
			for (float x = 0.0; x < 70.0; x++)
				if (x*32.0 +80.0 >= xscreen && x*32.0 <= xscreen +640.0 && y*32.0 +80.0 >= yscreen && y*32.0 <= yscreen + 480.0)
				tiles[0]->tile->CopyTo(m_Screen,(32.0+x*32.0)-xscreen,(32.0+y*32.0)-yscreen);
		//bushes
		for (float y = 0.0; y < 4.0; y++)
			for (float x = 0.0; x < 4.0; x++)
			{
				if (x*640.0 +200.0 >= xscreen && x*640.0 <= xscreen +640.0 && y*580.0 + 200.0 >= yscreen && y*580.0 <= yscreen + 480.0)
					tiles[4]->tile->CopyTo(m_Screen,(140.0+x*640.0+x)-xscreen,(80.0+y*580.0)-yscreen);
				if (x*580.0 +200.0 >= xscreen && x*580.0 <= xscreen +640.0 && y*460.0 + 200.0 >= yscreen && y*460.0 <= yscreen + 480.0)
					tiles[2]->tile->CopyTo(m_Screen,(100.0+x*580.0+x)-xscreen,(140.0+y*460.0)-yscreen);
			}
		//walls y
		for (float y = 0.0; y < 60.0; y++)
			if (y*32 +80 >= yscreen && y*32 <= yscreen + 480)
			{
			tiles[9]->tile->CopyTo(m_Screen,0-xscreen,(y*32)-yscreen);
			tiles[11]->tile->CopyTo(m_Screen,2272-xscreen,(y*32)-yscreen);
			}
		//walls x
		for (float x =0; x < 70; x++)
			if (x*32 +80 >= xscreen && x*32 <= xscreen +640)
			{
			tiles[6]->tile->CopyTo(m_Screen,(x*32+32)-xscreen,0-yscreen);
			tiles[14]->tile->CopyTo(m_Screen,(x*32+32)-xscreen,1920-yscreen);
			}
		// corners
		tiles[5]->tile->CopyTo(m_Screen,0-xscreen,0-yscreen);
		tiles[7]->tile->CopyTo(m_Screen,2272-xscreen,0-yscreen);
		tiles[13]->tile->CopyTo(m_Screen,0-xscreen,1920-yscreen);
		tiles[15]->tile->CopyTo(m_Screen,2272-xscreen,1920-yscreen);
		//wreckages
		tiles[18]->tile->CopyTo(m_Screen,640-xscreen,640-yscreen);
		tiles[19]->tile->CopyTo(m_Screen,672-xscreen,640-yscreen);
		tiles[22]->tile->CopyTo(m_Screen,640-xscreen,672-yscreen);
		tiles[23]->tile->CopyTo(m_Screen,670-xscreen,672-yscreen);
		tiles[16]->tile->CopyTo(m_Screen,1032-xscreen,1032-yscreen);
		tiles[17]->tile->CopyTo(m_Screen,1064-xscreen,1032-yscreen);
		tiles[20]->tile->CopyTo(m_Screen,1032-xscreen,1064-yscreen);
		tiles[21]->tile->CopyTo(m_Screen,1064-xscreen,1064-yscreen);
	}
	for (int i = 0; i < 20; i++)
		ebullet[i].Tick(a_DT, this);
	for (int i = 0; i < 20; i++)
		tbullet[i].Tick(a_DT, this);
	m_Turret->Draw(m_Screen); //static enemy
	//everything related to death
	if (alive == false && respawntimer <= 3.0 && respawntimer>= 0.0 && lives >= 1)
	{
		yscreen = 0.0; 
		xscreen = 0.0;
		alive = true;
	}
	//delay for enenmy shooting
	if (delay >= 1.0)
		delay = delay - 1;
	if (delay <= 0.0)
		delay = 100.0;
	if (delay2 >= 1.0)
		delay2 = delay2 - 1;
	if (delay2 <= 0.0)
		delay2 = 100.0;
	// explosion
	if (alive == false)
	{
		attacker[0].alive = false;
		attacker[1].alive = false;
		attacker[2].alive = false;
		xplosie.Graphic->CopyTo(m_Screen,260,200);
		if (respawntimer >= -1.0)
			respawntimer = respawntimer - 1.0;
	}
	//calculating bullet direction
	if (bulletactive == false)
	{
		bullet.xdir = cos((-rotation+90)/180*PI)*30;
		bullet.ydir = sin((rotation-90)/180*PI)*30;
		bullet.xmove = 0.0;
		bullet.ymove = 0.0;
	}
	//shooting
	if (keyspace == true)
	{
		if (bulletactive == false && alive == true)
		{
			bullet.xscreenpos = xscreen+260;
			bullet.yscreenpos = yscreen+200;
			bullet.xmove = bullet.xscreenpos;
			bullet.ymove = bullet.yscreenpos;
		}
		bulletactive = true;
	}
	if (bulletactive == true)
	{
		bullet.xmove = bullet.xmove + bullet.xdir;
		bullet.ymove = bullet.ymove + bullet.ydir;
		bullet.Graphic->CopyTo(m_Screen,bullet.xmove-xscreen,bullet.ymove-yscreen);
	}
	if (bullet.xmove - xscreen >= 640 | bullet.xmove - xscreen <= 0 | bullet.ymove - yscreen <= 0| bullet.ymove - yscreen >= 480)
		bulletactive = false;
	//score, lives, printing to screen
	m_Screen->Print("Lives left = ",10,10,0x7599e3);
	char liv[10];
	sprintf(liv,"%i",lives);
	m_Screen->Print(liv,90,10,0x7599e3);
	m_Screen->Print("Score = ",150,10,0x7599e3);
	char sco[5000];
	sprintf(sco,"%i",score);
	m_Screen->Print(sco,200,10,0x7599e3);
	if (lives == 0)
		m_Screen->Print("Game over!",300,300,0x7599e3);
	//player lives
	if (lives >= 1 && alive == true)
	{
	player.DrawRotated(288,220,m_Screen,rotation);
	//reseting rotation 360 scale
	if (rotation > 360.0)
		rotation = 0.0;
	if (rotation <0.0)
		rotation = 359.0;
	//colision events
	for (int i = 0; i < 20; i++)
		if (tbullet[i].xPos()-xscreen >= 254 && tbullet[i].xPos()-xscreen <= 320 && tbullet[i].yPos()-yscreen >= 198 && tbullet[i].yPos()-yscreen <= 242 && alive == true)
		{
			lives = lives-1;
			alive = false; 
			respawntimer = 100;
		}
	for (int i = 0; i < 20; i++)
		if (ebullet[i].xPos()-xscreen >= 254 && ebullet[i].xPos()-xscreen <= 320 && ebullet[i].yPos()-yscreen >= 198 && ebullet[i].yPos()-yscreen <= 242 && alive == true)
		{
			lives = lives-1;
			alive = false; 
			respawntimer = 100;
		}
	//player-corner walls
	if ((xscreen <= -270 | yscreen <= -200 | xscreen >= 1980 | yscreen >= 1700) && alive == true)
	{
		alive = false;
		lives = lives-1;
		respawntimer = 100.0;
	}
	//bullets kill
	if (bullet.xmove >= attacker[0].Xpos() && bullet.xmove <= attacker[0].Xpos() + 80 && bullet.ymove >= attacker[0].Ypos() && bullet.ymove <= attacker[0].Ypos() + 50)
	{
		attacker[0].alive = false; 
		bulletactive = false;
		score = score + 25;
	}
	if (bullet.xmove >= attacker[1].Xpos() && bullet.xmove <= attacker[1].Xpos() +80 && bullet.ymove >= attacker[1].Ypos() && bullet.ymove <= attacker[1].Ypos() + 50)
	{
		bulletactive = false;
		attacker[1].alive = false;
		score = score + 25;
	}
	if (bullet.xmove >= attacker[2].Xpos() && bullet.xmove <= attacker[2].Xpos() + 80 && bullet.ymove >= attacker[2].Ypos() && bullet.ymove <= attacker[2].Ypos() + 50)
	{
		bulletactive = false;
		attacker[2].alive = false;
		score = score + 25;
	}
	if (bullet.xmove >= 900.0  && bullet.xmove <= 950.0  && bullet.ymove >= 750 && bullet.ymove <= 878)
	{
		bulletactive = false;
		score = score + 10;
	}
	//attacker
	for (int i = 0; i < 3; i++)
	{
		attacker[i].Tick(a_DT);
		if (attacker[i].alive == true)
			if (attacker[i].Xpos() >= xscreen -200 && attacker[i].Xpos() <= xscreen +640.0 && attacker[i].Ypos() >= attacker[i].Ypos() <= yscreen + 480.0)
				attacker[i].Graphic->CopyTo(m_Screen,attacker[i].Xpos()-xscreen,attacker[i].Ypos()-yscreen);
	}
	//single key movement
	if ((keyleft&&!keyright&&!keyup&&!keydown)|(keyleft&&!keyright&&keyup&&keydown))
	{
		xscreen = xscreen-0.2*a_DT;
		if (rotation < 269.9 && rotation >= 90.0)
		rotation = rotation + 10.0;
		if (rotation > 270.1 | rotation < 90.0)
		rotation = rotation - 10.0;
	}
	if ((keyright&&!keyleft&&!keyup&&!keydown)|(!keyleft&&keyright&&keyup&&keydown))
	{
		xscreen = xscreen+0.2*a_DT;
		if (rotation < 89.9 | rotation > 270.0)
		rotation = rotation + 10.0;
		if (rotation > 90.1 && rotation <= 270.0)
		rotation = rotation - 10.0;
	}
	if ((keyup&&!keydown&&!keyleft&&!keyright)|(keyleft&&keyright&&keyup&&!keydown))
	{
		yscreen = yscreen-0.2*a_DT;
		if (rotation > 0.1 && rotation <= 180.0)
		rotation = rotation - 10.0;
		if (rotation < 359.9 && rotation > 180.0)
		rotation = rotation + 10.0;
	}
	if ((keydown&&!keyup&&!keyleft&&!keyright)|(keyleft&&keyright&&!keyup&&keydown))
	{
		yscreen = yscreen+0.2*a_DT;
		if (rotation >= 0 && rotation < 179.9)
		rotation = rotation + 10.0;
		if (rotation < 360 && rotation > 180.1)
		rotation = rotation - 10.0;
	}
	//double keys movement
	if (keyleft&&keydown&&!keyright&&!keyup)
	{
		yscreen = yscreen+0.2*a_DT;
		xscreen = xscreen-0.2*a_DT;
		if (rotation >= 45.0 && rotation < 224.9)
		rotation = rotation + 10.0;
		if (rotation < 45.0 | rotation > 225.1)
		rotation = rotation - 10.0;
	}
	if (!keyleft&&keydown&&keyright&&!keyup)
	{
		yscreen = yscreen+0.2*a_DT;
		xscreen = xscreen+0.2*a_DT;
		if (rotation < 124.9 | rotation > 305.0)
		rotation = rotation + 10.0;
		if (rotation > 125.1 && rotation <= 305.0)
		rotation = rotation - 10.0;
	}
	if (!keyleft&&!keydown&&keyright&&keyup)
	{
		yscreen = yscreen-0.2*a_DT;
		xscreen = xscreen+0.2*a_DT;
		if (rotation > 45.1 && rotation <= 225.0)
		rotation = rotation - 10.0;
		if (rotation < 44.9 | rotation > 225.0)
		rotation = rotation + 10.0;
	}
	if (keyleft&&!keydown&&!keyright&&keyup)
	{
		yscreen = yscreen-0.2*a_DT;
		xscreen = xscreen-0.2*a_DT;
		if (rotation < 314.9 && rotation >= 135.0)
		rotation = rotation + 10.0;
		if (rotation > 315.1 | rotation < 135.0)
		rotation = rotation - 10.0;
	}
	}
}
//turret draw
void Enemyturret::Draw(Surface* surface)
{
	Graphic = turretImage;
	a_X = 900.0 - xscreen;
	a_Y = 750.0 - yscreen;
	Graphic->CopyTo(surface,a_X,a_Y);
}

//Pressing keys for movement
void Game::KeyDown(unsigned int code)
{
	switch(code)
	{
	case KEY_UP:
		keyup=true;
		break;
	case KEY_DOWN:
		keydown=true;
		break;
	case KEY_LEFT:
		keyleft=true;
		break;
	case KEY_RIGHT:
		keyright=true;
		break;
	case KEY_SPACE:
		keyspace=true; 
		break;
	}
}
// releasing keys
void Game::KeyUp( unsigned int code )
{
	switch(code)
	{
	case KEY_UP:
		keyup=false;
		break;
	case KEY_DOWN:
		keydown=false;
		break;
	case KEY_LEFT:
		keyleft=false;
		break;
	case KEY_RIGHT:
		keyright=false;
		break;
	case KEY_SPACE:
		keyspace=false; 
		break;
	}
}

void Aliens::Tick(float a_DT)
{
	for (int i = 0; i < 3; i++)
	{
		if (attacker[0].alive == false && attacker[1].alive == false && attacker[2].alive == false && changestate == true)
		{
			state = DEAD;
			deadtimer = 100;
			attacker[i].xTick = 1500.0;
			attacker[i].yTick = 1500.0;
		}
	if (attacker[i].state == DEAD)
	{
		attacker[i].changestate = false;
		attacker[i].deadtimer = attacker[i].deadtimer - 1;
		if (attacker[i].deadtimer <= 10)
		{
			attacker[i].deadtimer = 100;
			attacker[i].alive = true;
			attacker[i].state = MOVEFREE;
		}
	}
	if (attacker[i].state == CALCULATE)
	{
		attacker[i].Xvel = (xscreen+220-attacker[i].xPos)/100;
		attacker[i].Yvel = (yscreen+220-attacker[i].yPos)/100;
		if (delay <= 10)
		{
			for (int i = 0; i < 20; i++)
				if (ebullet[i].active == false && attacker[i].alive == true)
				{
					ebullet[i].active = true;
					ebullet[i].calculate = true;
					delay = 100.0;
					break;
				}
		}
		attacker[i].state = MOVETOPLAYER;
	}
	if (attacker[i].state == MOVETOPLAYER)
	{
		attacker[i].yTick += attacker[i].Yvel;
		attacker[i].xTick += attacker[i].Xvel;
		if (attacker[i].yPos <= yscreen+740 && attacker[i].yPos >= yscreen-80 && attacker[i].xPos <= xscreen+580 && attacker[i].xPos >= xscreen-80)
			attacker[i].state = CALCULATE;
		else
			attacker[i].state = MOVEFREE;
	}
	if (attacker[i].state == MOVEFREE)
	{
		if (attacker[i].yPos  > 900.0 )
			attacker[i].state = MOVEUP;
		if (attacker[i].yPos  <= 900.0 )
			attacker[i].state = MOVEDOWN;
		if (attacker[i].xPos  < 1100.0 )
			attacker[i].state = MOVERIGHT;
		if (attacker[i].xPos  >= 1100.0 )
			attacker[i].state = MOVELEFT;
		if (attacker[i].yPos <= yscreen+680 && attacker[i].yPos >= yscreen-20 && attacker[i].xPos <= xscreen+520 && attacker[i].xPos >= xscreen-20)
			attacker[i].state = CALCULATE;
	}
	if (attacker[i].state == MOVEUP)
	{
		attacker[i].yTick=attacker[i].yTick-5;
		attacker[i].xTick = attacker[i].xTick;
		if (attacker[i].yPos <= 500)
			attacker[i].state = MOVELEFT;
		if (attacker[i].yPos <= yscreen+680 && attacker[i].yPos >= yscreen-20 && attacker[i].xPos <= xscreen+520 && attacker[i].xPos >= xscreen-20)
			attacker[i].state = CALCULATE;
	}
	if (attacker[i].state == MOVELEFT)
	{
		attacker[i].xTick=attacker[i].xTick-5;
		attacker[i].yTick = attacker[i].yTick;
		if (attacker[i].xPos <= 500)
			attacker[i].state = MOVEDOWN;
		if (attacker[i].yPos <= yscreen+680 && attacker[i].yPos >= yscreen-20 && attacker[i].xPos <= xscreen+520 && attacker[i].xPos >= xscreen-20)
			attacker[i].state = CALCULATE;
	}
	if (attacker[i].state == MOVEDOWN)
	{
		attacker[i].yTick=attacker[i].yTick+5;
		attacker[i].xTick = attacker[i].xTick;
		if (attacker[i].yPos >= 1500)
			attacker[i].state = MOVERIGHT;
		if (attacker[i].yPos <= yscreen+680 && attacker[i].yPos >= yscreen-20 && attacker[i].xPos <= xscreen+520 && attacker[i].xPos >= xscreen-20)
			attacker[i].state = CALCULATE;
	}
	if (attacker[i].state == MOVERIGHT)
	{
		attacker[i].xTick=attacker[i].xTick+5;
		attacker[i].yTick = attacker[i].yTick;
		if (attacker[i].xPos >= 1800)
			attacker[i].state = MOVEUP;
		if (attacker[i].yPos <= yscreen+680 && attacker[i].yPos >= yscreen-20 && attacker[i].xPos <= xscreen+520 && attacker[i].xPos >= xscreen-20)
			attacker[i].state = CALCULATE;
	}
}
}

int Aliens::Xpos()
{
	attacker[0].xPos = attacker[0].xTick;
	attacker[1].xPos = attacker[1].xTick+75;
	attacker[2].xPos = attacker[2].xTick+150;
	for (int i = 0; i < 3; i++)
		return attacker[i].xPos;
}

int Aliens::Ypos()
{
	yPos = yTick;
	return yPos;
}

void Enemybullet::Tick(float a_DT, Game* game)
{
	if (active == true && calculate == true)
	{
		for (int k = 0; k < 3; k++)
		{
			xpos = attacker[k].Xpos();
			ypos = attacker[k].Ypos();
		}
		xvel = (xscreen+220-xpos)*a_DT/1000;
		yvel = (yscreen+220-ypos)*a_DT/1000;
		calculate = false;
	}

	if (active == true)
		Graphic->CopyTo(game->m_Screen,xPos()-xscreen,yPos()-yscreen);

	if (xPos() <= xscreen | xPos () >= xscreen + 640 | yPos() <= yscreen | yPos() >= yscreen + 480)
		active = false;
}

int Enemybullet::xPos()
{
	xpos += xvel;
	return xpos;
}

int Enemybullet::yPos()
{
	ypos += yvel;
	return ypos;
}

void Towerbullet::Tick(float a_DT, Game* game)
{
	if (xscreen >= 260 && xscreen <= 1000 && yscreen >= 280 && yscreen <= 900)
		if (delay2 <= 10)
			for (int i = 0; i < 20; i++)
				if (tbullet[i].active == false)
				{
					tbullet[i].active = true;
					tbullet[i].calculate = true;
					delay2 = 50.0;
					break;
				}
	if (active == true && calculate == true)
	{
		xpos = 900.0 ;
		ypos = 750.0 ;
		xvel = (xscreen+220-xpos)/40;
		yvel = (yscreen+220-ypos)/40;
		calculate = false;
				//printf("plop");
	}

	if (active == true && calculate == false)
		Graphic->CopyTo(game->m_Screen,xPos()-xscreen,yPos()-yscreen);

	if (xPos() <= xscreen | xPos() >= xscreen + 640 | yPos() <= yscreen-100 | yPos() >= yscreen + 480)
		active = false;
}

int Towerbullet::xPos()
{
	xpos = xpos + xvel;
	return xpos;
}

int Towerbullet::yPos()
{
	ypos = ypos + yvel;
	return ypos;
}