/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/
#include "Server.hpp"
#include "Tile.hpp"
#include "Item.hpp"
#include "ServerSideNetworkHandler.hpp"

int main()
{
	LogMsg("Minecraft PE Server - Copyright (C) 2023 iProgramInCpp");

	LogMsg("Initializing databases...");
	Mth::initMth();
	Material::initMaterials();
	Tile::initTiles();
	Item::initItems();
	Biome::initBiomes();

	LogMsg("Starting server...");
	Server server;
	server.start();
	server.generateLevel();
	server.host();
	return 0;
}
