/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpRawResponse header file ]                                        #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-05-18                                                   #
#                                                                              #
** ************************************************************************* **/

#include "HttpRawResponse.hpp"

/*******************************************************************************
	* Construction :
*******************************************************************************/

//===[ Constructor: RawResponse ]==============================================
http::RawResponse::RawResponse(void)
	: mBody(""),
	  misConverted(false)
{
	setHeader("Content-Length", "0");
}

//===[ Destructor: RawResponse ]===============================================
http::RawResponse::~RawResponse(void) {}

/*******************************************************************************
	* Public Methods :
*******************************************************************************/

//===[ Methode : set Body ]====================================================
http::RawResponse& http::RawResponse::setBody(const_string& aBody)
{
	mBody = aBody;
	setHeader("Content-Length", std::to_string(mBody.size()));
	return (*this);
}

//===[ Methode : toRaw ]=======================================================
std::string http::RawResponse::toRaw(void) 
{
	if (misConverted == false)
	{
		mRawMessage = AResponse::toRaw();
		mRawMessage += mBody;
		misConverted = true;
	}
	return (mRawMessage);
}

//===[ Methode : removeBytesSent ]=============================================
void http::RawResponse::removeBytesSent(size_t bytesSent)
{
	mRawMessage.erase(0, bytesSent);
}

//===[ Methode : eof ]=========================================================
bool http::RawResponse::eof(void) const
{
	return (misConverted && mRawMessage.empty());
}

//===[ Methode : display ]=====================================================
void http::RawResponse::display(void) const
{
	AResponse::display();
	std::cout << "Body: \n" << mBody << std::endl;
	std::cout << "=================" << std::endl;
}
