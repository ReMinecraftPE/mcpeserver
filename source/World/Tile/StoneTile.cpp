/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "Tile.hpp"
#include "Level.hpp"

StoneTile::StoneTile(int a, int b, Material* c) : Tile(a, b, c)
{
}

int StoneTile::getResource(int a, Random* b)
{
	return Tile::stoneBrick->m_ID;
}
