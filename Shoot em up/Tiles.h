#pragma once
#include "template.h"
#include "surface.h"
#include "FreeImage.h"
#include <vector>

namespace Tmpl8
{
	class Tiles
	{
	public:
		Tiles(void);				//Constructor
		Tiles(Surface*tempTile,int x,int y);
		~Tiles(void);				//Destructor
		void CopyTo(Surface* a_Dst, Surface* a_Src, int a_X, int a_Y );

		Surface* tile;
		int xPos;
		int yPos;
	private:

	};
}

