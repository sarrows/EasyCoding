#ifndef __LIST_BASE_H__
#define __LIST_BASE_H__

/********************************************************
 * author: ���ǿ
 * date: 2005-8-10
 * desc: ʵ��List�������࣬���������ṩ���õĻ�����Ա����
 ********************************************************/

#include "config_platform.h"

template<class T>
class ListBase
{
public:
    typedef size_t size_type;
	virtual int append(const T&) = 0;    //����
	virtual int remove(T&) = 0;          //�Ƴ�ͷԪ��
	virtual size_type size () const = 0; //���ض�����Ԫ�صĸ���
	virtual bool empty() const = 0;      //�Ƿ�Ϊ��
	virtual bool full() const = 0;       //�Ƿ�����
	virtual void clear() = 0;            //�������Ԫ��
};

/*******************************************************
 * author: ���ǿ
 * date:  2005-8-10
 * desc: ʵ��List�����ĵ��������࣬��Ա����Ϊ���麯��
 *******************************************************/
template<class ITEM>
class ListIteratorBase
{
public:
	typedef ListBase<ITEM>* ListContainerPtr;  //�ض���������
public:
	explicit ListIteratorBase(ListContainerPtr ptr)  //���������캯��
	    : list_ptr_(ptr){}
protected:
	ListContainerPtr list_ptr_; //����ָ��
};

#endif
