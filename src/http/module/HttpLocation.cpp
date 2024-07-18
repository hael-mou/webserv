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

# include "HttpLocation.hpp"

/*******************************************************************************
    * Construction :
*******************************************************************************/

//=== [ HttpLocation Class Constructor ] ======================================
http::Location::Location(Directive::SharedPtr aLocationDir)
{
    setUri(aLocationDir->getTerminal("uri"));
    setRoot(aLocationDir->getTerminal("root"));
    setUpload(aLocationDir->getTerminal("upload"));
    setCgiExt(aLocationDir->getTerminal("cgi_extensions"));
    setIndexFiles(aLocationDir->getTerminal("index"));
    setRedirect(aLocationDir->getTerminal("redirect"));
    setAutoIndex(aLocationDir->getTerminal("auto_index"));
    setAllowedMethods(aLocationDir->getTerminal("allowed_methods"));
}

//===[ Destructor: HttpLocation ]===============================================
http::Location::~Location(void) {}

/*******************************************************************************
     * Public Methods :
*******************************************************************************/

//===[Method : setUri]==========================================================
void    http::Location::setUri(const StringVector&  aUri)
{
    if (aUri.empty() == true)
       throw(std::exception());
    mUri = (aUri[0][0] == '/') ? aUri[0] : '/' + aUri[0];
}

//===[Method : setRoot]=========================================================
void    http::Location::setRoot(const StringVector&  aRoot)
{
    if (aRoot.size() == 1)
    {
        mRoot = aRoot[0];
        if (!mRoot.empty() && mRoot[mRoot.length() - 1] == '/')
        {
            mRoot.resize(mRoot.length() - 1);
        }
        return;
    }
    
    mRoot = DEFAULT_ROOT;
}

//===[Method : setUpload]=======================================================
void    http::Location::setUpload(const StringVector& aUpload)
{
    if (aUpload.size() == 1)
    {
        mUpload = aUpload[0];
        if (!mUpload.empty() && mUpload[mUpload.length() - 1] == '/')
        {
            mUpload.resize(mUpload.length() - 1);
        }
        return;
    }
    
    mUpload = DEFAULT_UPLOAD;
}

//===[Method : setCgiExt]========================================================
void    http::Location::setCgiExt(const StringVector&  aCgiExt)
{
    if (aCgiExt.size() == 1)
        mCgiExt = str::split(aCgiExt[0], ' ');
}

//===[Method : setRedirect]=====================================================
void    http::Location::setRedirect(const StringVector&  aReturn)
{
    // To search 
    (void) aReturn;
}

//===[Method : setAutoIndex]====================================================
void    http::Location::setAutoIndex(const StringVector&  aAutoIndex)
{
    mAutoIndex = false;
    if (aAutoIndex.size() == 1)
    {
        std::string autoIndex = str::toLower(aAutoIndex[0]);
        mAutoIndex = (autoIndex == "on") ? true : false;
    }
}

//===[Method : setIndexFiles]================================================
void    http::Location::setIndexFiles(const StringVector&  aIndexFiles)
{
    if (aIndexFiles.size() == 1)
        mIndexFiles = str::split(aIndexFiles[0], ' ');
    else
        mIndexFiles = str::split(DEFAULT_INDEX_FILES, ' ');
}

//===[Method : setAllowedMethods]=============================================
void    http::Location::setAllowedMethods(const StringVector&  aAllowedMethods)
{
    if (aAllowedMethods.size() == 1)
    {
        mAllowedMethods = str::split(aAllowedMethods[0], ' ');
    }
}

/*** * Getters :
*******************************************************************************/

//=== [ HttpLocation Getters ] =================================================
const std::string& http::Location::getUri(void) const
{
    return (mUri);
}

//===[ Method : getRoot ]=======================================================
const std::string& http::Location::getRoot(void) const
{
    return (mRoot);
}

//===[ Method : getUpload ]=====================================================
const std::string& http::Location::getRedirect(void) const
{
    return (mRedirect);
}

//===[ Method : getCgiExt ]=====================================================
const StringVector& http::Location::getAllowedMethods(void) const
{
    return (mAllowedMethods);
}

//===[ Method : getIndexFiles ]================================================
const StringVector& http::Location::getIndexFiles(void) const
{
    return (mIndexFiles);
}

//===[ Method : getAutoIndex ]==================================================
bool http::Location::getAutoIndex(void) const
{
    return (mAutoIndex);
}

//===[ Method : getCgiExt ]=====================================================
const StringVector&    http::Location::getCgiExt(void) const
{
    return (mCgiExt);
}

//===[ Method : getUpload ]=====================================================
const std::string&     http::Location::getUpload(void) const
{
    return (mUpload);
}
