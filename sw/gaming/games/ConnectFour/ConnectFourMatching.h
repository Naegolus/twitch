/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on 23.08.2022

  Copyright (C) 2022-now Authors and www.dsp-crowd.com

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

#ifndef CONNECT_FOUR_MATCHING_H
#define CONNECT_FOUR_MATCHING_H

#include <jsoncpp/json/json.h>

#include "Processing.h"
#include "Pipe.h"

#define dForEach_CfMatchState(gen) \
		gen(CfMatchInit) \
		gen(CfMatchBeginShow) \
		gen(CfMatchRoundStart) \
		gen(CfMatchRoundDoneWait) \
		gen(CfMatchStatsShow) \

#define dGenCfMatchStateEnum(s) s,
dProcessStateEnum(CfMatchState);

class ConnectFourMatching : public Processing
{

public:

	static ConnectFourMatching *create()
	{
		return new (std::nothrow) ConnectFourMatching;
	}

	Pipe<Json::Value> *pIn;
	Pipe<Json::Value> *pOut;
	Json::Value *pGs;

protected:

	ConnectFourMatching();
	virtual ~ConnectFourMatching() {}

private:

	ConnectFourMatching(const ConnectFourMatching &) : Processing("") {}
	ConnectFourMatching &operator=(const ConnectFourMatching &) { return *this; }

	/*
	 * Naming of functions:  objectVerb()
	 * Example:              peerAdd()
	 */

	/* member functions */
	Success initialize();
	Success process();
	Success shutdown();
	void processInfo(char *pBuf, char *pBufEnd);

	/* member variables */
	enum CfMatchState mState;

	/* static functions */

	/* static variables */

	/* constants */

};

#endif

