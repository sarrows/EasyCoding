#ifndef __DILINKLIST_H__
#define __DILINKLIST_H__

/***************************************
 * author: ���ǿ
 * dete: 2005-8-10
 * desc: ʵ�ֵ�������,�ӻ���ListBase����
 *	���಻�ṩ���߳�ͬ������,��ҪӦ�����ⲿʵ��
 **************************************/

#include "listbase.h"      //List����
#include "ipc/mutex.h"
#include <functional>

/******************************************
 * ��������ڵ�
 * ���ü̳й�ϵ
 * Ŀ����ֻ����������ITEMʱ,��������
 ****************************************/
struct DiListNodeBase
{
	DiListNodeBase * next_;
};
/*����ڵ�����������һ���ڵ�ʱ,����ʵ��˫����*/
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
 * ��ʵ�ֵ�����,�ӵ�������������
 * �˵�����Ϊǰ��,����ִ�еݼ���prev����
 * �������Ʋ����ڵ������б���ڵ�ָ��ķ�ʽ
 * �����������Ȼû�п��ǵ������̰߳�ȫ,���Ǵ�Ч���Ͽ��ǻ���ֵ�õ�
 ***************************************/
template<class ITEM>
class DiLinkListIterator : public ListIteratorBase<ITEM>
{
    typedef DiListNodeBase * NodePtr;
	typedef typename ListIteratorBase<ITEM>::ListContainerPtr ListContainerPtr; 
	friend class DiLinkList<ITEM>;
public:
	explicit DiLinkListIterator()                   //ȱʡ���캯��
		: ListIteratorBase<ITEM>(0),
		prev_node_(0),
		cur_node_(0) {}

	DiLinkListIterator(const DiLinkListIterator<ITEM> & obj)  //�������캯��
		: ListIteratorBase<ITEM>(obj.list_ptr_),
		prev_node_(obj.prev_node_),
		cur_node_(obj.cur_node_) {}
	
	DiLinkListIterator & operator++(void);    //���� ,ǰ׺++
	DiLinkListIterator   operator++(int);      //����,��׺++
	DiLinkListIterator & operator = (const DiLinkListIterator & obj); //��ֵ����
	bool operator == ( const DiLinkListIterator & obj) const;  //��ȱȽϲ�����
	bool operator != (const DiLinkListIterator & obj) const;   //����ȱȽϲ�����
	
	ITEM& operator *(void);                //���ؽڵ�����
	ITEM* operator -> (void) const;         //���ؽڵ�ָ��

private:
	explicit DiLinkListIterator(ListContainerPtr ptr,    //���캯��,��Ϊ˽��
		NodePtr prev_node,
		NodePtr cur_node)
		: ListIteratorBase<ITEM>(ptr),
		prev_node_(prev_node),
		cur_node_(cur_node){}
private:
	NodePtr cur_node_;        //��ǰ�ڵ�
	NodePtr prev_node_;       //��һ���ڵ�,������һ���ڵ��Ŀ����ɾ��֮��
};


/******************************************
 * ��������
 * ���̰߳�ȫ��̳�,��û���ṩ�κ�ͬ������,�����û����
 ****************************************/
template < class ITEM>
class DiLinkList : public ListBase<ITEM>
{
public:
	typedef DiListNodeEnd       EndNode;  //������ʾ�����ĩβ
	typedef DiListNode<ITEM>    ThrNode;
	typedef DiListNodeBase *    NodePtr;  //����ڵ�ָ��
	typedef DiLinkList<ITEM>    Self;
	typedef DiLinkListIterator<ITEM> Iterator;   //������
	typedef typename ListBase<ITEM>::size_type size_type;
	friend class DiLinkListIterator<ITEM>;

	/*************************************************
	 * ���캯��,ͨ���������ֵ,�����������Ԫ�ظ���
	 * Ԫ�ظ�������ܳ���max_size_
	 * ���캯���Զ�����һ���ڵ���Ϊ���һ�ڵ�,ʵ���в���ʹ��
	 ************************************************/
	explicit DiLinkList();
	DiLinkList(const Self & obj);   //�������캯��
	/***************************************
	 * ��������,�ͷ����е���Դ
	 **************************************/
	~DiLinkList(){
        clear();
        release_node(end_node_);
        if (critical_) delete critical;
    }

	/*****************************
	 * ���������������Ŀ�ʼ��ĩβ
	 *****************************/
	Iterator begin () const;
	Iterator end () const;

	int  append (const ITEM&);    //���һ��Ԫ��
	int  remove (ITEM&);          //�Ƴ���Ԫ��
	int  insert (const Iterator& it, const ITEM &);  //����pos����һ��Ԫ��
	int  erase (Iterator& it);  //ɾ��һ��Ԫ��
	void erase (const Iterator& itbegin, const Iterator& itend);
	void clear ();  //�������Ԫ��
	
	size_type size () const; //Ԫ�ظ���
	bool empty () const;   //�Ƿ�Ϊ��
	bool full () const;    //�Ƿ�����

	Self & operator = (const Self & obj);
	
	size_type distance(const Iterator & it) const;          //����ʼ���ľ���
	void   advance(Iterator& it, size_type size) const;     //�ӵ�ǰλ�ÿ�ʼ��ǰ�ƶ�

	bool do_each_element(std::function<bool(ITEM&)> f);
	bool search_element(Iterator& it, std::function<bool(ITEM&)> f) const;

	void lock() { // ���뱣������
        if (!critical_) critical_ = new Mutex();
        critical_->acquire();
    }
	void unlock() { if (critical_) critical_->release(); } // �뿪��������

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
