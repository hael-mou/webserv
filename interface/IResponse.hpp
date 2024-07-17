/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ IResponse Interface ]                                               #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-16                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __IResponse_HPP__
# define   __IResponse_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"

/*******************************************************************************
    * http::IRequest Interface :
*******************************************************************************/
namespace http
{
    class IResponse
    {
    public:
        typedef mem::shared_ptr<IResponse>           SharedPtr;

        virtual ~IResponse(void) {}

        
        virtual std::string     toRaw(void) = 0;
        virtual void            removeBytesSent(size_t bytesSent) = 0;
        virtual time_t          getSendTimeout(void) const = 0;
        virtual const_string&   getHeader(const_string& aHeader) const = 0;
        virtual bool            eof(void) const = 0;
        virtual void            display(void) const = 0;
    };
}

/*********************************************************************************
    * Status Code :
*******************************************************************************/
namespace http
{
    enum StatusCode
    {
        CONTINUE                        = 100,
        SWITCHING_PROTOCOLS             = 101,
        PROCESSING                      = 102,
        EARLY_HINTS                     = 103,

        OK                              = 200,
        CREATED                         = 201,
        ACCEPTED                        = 202,
        NON_AUTHORITATIVE               = 203,
        NO_CONTENT                      = 204,
        RESET_CONTENT                   = 205,
        PARTIAL_CONTENT                 = 206,
        MULTI_STATUS                    = 207,
        ALREADY_REPORTED                = 208,
        IM_USED                         = 226,

        MULTIPLE_CHOICES                = 300,
        MOVED_PERMANENTLY               = 301,
        MOVED_TEMPORARILY               = 302,
        SEE_OTHER                       = 303,
        NOT_MODIFIED                    = 304,
        USE_PROXY                       = 305,
        SWITCH_PROXY                    = 306,
        TEMPORARY_REDIRECT              = 307,
        PERMANENT_REDIRECT              = 308,

        BAD_REQUEST                     = 400,
        UNAUTHORIZED                    = 401,
        PAYMENT_REQUIRED                = 402,
        FORBIDDEN                       = 403,
        NOT_FOUND                       = 404,
        METHOD_NOT_ALLOWED              = 405,
        NOT_ACCEPTABLE                  = 406,
        REQUEST_TIMEOUT                 = 408,
        CONFLICT                        = 409,
        GONE                            = 410,
        LENGTH_REQUIRED                 = 411,
        PRECONDITION_FAILED             = 412,
        PAYLOAD_TOO_LARGE               = 413,
        URI_TOO_LONG                    = 414,
        UNSUPPORTED_MEDIA_TYPE          = 415,
        RANGE_NOT_SATISFIABLE           = 416,
        EXPECTATION_FAILED              = 417,
        IM_A_TEAPOT                     = 418,
        MISDIRECTED_REQUEST             = 421,

        INTERNAL_SERVER_ERROR           = 500,
        NOT_IMPLEMENTED                 = 501,
        BAD_GATEWAY                     = 502,
        SERVICE_UNAVAILABLE             = 503,
        GATEWAY_TIMEOUT                 = 504,
        INSUFFICIENT_STORAGE            = 507,
        LOOP_DETECTED                   = 508,
        NOT_EXTENDED                    = 510,
    };
}

#endif	/* __IResponse_HPP__ */