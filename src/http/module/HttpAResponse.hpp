/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpAResponse header file ]                                          #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __HttpAResponse_HPP__
# define   __HttpAResponse_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

# include "IResponse.hpp"

# include <iostream>

/*******************************************************************************
    * HttpAResponse Class :
*******************************************************************************/
namespace http
{
    class AResponse : public IResponse
    {
    public:   
        AResponse(void);
        virtual	~AResponse(void);

        AResponse&	   setVersion(const std::string& aVersion);
        AResponse&	   setStatusCode(unsigned int aStatusCode);
        AResponse&	   setHeader(const std::string& aHeader, const_string& aValue);

        const_string&  getHeader(const_string& aHeader) const;
        time_t         getSendTimeout(void) const;

        std::string    toRaw(void);
        void           display(void) const;

    protected:
        std::string    mVersion;
        std::string    mStatusline;
        StringMap      mHeaders;
        time_t         mSendTimeout;
        std::string    mRawMessage;

        static const UintStringMap    sStatusMessage;
        static const UintStringMap    _sinitStatusMessage(void);
    };
}

#endif	/* __HttpAResponse_HPP__ */