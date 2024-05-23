/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ SelectMultiplexer implementation file ]                              #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#include "SelectMultiplexer.hpp"

/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor : ]==========================================================
SelectMultiplexer::SelectMultiplexer(void)
	: mMaxHandle(0)
{
	FD_ZERO(&mReadSet);
	FD_ZERO(&mWriteSet);
	FD_ZERO(&mReadSetTmp);
	FD_ZERO(&mWriteSetTmp);
}

//===[ Destructor : ]===========================================================
SelectMultiplexer::~SelectMultiplexer(void)
{
}

/*******************************************************************************
	* Methods :
*******************************************************************************/

//===[ RegisterHandle : ]=======================================================
void SelectMultiplexer::registerHandle(const Handle& aHandle, const Mode& aMode)
{
	FD_SET(aHandle, (aMode == Read ? &mReadSet : &mWriteSet));
	mMaxHandle = (mMaxHandle > aHandle) ? mMaxHandle : aHandle;
}

//===[ RemoveHandle : ]=========================================================
void SelectMultiplexer::removeHandle(const Handle& aHandle, const Mode& aMode)
{
	int newMaxFd = 0;

	FD_CLR(aHandle, (aMode == IMultiplexer::Read ? &mReadSet : &mWriteSet));
	for (int iFd = 0 ; iFd < mMaxHandle + 1 ; iFd++)
	{
		if (FD_ISSET(iFd, &mReadSet) || FD_ISSET(iFd, &mWriteSet))
			newMaxFd = iFd;
	}
	mMaxHandle = newMaxFd;
}

//===[ GetReadyHandles : ]======================================================
SelectMultiplexer::HandleQueue	SelectMultiplexer::getReadyHandles(void) const
{
	HandleQueue		readyHandles;
	for (int fd = 0 ; fd < mMaxHandle + 1 ; ++fd)
	{
		if (FD_ISSET(fd, &mReadSetTmp) || FD_ISSET(fd, &mWriteSetTmp))
			readyHandles.push(fd);
	}
	return (readyHandles);
}

//===[ WaitEvent : ]============================================================
int		SelectMultiplexer::waitEvent(long long aTimeout_ms)
{
	struct timeval	tv;
	tv.tv_sec	= aTimeout_ms / 1000;
	tv.tv_usec	= (aTimeout_ms % 1000) * 1000;
	
	mReadSetTmp  = mReadSet;
	mWriteSetTmp = mWriteSet;
	
	return (::select(mMaxHandle + 1, &mReadSetTmp, &mWriteSetTmp, NULL, &tv));
}
