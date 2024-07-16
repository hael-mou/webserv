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

#ifndef   __HttpRawResponse_HPP__
# define   __HttpRawResponse_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

# include "HttpAResponse.hpp"

# include <iostream>

/*******************************************************************************
	* HttpRawResponse Class :
*******************************************************************************/
namespace http
{
	class RawResponse : public AResponse
	{
	public:
		RawResponse(void);
		virtual ~RawResponse(void);

		RawResponse&    setBody(const_string& aBody);
		std::string     toRaw(void);
		void			removeBytesSent(size_t bytesSent);
        bool            eof(void) const;
		void			display(void) const;
	
	private:
		std::string		mBody;
		bool			misConverted;
	};
}

#endif	/* __HttpRawResponse_HPP__ */