/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ HttpLocation header file ]                                          #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-07-09                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef __HTTPLOCATION_HPP__
# define __HTTPLOCATION_HPP__


/******************************************************************************
 * Defaults :
******************************************************************************/

# define DEFAULT_ROOT  "." /* NGNIX : /home/website.com/public_html*/
# define DEFAULT_UPLOAD "/tmp" 
# define DEFAULT_AUTOINDEX "off"
# define DEFAULT_INDEX_FILES "index.html"
/*******************************************************************************
    * Includes :
*******************************************************************************/
# include "shared_ptr.hpp"
# include "typedefs.hpp"
# include "Utils.hpp"

#include "Directive.hpp"
/*******************************************************************************/

namespace http
{
    class Location
    {
        public:

            typedef mem::shared_ptr<http::Location>  SharedPtr; 

            Location(Directive::SharedPtr aLocationDir);
            ~Location(void);

            bool                    isAllowedMethod(const_string& aMethod) const;
            bool                    isAutoIndex(void) const;
        
            const_string&           getUri(void) const;
            const_string&           getRoot(void) const;
            const_string&           getUpload(void) const;
            const_string&           getRedirect(void) const;
            const StringVector&     getCgiExt(void) const;
            const StringVector&     getIndexFiles(void) const;

            void    setUri(const StringVector&  aUri);
            void    setRoot(const StringVector&  aRoot);
            void    setUpload(const StringVector& aCgiExt);
            void    setCgiExt(const StringVector& aCgiExt);
            void    setRedirect(const StringVector&  aReturn);
            void    setAutoIndex(const StringVector& aAutoIndex);
            void    setIndexFiles(const StringVector& aIndexFiles);
            void    setAllowedMethods(const StringVector& aAllowedMethods);

        private:

            bool            mAutoIndex;
            std::string     mUri;
            std::string     mRoot;
            std::string     mRedirect;
            std::string     mUpload;
            StringVector    mCgiExt;
            StringVector    mIndexFiles;
            StringVector    mAllowedMethods;
    };
};

#endif /* __HTTPLOCATION_HPP__ */

