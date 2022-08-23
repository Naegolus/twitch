/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on 17.08.2022

  Copyright (C) 2022 Authors and www.dsp-crowd.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "GameServing.h"
#include "Gaming.h"
#include "TicTacToeGaming.h"
#include "ConnectFourGaming.h"

using namespace std;

#define LOG_LVL	0

typedef list<GamerInteracting *>::iterator GamerIter;

GameServing::GameServing()
	: Processing("GameServing")
	, mpLst(NULL)
{}

/* member functions */
Success GameServing::initialize()
{
	dGameRegister(TicTacToe);
	dGameRegister(ConnectFour);
	// dGameRegister(Battleship);

	mpLst = TcpListening::create();
	mpLst->portSet(4000);
	mpLst->procTreeDisplaySet(true);
	start(mpLst);

	return Positive;
}

Success GameServing::process()
{
	gamerListUpdate();

	return Pending;
}

void GameServing::gamerListUpdate()
{
	gamerRemove();
	gamerAdd();
}

void GameServing::gamerRemove()
{
	GamerIter iter;
	GamerInteracting *pGamer;

	iter = GamerInteracting::gamerList.begin();
	while (iter != GamerInteracting::gamerList.end())
	{
		pGamer = *iter;

		if (pGamer->success() == Pending)
		{
			++iter;
			continue;
		}

		procDbgLog(LOG_LVL, "removing gamer. process: %p", pGamer);
		repel(pGamer);

		iter = GamerInteracting::gamerList.erase(iter);
	}
}

void GameServing::gamerAdd()
{
	PipeEntry<int> peerFdEntry;
	int peerFd;
	GamerInteracting *pGamer = NULL;

	while (1)
	{
		if (!mpLst->ppPeerFd.get(peerFdEntry))
			break;

		peerFd = peerFdEntry.particle;

		pGamer = GamerInteracting::create(peerFd);
		start(pGamer);

		procDbgLog(LOG_LVL, "adding gamer. process: %p", pGamer);

		GamerInteracting::gamerList.push_back(pGamer);
	}
}

void GameServing::processInfo(char *pBuf, char *pBufEnd)
{
	dInfo("Gamers\t\t\t%ld", GamerInteracting::gamerList.size());
}

/* static functions */

