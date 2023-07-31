#include "Server.hpp"
#include "MemoryLevelStorage.hpp"

Server::Server()
{
	m_pDimension = Dimension::getNew(0);
	m_pLevelStorage = new MemoryLevelStorage;
	m_pLevel = new Level(m_pLevelStorage, "Level", 123456, 1, m_pDimension);
	m_pRakNetInstance = new RakNetInstance;
	m_pSSNH = new ServerSideNetworkHandler(this, m_pRakNetInstance);
}

Server::~Server()
{
	delete m_pSSNH;
	delete m_pLevel;
	delete m_pLevelStorage;
	// don't delete the m_pDimension- it's deleted by the level automatically
	delete m_pRakNetInstance;
}

Level* Server::getLevel()
{
	return m_pLevel;
}

RakNetInstance* Server::getRakNetInstance()
{
	return m_pRakNetInstance;
}

Options* Server::getOptions()
{
	return &m_Options;
}

void Server::start()
{
	m_pRakNetInstance->host("name", C_DEFAULT_PORT, C_MAX_CONNECTIONS);
}

void Server::generateLevel()
{
	LogMsg("Building terrain");

	float startTime = getTimeS();
	Level* pLevel = m_pLevel;

	if (!pLevel->field_B0C)
	{
		pLevel->setUpdateLights(0);
	}

	for (int i = 8, i2 = 0; i != 8 + C_MAX_CHUNKS_X * 16; i += 16)
	{
		for (int j = 8; j != 8 + C_MAX_CHUNKS_Z * 16; j += 16, i2 += 100)
		{
			// this looks like some kind of progress tracking
			//m_progressPercent = i2 / (C_MAX_CHUNKS_X * C_MAX_CHUNKS_Z);

			float time1 = getTimeS();

			// generating all the chunks at once
			TileID unused = m_pLevel->getTile(i, (C_MAX_Y + C_MIN_Y) / 2, j);

			if (time1 != -1.0f)
				getTimeS();

			float time2 = getTimeS();
			if (m_pLevel->field_B0C)
			{
				while (m_pLevel->updateLights());
			}

			if (time2 != -1.0f)
				getTimeS();
		}
	}

	if (startTime != -1.0f)
		getTimeS();

	m_pLevel->setUpdateLights(1);

	startTime = getTimeS();

	for (int x = 0; x < C_MAX_CHUNKS_X; x++)
	{
		for (int z = 0; z < C_MAX_CHUNKS_Z; z++)
		{
			LevelChunk* pChunk = m_pLevel->getChunk(x, z);
			if (!pChunk)
				continue;

			if (pChunk->field_237)
				continue;

			pChunk->m_bUnsaved = false;
			pChunk->clearUpdateMap();
		}
	}

	if (startTime != -1.0f)
		getTimeS();

	LogMsg("Saving chunks");

	if (m_pLevel->field_B0C)
	{
		m_pLevel->setInitialSpawn();
		m_pLevel->saveLevelData();
		m_pLevel->getChunkSource()->saveAll();
	}
	else
	{
		m_pLevel->saveLevelData();
	}

	LogMsg("Preparing");

	startTime = getTimeS();

	m_pLevel->prepare();

	m_pSSNH->levelGenerated(m_pLevel);
}

void Server::tick()
{
	m_pLevel->tickEntities();
	m_pLevel->tick();
}

void Server::host()
{
	m_pSSNH->allowIncomingConnections(true);
	LogMsg("Server is ready!");

	while (true)
	{
		m_pRakNetInstance->runEvents(m_pSSNH);

		// tick
		m_tickTimer.advanceTime();

		for (int i = 0; i < m_tickTimer.field_14; i++)
		{
			tick();
		}

		sleepMs(1);
	}
}


