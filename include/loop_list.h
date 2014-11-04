#ifndef __LOOP_LIST_INCLUDE
#define __LOOP_LIST_INCLUDE

#include "listbase.h"     //List�����������������Ķ���ͷ�ļ�

#pragma once

template<class ITEM> struct LoopListNode
{
	ITEM item_;
};
template<class ITEM> class LoopList;   //��������
/*********************************************
 * author: ���ǿ
 * date: 2005-8-11
 * desc: ���еĵ����������ڱ�������
 ********************************************/
template< class ITEM >
class LoopListIterator : public ListIteratorBase<ITEM>
{
	typedef LoopList<ITEM>*     ListPtr;
	friend class LoopList<ITEM>;
public:
	typedef LoopListNode<ITEM>  ThrNode;
	typedef typename ListIteratorBase<ITEM>::ListContainerPtr ListContainerPtr;
	
	explicit LoopListIterator(ListContainerPtr ptr = 0, ulong idx = 0)//���캯��
		:ListIteratorBase<ITEM>(ptr), index_(idx){}
	LoopListIterator(const LoopListIterator<ITEM> & obj)   //�������캯��
		:ListIteratorBase<ITEM>(obj.list_ptr_), index_(obj.index_){}
	
	LoopListIterator & operator= (const LoopListIterator & obj);  //��ֵ����
	LoopListIterator & operator++ (void);      //ǰ׺++
	LoopListIterator operator++ (int);         //��׺++
	bool operator == (const LoopListIterator& obj) const;   //�ȽϺ���,��ʽ�Ƚ�
	bool operator != (const LoopListIterator& obj) const;   //�ȽϺ���,����ʽ�Ƚ�
	ITEM* operator->(void) const;        //->����������
	ITEM& operator*(void);       //*����������
private:
	ulong index_;         //����ֵ����ʾ��ǰ������ƫ��(��Զ��еĿ�ʼλ��)
};
/*********************************************
 * author: ���ǿ
 * date: 2005-8-12
 * desc: ����ʵ���˻��ж��У�����ģ��Ĺ�����
 * ģ��ĵ�һ��������ʾ���ͣ��ڶ���������ʾ����
 * ���߳����̳�,��û�м���ͬ��,���������ʹ�������
 ********************************************/
template<class ITEM>
class LoopList : public ListBase<ITEM>
{
	friend class LoopListIterator<ITEM>; //������������ʱ����˽�м�������Ա
	typedef LoopListNode<ITEM>* NodePtr;
	typedef LoopListNode<ITEM>  Node;
public:
	typedef LoopList<ITEM>            Self;
	typedef LoopListIterator<ITEM>    Iterator;
	typedef const LoopListIterator<ITEM> Const_Iterator;
	typedef typename ListBase<ITEM>::size_type size_type;
public:
	explicit LoopList(ulong bound = 1024);  //���캯�������ö��е�ά��
    LoopList (const LoopList<ITEM>& obj); //�������캯��
	~LoopList();          //��������
	
	int  append(const ITEM&);   //���뵽����
	int  remove(ITEM&);        //�Ӷ���ȡ����һ��Ԫ��,���Ӷ�����ɾ��ͷԪ��

	size_type  size () const;     //������Ԫ�صĸ���
	bool empty() const;        //�������Ƿ�Ϊ��
	bool full() const;         //�������Ƿ�����
    void clear();              //���Ԫ��
    
	Iterator  begin() const;   //���ؿ�ʼλ�õĵ�����
	Iterator  end () const;    //�������һ��λ�õĵ�����

	LoopList<ITEM>& operator = (const LoopList<ITEM>& obj);  //��ֵ������
	size_type  distance(const Iterator& it) const;        //����ʼ���ľ���
	void    advance(Iterator& it, size_type size) const; //�ڵ�ǰλ������ǰ�ƶ�size
private:
    void create_buffer()
    { this->elements_ = new Node[max_size_]; }
    void release_buffer()
    { delete [] this->elements_; }
private:
	long head_pos_;   //��һ��Ԫ�ص�λ��
	long tail_pos_;   //���һ��Ԫ�ص�λ��
	long max_size_;   //���ж������Ԫ�صĸ���, ���û��趨�Ĵ�1
	NodePtr elements_;   //���Ԫ�ص�����
};

#include "loop_list.inl"

#ifdef UNITTEST
#include <cppunit/extensions/HelperMacros.h>
class LoopListTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(LoopListTest);
        CPPUNIT_TEST(test_looplist);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void test_looplist();
};
#endif

#endif
