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
        if (values.size() < 2)
            continue;

        std::string path = values[values.size() - 1];
        if (path[path.length() - 1] == '/')
            continue;
    
        for (size_t i = 0; i < values.size() - 1; ++i)
        {
            int code = integer::strToInt(values[i]);
            if (code <= 0 || code > 999)
                continue ;
			
            setErrorPage(code, aRoot + path);
        }
    }
}

//===[ Destructor: ErrorPages ]=================================================
http::ErrorPages::~ErrorPages(void) {}

/*******************************************************************************
	* Public Methods :
*******************************************************************************/


void	http::ErrorPages::setErrorPage(u_int aCode, const_string& aPath)
{
	mErrorPages[aCode] = aPath;
}

//===[ Method: build error page ]===============================================
http::IResponse::SharedPtr http::ErrorPages::build(u_int aCode) const
{
    try
    {
        std::string path = mErrorPages.at(aCode);
        http::FileResponse* response = new http::FileResponse();
        response->setStatusCode(aCode);
        response->setHeader("Content-Type", "text/html");
        response->setPath(path);
        return (response);
    }
    catch (...)
    {
        http::RawResponse* response = new http::RawResponse();
        response->setTemplateOn();
        response->setStatusCode(aCode);
        response->setBody(CUSTOM_ERROR_PAGE);
        return (response);
    }
}