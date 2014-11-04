#ifndef __DILINKLIST_H__
#define __DILINKLIST_H__

/***************************************
 * author: 李国强
 * dete: 2005-8-10
 * desc: 实现单向链表,从基类ListBase派生
 *	此类不提供多线程同步问题,需要应用在外部实现
 **************************************/

#include "listbase.h"      //List基类
#include "ipc/mutex.h"
#include <functional>

/******************************************
 * 单向链表节点
 * 采用继承关系
 * 目的是只有真正关心ITEM时,才用子类
 ****************************************/
struct DiListNodeBase
{
	DiListNodeBase * next_;
};
/*这个节点仅仅用于最后一个节点时,并不实现双链表*/
struct DiListNodeEnd : public DiListNodeBase
{
	DiListNodeBase * prev_;
};
template<class ITEM>
struct DiListNode : public DiListNodeBase
{
	ITEM item_;
};

template<class ITEM> class DiLinkList;

/****************************************
 * 先实现迭代器,从迭代器基类派生
 * 此迭代器为前向,不能执行递减或prev操作
 * 此类的设计采用在迭代器中保存节点指针的方式
 * 这样的设计虽然没有考虑到访问线程安全,但是从效率上考虑还是值得的
 ***************************************/
template<class ITEM>
class DiLinkListIterator : public ListIteratorBase<ITEM>
{
    typedef DiListNodeBase * NodePtr;
	typedef typename ListIteratorBase<ITEM>::ListContainerPtr ListContainerPtr; 
	friend class DiLinkList<ITEM>;
public:
	explicit DiLinkListIterator()                   //缺省构造函数
		: ListIteratorBase<ITEM>(0),
		prev_node_(0),
		cur_node_(0) {}

	DiLinkListIterator(const DiLinkListIterator<ITEM> & obj)  //拷贝构造函数
		: ListIteratorBase<ITEM>(obj.list_ptr_),
		prev_node_(obj.prev_node_),
		cur_node_(obj.cur_node_) {}
	
	DiLinkListIterator & operator++(void);    //递增 ,前缀++
	DiLinkListIterator   operator++(int);      //递增,后缀++
	DiLinkListIterator & operator = (const DiLinkListIterator & obj); //赋值操作
	bool operator == ( const DiLinkListIterator & obj) const;  //相等比较操作符
	bool operator != (const DiLinkListIterator & obj) const;   //不相等比较操作符
	
	ITEM& operator *(void);                //返回节点引用
	ITEM* operator -> (void) const;         //返回节点指针

private:
	explicit DiLinkListIterator(ListContainerPtr ptr,    //构造函数,作为私有
		NodePtr prev_node,
		NodePtr cur_node)
		: ListIteratorBase<ITEM>(ptr),
		prev_node_(prev_node),
		cur_node_(cur_node){}
private:
	NodePtr cur_node_;        //当前节点
	NodePtr prev_node_;       //上一个节点,保存上一个节点的目的做删除之用
};


/******************************************
 * 单向链表
 * 从线程安全类继承,但没有提供任何同步机制,留给用户完成
 ****************************************/
template < class ITEM>
class DiLinkList : public ListBase<ITEM>
{
public:
	typedef DiListNodeEnd       EndNode;  //用来表示链表的末尾
	typedef DiListNode<ITEM>    ThrNode;
	typedef DiListNodeBase *    NodePtr;  //链表节点指针
	typedef DiLinkList<ITEM>    Self;
	typedef DiLinkListIterator<ITEM> Iterator;   //迭代器
	typedef typename ListBase<ITEM>::size_type size_type;
	friend class DiLinkListIterator<ITEM>;

	/*************************************************
	 * 构造函数,通过设置最大值,限制了链表的元素个数
	 * 元素个数最大不能超过max_size_
	 * 构造函数自动创建一个节点作为最后一节点,实际中并不使用
	 ************************************************/
	explicit DiLinkList();
	DiLinkList(const Self & obj);   //拷贝构造函数
	/***************************************
	 * 析构函数,释放所有的资源
	 **************************************/
	~DiLinkList(){
        clear();
        release_node(end_node_);
        if (critical_) delete critical;
    }

	/*****************************
	 * 返回两个迭代器的开始和末尾
	 *****************************/
	Iterator begin () const;
	Iterator end () const;

	int  append (const ITEM&);    //添加一个元素
	int  remove (ITEM&);          //移除首元素
	int  insert (const Iterator& it, const ITEM &);  //根据pos插入一个元素
	int  erase (Iterator& it);  //删除一个元素
	void erase (const Iterator& itbegin, const Iterator& itend);
	void clear ();  //清除所有元素
	
	size_type size () const; //元素个数
	bool empty () const;   //是否为空
	bool full () const;    //是否已满

	Self & operator = (const Self & obj);
	
	size_type distance(const Iterator & it) const;          //到开始处的距离
	void   advance(Iterator& it, size_type size) const;     //从当前位置开始向前移动

	bool do_each_element(std::function<bool(ITEM&)> f);
	bool search_element(Iterator& it, std::function<bool(ITEM&)> f) const;

	void lock() { // 进入保护区域
        if (!critical_) critical_ = new Mutex();
        critical_->acquire();
    }
	void unlock() { if (critical_) critical_->release(); } // 离开保护区域

private:
	NodePtr first_node() const;
	NodePtr end_node() const;
	NodePtr create_node();
	void    release_node(NodePtr node);
private:
	EndNode*    end_node_;
	size_type   cur_size_;
	EasyCoding::Mutex*      critical_;
};

#include "dilink_list.inl"

#ifdef UNITTEST
#include <cppunit/extensions/HelperMacros.h>
class DiLinkListTest :  public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(DiLinkListTest);
        CPPUNIT_TEST(test_linklist);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void test_linklist();
};
#endif

#endif
