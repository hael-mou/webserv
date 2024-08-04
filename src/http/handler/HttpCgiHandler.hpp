/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpCgiHandler header file ]                                         #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-29                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef	  __HTTPCGIHANDLER_HPP__
# define   __HTTPCGIHANDLER_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "typedefs.hpp"
# include "Utils.hpp"

# include "IEventHandler.hpp"
# include "IResponse.hpp"
# include "IRequest.hpp"
# include "IClient.hpp"

# include "HttpFactory.hpp"

#include <unistd.h>
#include <sys/wait.h>

/*******************************************************************************
    * class : CgiHandler :
*******************************************************************************/
namespace http
{   
    class CgiHandler : public IEventHandler
    {
    public:
        typedef IEventHandlerQueue (CgiHandler::*Operation)(void);

        CgiHandler(IClient::SharedPtr aClient, IRequest::SharedPtr aRequest);
        virtual ~CgiHandler();

        const Handle&           getHandle(void) const;
        IMultiplexer::Mode      getMode(void) const;
        IEventHandlerQueue      handleEvent(void);
        bool                    isTerminated(void) const;

    private:
        IClient::SharedPtr      mClient;
        IRequest::SharedPtr     mRequest;
        std::string             mRessourcePath;
        std::string             mOutPath;
        fd_t                    mOutFd;
        int                     mCgiProcess;
        Operation               mCurrentOperation;
        time_t                  mCgiLastActiveTime;
    
        // StringVector            _buildCgiEnv(void) const;
        void                    _cleanHandler(void);
        void                    _checkUploadPermission(void);
        void                    _createCgiProcess(void);
        void                    _setupCgiIo(void);
        string                  _getAbsoluteCgiPath(void) const;

        IEventHandlerQueue      _setupCgi(void);
        IEventHandlerQueue      _waitCgiToFinish(void);

    };
};

#endif /* __HTTPCGIHANDLER_HPP__ */
