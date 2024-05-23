/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ SelectMultiplexer header file ]                                      #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __SELECTMULTIPLEXER_HPP__
#define    __SELECTMULTIPLEXER_HPP__

/*******************************************************************************
	* Includes
*******************************************************************************/
# include "IMultiplexer.hpp"
# include <sys/select.h>

/*******************************************************************************
	* Class SelectMultiplexer
*******************************************************************************/
class SelectMultiplexer : public IMultiplexer
{
public:
	SelectMultiplexer(void);
	virtual ~SelectMultiplexer(void);

	void		 registerHandle(const Handle& aHandle, const Mode& aMode);
	void		 removeHandle(const Handle& aHandle, const Mode& aMode);
	int			 waitEvent(long long aTimeout_ms);
	HandleQueue	 getReadyHandles(void) const;

private:
	int			mMaxHandle;
	fd_set		mReadSet, mReadSetTmp;
	fd_set		mWriteSet, mWriteSetTmp;
};

#endif /* __SELECTMULTIPLEXER_HPP__ */
