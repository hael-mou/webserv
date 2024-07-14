/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpErrorPage header file ]                                          #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-12                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef	  __HTTPERRORPAGE_HPP__
# define   __HTTPERRORPAGE_HPP__

/*******************************************************************************
	* Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

/*******************************************************************************
	* CUSTOM Error PAGE :
*******************************************************************************/

# define CUSTOM_ERROR_PAGE "\
	<!DOCTYPE html>\
			<head>\
				<title>$(TITLE)</title>\
				<style>\
					body {\
						font-family: Arial, sans-serif;\
						background: #282828;\
						padding: 10px;\
						color: #c6c6c6;\
						margin: 0 auto;\
						height: 100%;\
						min-height: 100vh;\
						box-sizing: border-box;\
					}\
				</style>\
			</head>\
			<body>\
				<center><h1>$(ERROR_MESSAGE)</h1></center>\
				<hr />\
				<center><p> web server </p></center>\
			</body>\
	</html>"

/*******************************************************************************
	* HttpErrorPage Class :
*******************************************************************************/
namespace http
{
	class ErrorPages
	{
	public:
		ErrorPages(void);
		ErrorPages(const StringVector& aErrorPages, const_string& aRoot);
		virtual ~ErrorPages(void);

		void			 setErrorPage(unsigned int aCode, const_string& aPath);
		const_string&    getErrorPagePath(unsigned int aCode) const;
		// IResponse*		build(unsigned int aCode, const_string& aMessage) const;

	private:
		std::map<int, std::string>		mErrorPages;
	};
}

#endif /* __HTTPERRORPAGE_HPP__ */