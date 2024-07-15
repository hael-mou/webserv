/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpServer header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-02                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef	  __HTTPSERVER_HPP__
# define   __HTTPSERVER_HPP__
/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

# include "Directive.hpp"
# include "HttpErrorPage.hpp"
# include "IServer.hpp"
# include "HttpLocation.hpp"

/*******************************************************************************
    * DEFAULT VALUES :
*******************************************************************************/
# define   DEFAULT_LISTEN              "0.0.0.0:80"
# define   DEFAULT_TIMEOUT             7
# define   DEFAULT_BODY_BUFFER_SIZE    1024
# define   DEFAULT_MIME_TYPE           "text/html"
# define   DEFAULT_SERVER_ROOT         "."

/*******************************************************************************
    * PorotocolFactory Class :
*******************************************************************************/
namespace http
{
	class Server : public IServer
	{
    public:

        typedef std::map<std::string, http::Location::SharedPtr> LocationMap;

        Server(Directive::SharedPtr aServerDir);
        virtual ~Server(void);

        bool    isMatch(const_string& aHostName) const;
        bool    isKeepAlive(void) const;


        void    setListens(const StringVector& aListens);
        void    setServerNames(const StringVector& aServerName);
        void    setConnectionType(const StringVector& aConnection);
        void    setKeepAliveTimeout(const StringVector& aTimeout);
        void    setBodyBufferSize(const StringVector& aBodyBufferSize);
        void    setMaxBodySize(const StringVector& aMaxBodySize);
        void    setDefaultMimeType(const StringVector& aDefaultType);
        void    setMimeTypes(const StringVector& aTypes);
        void    setServerRoot(const StringVector& aRoot);
        void    setLocations(Directive::SharedPtr aServerDir,
                                Directive::DirPtrVector aLocation);

        const StringVector&   getListens(void) const;
        const StringVector&   getServerNames(void) const;
        time_t                getKeepAliveTimeout(void) const;
        unsigned long         getBodyBufferSize(void) const;
        unsigned long         getMaxBodySize(void) const;
        const std::string&    getMimeType(const_string aExtansion) const;
        const ErrorPages&     getErrorPages(void) const;
        const LocationMap&    getLocations(void) const;

    private:
	    StringVector    mListens;
	    StringVector    mServerName;
        std::string     mRoot; 
        bool            mKeepAlive;
        time_t          mKeepAliveTimeout;
        unsigned long   mBodyBufferSize;
        unsigned long   mMaxBodySize;
        StringMap       mMimeTypes;
        ErrorPages      mErrorPages;
        LocationMap     mLocations;
        // location
    };
}

#endif /* __HTTPSERVER_HPP__ */