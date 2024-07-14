/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpErrorPage implementation file ]                                  #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-12                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpErrorPage.hpp"
#include <iostream>
/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor: ErrorPages ]================================================
http::ErrorPages::ErrorPages(void) {}

//===[ Constructor: ErrorPages ]================================================
http::ErrorPages::ErrorPages(const StringVector& aErrorPages, const_string& aRoot)
{
	for (size_t index = 0; index < aErrorPages.size(); ++index)
    {
        StringVector values = str::split(aErrorPages[index], ' ');
        if (values.size() < 2 || values.back().back() == '/')
            continue;

        for (size_t i = 0; i < values.size() - 1; ++i)
        {
            int code = integer::strToInt(values[i]);
            if (code <= 0 || code > 999)
                continue ;
			
            setErrorPage(code, aRoot + "/" + values.back());
        }
    }
}

//===[ Destructor: ErrorPages ]=================================================
http::ErrorPages::~ErrorPages(void) {}

/*******************************************************************************
	* Public Methods :
*******************************************************************************/

//===[ setErrorPage: set the error page ]=======================================
void	http::ErrorPages::setErrorPage(unsigned int aCode, const_string& aPath)
{
	mErrorPages[aCode] = aPath;
}

//===[ getErrorPagePath: get the error page path ]==============================
const_string&	http::ErrorPages::getErrorPagePath(unsigned int aCode) const
{
	return (mErrorPages.at(aCode));
}