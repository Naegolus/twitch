/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on 20.08.2022

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

#include "GameSelecting.h"
#include "Gaming.h"

#if 1
#define dGenGsStateString(s) #s,
dProcessStateStr(GsState);
#endif

using namespace std;

#define LOG_LVL	0

GameSelecting::GameSelecting(TcpTransfering *pConn)
	: Processing("GameSelecting")
	, mState(GsStart)
	, mpConn(pConn)
	, mKeyLastGotMs(0)
	, mNumGames(0)
{}

/* member functions */
Success GameSelecting::initialize()
{
	return Positive;
}

Success GameSelecting::process()
{
	string msg = "";
	uint8_t key;

	switch (mState)
	{
	case GsStart:

		mState = GsGamesListRead;

		break;
	case GsGamesListRead:

		procInfLog("Getting server list");

		mGamesList.clear();

		{
			lock_guard<mutex> lock(Gaming::mtxGamesList);
			list<Gaming *>::iterator iter;
			Gaming *pGaming = NULL;
			int i = 0;

			mNumGames = Gaming::gamesList.size();
			mGamesList.reserve(mNumGames);

			for (iter = Gaming::gamesList.begin(); iter != Gaming::gamesList.end(); ++iter, ++i)
			{
				pGaming = *iter;

				mGamesList[i].name = pGaming->mGameName;
				mGamesList[i].type = pGaming->mType;
			}
		}

		procInfLog("Got server list");

		msgGamesList(msg);
		mState = GsIdle;

		break;
	case GsIdle:

		key = keyGet(mpConn, mKeyLastGotMs);

		if (!key)
			break;

		if (key == keyEsc)
			return Positive;

		break;
	default:
		break;
	}

	if (!msg.size())
		return Pending;

	mpConn->send(msg.c_str(), msg.size());

	return Pending;
}

void GameSelecting::msgGamesList(string &msg)
{
	msg = "\033[2J\033[H";
	msg += "\r\n";
	msg += "Games " + to_string(mNumGames);
	msg += "\r\n";
	msg += "\r\n";
	msg += "[k]\tUp";
	msg += "\r\n";
	msg += "[j]\tDown";
	msg += "\r\n";
	msg += "[esc]\tQuit";
	msg += "\r\n";
}

void GameSelecting::processInfo(char *pBuf, char *pBufEnd)
{
#if 1
	dInfo("State\t\t\t%s\n", GsStateString[mState]);
#endif
}

/* static functions */

