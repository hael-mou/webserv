/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpRequest header file ]                                           #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-09                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef __HTTPREQUEST_HPP__
# define __HTTPREQUEST_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

# include "IServer.hpp"
# include "IRequest.hpp"

# include "HttpReader.hpp"
// to add ChunkdedReader Header Here

# include <iostream>

/*******************************************************************************
    * Class Request :
*******************************************************************************/

namespace http
{

    class Request : public IRequest
    {
    public:
        Request(std::string& aBuffer);
        virtual ~Request(void);
        
        void			selectMatechedRoute(const ServerVector& aServerList);
        void            setHeader(std::string& aLine);
     
        std::string		getVersion(void) const;
        std::string		getMethod(void) const;
        std::string		getUriPath(void) const;
        std::string		getHeader(std::string const& key);
        StringMap		getUriQuery(void) const;
        StringMap 		getHeaders(void) const;
        const IServer&  getMatchedServer(void) const;
        const Location& getMatchedLocation(void) const;
     
        void            buildBody(const std::string& aBody);

        void            display(void) const;

    private:
        IReader::SharedPtr  mReader;
        IServer::SharedPtr  mMatchedServer;
        Location::SharedPtr mMatchedLocation;
        std::string		    mVersion;
        std::string		    mMethod;
        std::string		    mUri;	
        StringMap		    mHeaders;
        StringMap		    mQuery;
    
        bool                _isInnerPath(const std::string& uri, const std::string& requestUri);
        void                _setRequestLine(const std::string& aLine);
        std::string&        _parseUri(std::string& aUri);
        void                _parseQuery(std::string& aUri);
        Location::SharedPtr _selectMatchedLocation();
        IServer::SharedPtr  _selectMatchedServer(const ServerVector& aServerList);
    
    };
};

#endif /* __HTTPREQUEST_HPP__ */