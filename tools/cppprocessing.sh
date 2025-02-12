#!/bin/bash

if [ -z "$1" ]; then
	echo ""
	echo "Error: No classname specified"
	echo ""
	echo "Usage: namesegment(-namesegment)*"
	echo "  Name segments must be separated with dashes '-'"
	echo "  Ending 'ing' is added automatically to classname"
	echo ""
	echo "Examples"
	echo ""
	echo "Input:"
	echo "cppclass.sh eat"
	echo ""
	echo "Result:"
	echo "Eating.cpp"
	echo "Eating.h"
	echo ""
	echo "Input:"
	echo "cppclass.sh banana-eat"
	echo ""
	echo "Result:"
	echo "BananaEating.cpp"
	echo "BananaEating.h"
	echo ""
	exit 1
fi

# Parameters
inputname=$(echo $1 | tr '[:upper:]' '[:lower:]')
classname=$(echo "$inputname" | sed -e "s:\b\(.\):\u\1:g" -e "s:-\| ::g")
classname="${classname}ing"
inputname="${inputname}ing"
headerdef=$(echo "${inputname^^}" | sed -e "s:-:_:g")
cppfilename=$classname.cpp
hppfilename=$classname.h
thedate=$(date +%d.%m.%Y)
theyear=$(date +%Y)

# CPP file
cat > $cppfilename << EOF
/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on ${thedate}

  Copyright (C) ${theyear}-now Authors and www.dsp-crowd.com

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

#include "$hppfilename"

using namespace std;

#define LOG_LVL	0

${classname}::${classname}()
	: Processing("${classname}")
{}

/* member functions */
Success ${classname}::initialize()
{
	return Positive;
}

Success ${classname}::process()
{
	return Pending;
}

Success ${classname}::shutdown()
{
	return Positive;
}

void ${classname}::processInfo(char *pBuf, char *pBufEnd)
{
	(void)pBuf;
	(void)pBufEnd;
}

/* static functions */

EOF

# Header file
cat > $hppfilename << EOF
/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on ${thedate}

  Copyright (C) ${theyear}-now Authors and www.dsp-crowd.com

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

#ifndef ${headerdef}_H
#define ${headerdef}_H

#include "Processing.h"

class ${classname} : public Processing
{

public:

	static ${classname} *create()
	{
		return new (std::nothrow) ${classname};
	}

protected:

	${classname}();
	virtual ~${classname}() {}

private:

	${classname}(const ${classname} &) : Processing("") {}
	${classname} &operator=(const ${classname} &) { return *this; }

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

	/* static functions */

	/* static variables */

	/* constants */

};

#endif

EOF

# Style
astyle --suffix=none --style=linux --indent=force-tab=4 ${cppfilename} ${hppfilename} &> /dev/null

# Debugging
cat ${cppfilename}
cat ${hppfilename}
