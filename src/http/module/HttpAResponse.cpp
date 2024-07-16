/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpAResponse implementation file ]                                  #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpAResponse.hpp"

/*******************************************************************************
    * Static Variables :
*******************************************************************************/
const UintStringMap
http::AResponse::sStatusMessage = http::AResponse::_sinitStatusMessage();

/*******************************************************************************
    * Construction :
*******************************************************************************/

//===[ Constructor: AResponse ]================================================
http::AResponse::AResponse(void)
    : mVersion("HTTP/1.1"),
      mStatusline("501 Not Implemented"),
      mSendTimeout(60),
      mRawMessage("")
{
}

//===[ Destructor: AResponse ]=================================================
http::AResponse::~AResponse(void) {}

/*******************************************************************************
    * Public Methods :
*******************************************************************************/

//===[ Methode : set Version ]=================================================
http::AResponse& http::AResponse::setVersion(const std::string& aVersion)
{
    mVersion = aVersion;
    return (*this);
}

//===[ Methode : set StatusCode ]==============================================
http::AResponse& http::AResponse::setStatusCode(unsigned int aStatusCode)
{
    UintStringMap::const_iterator it = sStatusMessage.find(aStatusCode);
    if (it != sStatusMessage.end())
    {
        mStatusline = it->second;
    }
    return (*this);
}

//===[ Methode : set Header ]==================================================
http::AResponse& http::AResponse::setHeader(const std::string& aHeader,
                                            const_string& aValue)
{
    mHeaders[str::toLower(aHeader)] = aValue;
    return (*this);
}

//===[ Methode : get Header ]==================================================
const_string& http::AResponse::getHeader(const_string& aHeader) const
{
    StringMap::const_iterator it = mHeaders.find(str::toLower(aHeader));
    if (it != mHeaders.end())
    {
        return (it->second);
    }
    return (EmptyString);
}

//===[ Methode : get Send Timeout ]=============================================
time_t  http::AResponse::getSendTimeout(void) const
{
    return (mSendTimeout);
}

//===[ Methode : toRaw ]=======================================================
std::string http::AResponse::toRaw(void)
{
    mRawMessage = mVersion + " " + mStatusline + "\r\n";
    StringMap::const_iterator it = mHeaders.begin();
    while (it != mHeaders.end())
    {
        mRawMessage += it->first + ": " + it->second + "\r\n";
        ++it;
    }
    mRawMessage += "\r\n";
    return (mRawMessage); 
}

//===[ Methode : display ]=====================================================
void http::AResponse::display(void) const
{
    std::cout << "statusline: " << mVersion << " " <<  mStatusline << std::endl;
    std::cout << "headers: ===== " << std::endl;
    for (StringMap::const_iterator it = mHeaders.begin();
         it != mHeaders.end(); it++) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    std::cout << "send timeout: " << mSendTimeout << std::endl;
    std::cout << "================" << std::endl;
}

/*******************************************************************************
    * Static Methods :
*******************************************************************************/

//===[ Methode : _sinitStatusMessage ]==========================================
const UintStringMap
http::AResponse::_sinitStatusMessage(void)
{
    UintStringMap statusMessage;

    statusMessage[200] = "200 OK";
    statusMessage[404] = "404 Not Found";

    return (statusMessage);
}