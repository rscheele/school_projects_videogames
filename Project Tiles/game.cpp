// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009
#include "game.h"

using namespace Tmpl8;

void Game::Init()
{
	imagedata = new Surface("assets/tiles.png");

	for (int y = 0; y<10;y++)
	{
		for(int x = 0; x<20;x++)
		{
			Surface* tempTile = new Surface(32,32);
			CopyTo(tempTile,imagedata,x*32,y*32);

			Tiles* tilez = new Tiles(tempTile,x*32,y*32);
			tiles.push_back(tilez);
		}
	}
}

void Game::CopyTo( Surface* a_Dst,Surface* a_Src, int a_X, int a_Y )
{
	Pixel* src = a_Src->GetBuffer()+(a_Y * a_Src->GetPitch() + a_X);
	Pixel* dst = a_Dst->GetBuffer();
	if ((src) && (dst)) 
	{
		int srcwidth = 32;
		int srcheight = 32;

		int srcpitch = a_Src->GetPitch();
		int dstwidth = a_Dst->GetWidth();

		int dstheight = a_Dst->GetHeight();
		int dstpitch = a_Dst->GetPitch();
		//dst += a_X + dstpitch * a_Y ;
		for ( int y = 0; y < srcheight; y++ )
		{
			memcpy( dst, src, srcwidth * sizeof(Pixel) );
			dst += dstpitch;
			src += srcpitch;
		}
	}
}

void Game::Tick( float a_DT )
{
	for (int i = 0; i <20 ; i++) 
		m_Screen->Clear( 0 );  

	for(int i =0; i< tiles.size();i++)
	{
		tiles[i]->tile->CopyTo(m_Screen,tiles[i]->xPos,tiles[i]->yPos);
	}
	
}




