/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on 21.05.2019

  Copyright (C) 2019-now Authors and www.dsp-crowd.com

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <unistd.h>

#include "TcpTransfering.h"
#include "LibTime.h"
#include "LibFilesys.h"

#define dForEach_ProcState(gen) \
		gen(StSrvStart) \
		gen(StSrvArgCheck) \
		gen(StCltStart) \
		gen(StCltArgCheck) \
		gen(StCltConnDoneWait) \
		gen(StConnMain) \
		gen(StTmp) \

#define dGenProcStateEnum(s) s,
dProcessStateEnum(ProcState);

#if 1
#define dGenProcStateString(s) #s,
dProcessStateStr(ProcState);
#endif

using namespace std;

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#define LOG_LVL	0

#define dTmoDefaultConnDoneMs			2000

/*
 * Literature
 * - https://stackoverflow.com/questions/28027937/cross-platform-sockets
 */
TcpTransfering::TcpTransfering(int fd)
	: Transfering("TcpTransfering")
	, mState(StSrvStart)
	, mStartMs(0)
	, mSocketFd(fd)
	, mHostAddrStr("")
	, mErrno(0)
	, mInfoSet(false)
	, mBytesReceived(0)
	, mBytesSent(0)
{
	addrInfoSet();
	mSendReady = true;
}

// strAddrHost can be
// - IPv4
// - IPv6 (TODO)
// - Domain (TODO)
TcpTransfering::TcpTransfering(const string &hostAddr, uint16_t hostPort)
	: Transfering("TcpTransfering")
	, mState(StCltStart)
	, mStartMs(0)
	, mSocketFd(-1)
	, mHostAddrStr(hostAddr)
	, mHostPort(hostPort)
	, mErrno(0)
	, mInfoSet(false)
	, mBytesReceived(0)
	, mBytesSent(0)
{
	mSendReady = false;
}

/*
 * Literature
 * - https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
 * - https://man7.org/linux/man-pages/man3/inet_pton.3.html
 * - https://man7.org/linux/man-pages/man2/socket.2.html
 * - https://man7.org/linux/man-pages/man2/connect.2.html
 */
Success TcpTransfering::process()
{
	uint32_t curTimeMs = millis();
	uint32_t diffMs = curTimeMs - mStartMs;
	Success success;
	int res;
	ssize_t connCheck;
#if 0
	procWrnLog("mState = %s", ProcStateString[mState]);
#endif
	switch (mState)
	{
	case StSrvStart:

		mState = StSrvArgCheck;

		break;
	case StSrvArgCheck:

		if (mSocketFd < 0)
			return procErrLog(-1, "socket file descriptor not set");

		success = socketOptionsSet();
		if (success != Positive)
			return procErrLog(-1, "could not set socket options");

		mState = StConnMain;

		break;
	case StCltStart:

		mState = StCltArgCheck;

		break;
	case StCltArgCheck:

		if (mHostAddrStr == "localhost")
			mHostAddrStr = "127.0.0.1";

		memset(&mHostAddr, 0, sizeof(mHostAddr));

		res = inet_pton(AF_INET, mHostAddrStr.c_str(), &mHostAddr.sin_addr);
		if (res < 1)
			return procErrLog(-1, "invalid argument. Only IPv4 address supported by now. Given: '%s'",
					mHostAddrStr.c_str());

		mSocketFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
		if (mSocketFd < 0)
			return procErrLog(-1, "could not create socket: %s (%d)", strerror(errno), errno);

		mHostAddr.sin_family = AF_INET;
		mHostAddr.sin_port = htons(mHostPort);

		mStartMs = curTimeMs;
		mState = StCltConnDoneWait;

		break;
	case StCltConnDoneWait:

		if (diffMs > dTmoDefaultConnDoneMs)
			return procErrLog(-1, "timeout connecting to host");

		res = connect(mSocketFd, (struct sockaddr *)&mHostAddr, sizeof(mHostAddr));
		if (res < 0 and errno == EINPROGRESS)
			break;

		if (res < 0 and errno == EAGAIN)
			break;

		if (res < 0)
			return procErrLog(-1, "could not connect to host: %s (%d)", strerror(errno), errno);

		success = socketOptionsSet();
		if (success != Positive)
			return procErrLog(-1, "could not set socket options");

		mSendReady = true;

		mState = StConnMain;

		break;
	case StConnMain:

		connCheck = read(NULL, 0);

		if (mDone)
			return Positive;

		if (connCheck >= 0)
			break;

		if (mErrno)
			return procErrLog(-1, "connection error occured: %s (%d)", strerror(mErrno), mErrno);

		return Positive;

		break;
	case StTmp:

		break;
	default:
		break;
	}

	return Pending;
}

Success TcpTransfering::shutdown()
{
	procDbgLog(LOG_LVL, "shutdown");

	Guard lock(mSocketFdMtx);
	disconnect();

	return Positive;
}

/*
Literature socket programming:
- http://man7.org/linux/man-pages/man2/poll.2.html
- http://man7.org/linux/man-pages/man2/recvmsg.2.html
- http://man7.org/linux/man-pages/man2/select.2.html
- http://man7.org/linux/man-pages/man2/read.2.html
- https://linux.die.net/man/2/send
  - Important: MSG_NOSIGNAL
- https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_74/rzab6/poll.htm
- https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-server-code
- https://stackoverflow.com/questions/28027937/cross-platform-sockets
- https://daniel.haxx.se/docs/poll-vs-select.html
- http://deepix.github.io/2016/10/21/tcprst.html
- https://stackoverflow.com/questions/11436013/writing-to-a-closed-local-tcp-socket-not-failing
- https://www.usenix.org/legacy/publications/library/proceedings/usenix99/full_papers/banga/banga_html/node3.html
- https://www.linuxtoday.com/blog/multiplexed-i0-with-poll.html
- https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/poll.h
- https://stackoverflow.com/questions/24791625/how-to-handle-the-linux-socket-revents-pollerr-pollhup-and-pollnval
*/
ssize_t TcpTransfering::read(void *pBuf, size_t lenReq)
{
	Guard lock(mSocketFdMtx);

	if (!mReadReady)
		return 0;

	if (mSocketFd < 0)
		return -1;

	ssize_t numBytes = 0;
	bool peek = false;
	char buf[1];

	if (!pBuf or !lenReq)
	{
		pBuf = buf;
		lenReq = sizeof(buf);
		peek = true;
	}

	numBytes = ::recv(mSocketFd, (char *)pBuf, lenReq, MSG_PEEK);

	if (numBytes < 0)
	{
		if (errno == EAGAIN or errno == EWOULDBLOCK)
			return 0; // std case and ok

		disconnect(errno);

		return procErrLog(-2, "recv() failed: %s", strerror(errno));
	}

	if (!numBytes)
	{
		procDbgLog(LOG_LVL, "connection reset by peer");
		disconnect();
		return -3;
	}

	if (peek)
		return numBytes;

	numBytes = ::recv(mSocketFd, (char *)pBuf, numBytes, 0);
	//procDbgLog(LOG_LVL, "received data. len: %d", numBytes);

	mBytesReceived += numBytes;

	return numBytes;
}

ssize_t TcpTransfering::readFlush()
{
	ssize_t bytesRead = 1, bytesSum = 0;
	char buf[32];

	while (bytesRead)
	{
		bytesRead = read(buf, sizeof(buf));
		bytesSum += bytesRead;
	}

	return bytesSum;
}

ssize_t TcpTransfering::send(const void *pData, size_t lenReq)
{
	if (!mSendReady)
		return procErrLog(-1, "unable to send data. Not ready");

	Guard lock(mSocketFdMtx);

	if (mSocketFd < 0)
		return procErrLog(-1, "socket not set");

	ssize_t res;
	size_t lenBkup = lenReq;
	size_t bytesSent = 0;

	while (lenReq)
	{
		/* IMPORTANT:
		  * Connection may be reset by remote peer already.
		  * Flag MSG_NOSIGNAL prevents function send() to
		  * emit signal SIGPIPE and therefore kill the entire
		  * application in this case.
		  */
		res = ::send(mSocketFd, (const char *)pData, lenReq, MSG_NOSIGNAL);
		if (res < 0)
		{
			disconnect(errno);
			return procErrLog(-1, "connection down: %s", strerror(errno));
		}

		if (!res)
			break;

		pData = ((const uint8_t *)pData) + res;
		lenReq -= res;

		bytesSent += res;
	}

	if (bytesSent != lenBkup)
		procWrnLog("not all data has been sent");

	mBytesSent += bytesSent;

	return bytesSent;
}

void TcpTransfering::disconnect(int err)
{
	//Guard lock(mSocketFdMtx); // every caller must lock in advance!

	if (mSocketFd < 0)
	{
		procDbgLog(LOG_LVL, "socket closed already");
		return;
	}

	procDbgLog(LOG_LVL, "closing socket: %d", mSocketFd);
	mErrno = err;
	::close(mSocketFd);
	mSocketFd = -1;
	procDbgLog(LOG_LVL, "closing socket: %d: done", mSocketFd);
}

Success TcpTransfering::socketOptionsSet()
{
	Guard lock(mSocketFdMtx);

	int opt = 1;
	bool ok;

	addrInfoSet();

	if (::setsockopt(mSocketFd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&opt, sizeof(opt)))
		return procErrLog(-2, "setsockopt(SO_KEEPALIVE) failed: %s", strerror(errno));

	ok = fileNonBlockingSet(mSocketFd);
	if (!ok)
		return procErrLog(-3, "could not set non blocking mode: %s", strerror(errno));

	mReadReady = true;

	return Positive;
}

/* Literature
 * - http://man7.org/linux/man-pages/man2/getsockname.2.html
 * - http://man7.org/linux/man-pages/man2/getpeername.2.html
 * - https://stackoverflow.com/questions/10167540/how-to-get-local-ip-address-and-port-in-unix-socket-programming
 *   - https://beej.us/guide/bgnet/html/multi/getpeernameman.html
 * - http://www.masterraghu.com/subjects/np/introduction/unix_network_programming_v1.3/ch04lev1sec10.html
 * - https://linux.die.net/man/3/inet_ntoa
 *   The inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation.
 *   The string is returned in a statically allocated buffer, which subsequent calls will overwrite.
 */
void TcpTransfering::addrInfoSet()
{
	if (mInfoSet)
		return;

	if (mSocketFd < 0)
		return;

	struct sockaddr_in addr;
	socklen_t addrLen;

	memset(&addr, 0, sizeof(addr));

	addrLen = sizeof(addr);
	::getsockname(mSocketFd, (struct sockaddr*)&addr, &addrLen);
	mAddrLocal = ::inet_ntoa(addr.sin_addr);
	mPortLocal = ::ntohs(addr.sin_port);

	addrLen = sizeof(addr);
	::getpeername(mSocketFd, (struct sockaddr*)&addr, &addrLen);
	mAddrRemote = ::inet_ntoa(addr.sin_addr);
	mPortRemote = ::ntohs(addr.sin_port);

	mInfoSet = true;
}

void TcpTransfering::processInfo(char *pBuf, char *pBufEnd)
{
	dInfo("State\t\t\t%s\n", ProcStateString[mState]);
	dInfo("Bytes received\t\t%d\n", mBytesReceived);

	if (!mInfoSet)
		return;

	dInfo("%s:%d <--> ", mAddrLocal.c_str(), mPortLocal);
	dInfo("%s:%d\n", mAddrRemote.c_str(), mPortRemote);
}

