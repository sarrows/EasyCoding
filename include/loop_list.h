#ifndef __LOOP_LIST_INCLUDE
#define __LOOP_LIST_INCLUDE

#include "listbase.h"     //List容器和其迭代器基类的定义头文件

#pragma once

template<class ITEM> struct LoopListNode
{
	ITEM item_;
};
template<class ITEM> class LoopList;   //事先声明
/*********************************************
 * author: 李国强
 * date: 2005-8-11
 * desc: 队列的迭代器，便于遍历队列
 ********************************************/
template< class ITEM >
class LoopListIterator : public ListIteratorBase<ITEM>
{
	typedef LoopList<ITEM>*     ListPtr;
	friend class LoopList<ITEM>;
public:
	typedef LoopListNode<ITEM>  ThrNode;
	typedef typename ListIteratorBase<ITEM>::ListContainerPtr ListContainerPtr;
	
	explicit LoopListIterator(ListContainerPtr ptr = 0, ulong idx = 0)//构造函数
		:ListIteratorBase<ITEM>(ptr), index_(idx){}
	LoopListIterator(const LoopListIterator<ITEM> & obj)   //拷贝构造函数
		:ListIteratorBase<ITEM>(obj.list_ptr_), index_(obj.index_){}
	
	LoopListIterator & operator= (const LoopListIterator & obj);  //赋值函数
	LoopListIterator & operator++ (void);      //前缀++
	LoopListIterator operator++ (int);         //后缀++
	bool operator == (const LoopListIterator& obj) const;   //比较函数,等式比较
	bool operator != (const LoopListIterator& obj) const;   //比较函数,不等式比较
	ITEM* operator->(void) const;        //->操作符函数
	ITEM& operator*(void);       //*操作符函数
private:
	ulong index_;         //索引值，表示当前遍历的偏移(相对队列的开始位置)
};
/*********************************************
 * author: 李国强
 * date: 2005-8-12
 * desc: 此类实现了环行队列，按照模板的规则定义
 * 模板的第一个参数表示类型，第二个参数表示个数
 * 从线程锁继承,但没有加锁同步,这个工作让使用者完成
 ********************************************/
template<class ITEM>
class LoopList : public ListBase<ITEM>
{
	friend class LoopListIterator<ITEM>; //允许迭代器访问本类的私有及保护成员
	typedef LoopListNode<ITEM>* NodePtr;
	typedef LoopListNode<ITEM>  Node;
public:
	typedef LoopList<ITEM>            Self;
	typedef LoopListIterator<ITEM>    Iterator;
	typedef const LoopListIterator<ITEM> Const_Iterator;
	typedef typename ListBase<ITEM>::size_type size_type;
public:
	explicit LoopList(ulong bound = 1024);  //构造函数，设置队列的维数
    LoopList (const LoopList<ITEM>& obj); //拷贝构造函数
	~LoopList();          //析构函数
	
	int  append(const ITEM&);   //插入到队列
	int  remove(ITEM&);        //从队列取出第一个元素,并从队列中删除头元素

	size_type  size () const;     //队列中元素的个数
	bool empty() const;        //检查队列是否为空
	bool full() const;         //检查队列是否已满
    void clear();              //清空元素
    
	Iterator  begin() const;   //返回开始位置的迭代器
	Iterator  end () const;    //返回最后一个位置的迭代器

	LoopList<ITEM>& operator = (const LoopList<ITEM>& obj);  //赋值操作符
	size_type  distance(const Iterator& it) const;        //到开始处的距离
	void    advance(Iterator& it, size_type size) const; //在当前位置上向前移动size
private:
    void create_buffer()
    { this->elements_ = new Node[max_size_]; }
    void release_buffer()
    { delete [] this->elements_; }
private:
	long head_pos_;   //第一个元素的位置
	long tail_pos_;   //最后一个元素的位置
	long max_size_;   //环行队列最大元素的个数, 比用户设定的大1
	NodePtr elements_;   //存放元素的数组
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
