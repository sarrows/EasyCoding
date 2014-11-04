#ifndef __RECT_INCLUDE__
#define __RECT_INCLUDE__

#include "config_platform.h"

#ifdef MY_WIN32

class ECExport Rect : public RECT
{
public:
    Rect();
    Rect(int,int,int,int);
    Rect(const Rect& obj);
    int cx() const;
    int cy() const;
    void move(int,int,int,int);
    void move(int,int);
    Rect& operator == (const Rect& obj);
};

inline int Rect::cx() const
{
    return (this->right - this->left);
}

inline int Rect::cy() const
{
    return (this->top < this->bottom ?
        this->bottom - this->top
        : this->top - this->bottom);
}
#endif

#endif
