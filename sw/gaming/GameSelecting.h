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

#ifndef GAME_SELECTING_H
#define GAME_SELECTING_H

#include <vector>

#include "Processing.h"
#include "LibGame.h"

#define dForEach_GsState(gen) \
		gen(GsStart) \
		gen(GsGamesListRead) \
		gen(GsGamesList) \
		gen(GsTypesList) \

#define dGenGsStateEnum(s) s,
dProcessStateEnum(GsState);

struct GameListElem
{
	std::string name;
	std::string type;
};

class GameSelecting : public Processing
{

public:

	static GameSelecting *create(TcpTransfering *pConn)
	{
		return new (std::nothrow) GameSelecting(pConn);
	}

	bool aborted;

protected:

	GameSelecting(TcpTransfering *pConn);
	virtual ~GameSelecting() {}

private:

	GameSelecting() : Processing("") {}
	GameSelecting(const GameSelecting &) : Processing("") {}
	GameSelecting &operator=(const GameSelecting &) { return *this; }

	/*
	 * Naming of functions:  objectVerb()
	 * Example:              peerAdd()
	 */

	/* member functions */
	Success initialize();
	Success process();
	void processInfo(char *pBuf, char *pBufEnd);

	void msgGamesList(std::string &msg);
	void msgTypesList(std::string &msg);

	/* member variables */
	enum GsState mState;
	std::vector<struct GameListElem> mGamesList;
	TcpTransfering *mpConn;
	uint32_t mKeyLastGotMs;
	uint32_t mNumGames;
	uint32_t mNumGamers;

	uint32_t mOffCursor;
	uint32_t mOffGames;

	/* static functions */

	/* static variables */

	/* constants */

};

#endif

