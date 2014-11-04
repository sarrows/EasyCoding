#ifndef __LIST_BASE_H__
#define __LIST_BASE_H__

/********************************************************
 * author: 李国强
 * date: 2005-8-10
 * desc: 实现List容器基类，定义子类提供常用的基本成员函数
 ********************************************************/

#include "config_platform.h"

template<class T>
class ListBase
{
public:
    typedef size_t size_type;
	virtual int append(const T&) = 0;    //插入
	virtual int remove(T&) = 0;          //移除头元素
	virtual size_type size () const = 0; //返回队列中元素的个数
	virtual bool empty() const = 0;      //是否为空
	virtual bool full() const = 0;       //是否已满
	virtual void clear() = 0;            //清空所有元素
};

/*******************************************************
 * author: 李国强
 * date:  2005-8-10
 * desc: 实现List容器的迭代器基类，成员函数为纯虚函数
 *******************************************************/
template<class ITEM>
class ListIteratorBase
{
public:
	typedef ListBase<ITEM>* ListContainerPtr;  //重定义容器类
public:
	explicit ListIteratorBase(ListContainerPtr ptr)  //迭代器构造函数
	    : list_ptr_(ptr){}
protected:
	ListContainerPtr list_ptr_; //链表指针
};

#endif
