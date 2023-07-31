#pragma once

#include "Level.hpp"
#include "RakNetInstance.hpp"
#include "Options.hpp"
#include "ServerSideNetworkHandler.hpp"
#include "Timer.hpp"

class Server
{
public:
	Server();
	~Server();

	Level* getLevel();
	RakNetInstance* getRakNetInstance();
	Options* getOptions();

	void start();
	void generateLevel();
	void tick();
	void host();

private:
	ServerSideNetworkHandler* m_pSSNH;
	LevelStorage* m_pLevelStorage;
	Dimension* m_pDimension;
	Level* m_pLevel;
	RakNetInstance* m_pRakNetInstance;
	Options m_Options;
	Timer m_tickTimer;
};

