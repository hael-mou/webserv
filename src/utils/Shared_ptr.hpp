/** ************************************************************************ ***
#                                                                              #
#         __ __         __    __  ___                                          #
#        / // /__ ____ / /   /  |/  /__  __ __                                 #
#       / _  / _ `/ -_) /   / /|_/ / _ \/ // /                                 #
#      /_//_/\_,_/\__/_/   /_/  /_/\___/\_,_/                                  #
#                                                                              #
#      | [ Shared_ptr header file ]                                             #
#      | By: hael-mou <hamzaelmoudden2@gmail.com>                              #
#      | Created: 2024-06-26                                                   #
#                                                                              #
** ************************************************************************* **/

#ifndef   __SHARED_PTR_HPP__
# define   __SHARED_PTR_HPP__

/*******************************************************************************
    * Includes :
*******************************************************************************/
# include <cstddef>

/*******************************************************************************
    * shared_ptr Template Class :
*******************************************************************************/
namespace mem {

template<typename T>
class shared_ptr
{
public:
    shared_ptr(T* aPtr = new T());
    shared_ptr(const shared_ptr<T>& aOther);
    virtual	~shared_ptr(void);

    size_t          use_count(void);
    T*              get(void);

    shared_ptr<T>&  operator=(const shared_ptr<T>& aOther);
    T&              operator*(void);
    T*              operator->(void);
    operator        bool(void) const;


private:
    T*      mPtr;
    size_t* mRef_count;
};

};

//===[ implementation ]=======================================================
# include "Shared_ptr.tpp"

#endif /* __SHARED_PTR_HPP__ */