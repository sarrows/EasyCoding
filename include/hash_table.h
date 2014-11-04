#ifndef __HASHTABLE_INCLUDE
#define __HASHTABLE_INCLUDE

/*******************************************
 * author: 李国强
 * date: 2006-1-10
 * desc: 实现HASH表,每个桶采用链表实现
 * 
 ******************************************/
#include "config_platform.h"
#include "hash_fun.h"           //HASH函数

#ifndef MY_ANDROID
#pragma warning(disable:4284)
#endif

#pragma pack(4)
/******************************************
 * HASH表的链表节点,节点保存KEY和VALUE
 *****************************************/
template<typename KEY, typename ITEM>
struct HashItem
{
	KEY  key_;
	ITEM val_;
};
template<typename KEY, typename ITEM >
struct HashNode
{
	int  bucket_top_;
	uint bucket_nums_;
    HashItem<KEY, ITEM>  item_;
	HashNode<KEY, ITEM>* next_;
};

template<typename KEY, typename ITEM > class HashTable;
/******************************************
 * HASH 迭代器基类,提供常用的方法
 *****************************************/
template<typename KEY, typename ITEM >
class HashIteratorBase
{
public:
    typedef HashTable<KEY, ITEM>* HashPtr;
	typedef HashNode<KEY, ITEM>*  NodePtr;
public:
    explicit HashIteratorBase(NodePtr node) //缺省构造函数
        : cur_node_(node)
    {
    }
protected:
	NodePtr cur_node_;
};
/******************************************
 * HASH 迭代器从基类派生,实现基类方法
 *****************************************/
template<typename KEY, typename ITEM >
class HashIterator : public HashIteratorBase<KEY, ITEM>
{
    typedef HashIterator<KEY, ITEM> Self;
    typedef HashItem<KEY, ITEM>     ThrItem;
	typedef typename HashIteratorBase<KEY, ITEM>::HashPtr HashPtr;
	typedef typename HashIteratorBase<KEY, ITEM>::NodePtr NodePtr;
    typedef ThrItem*                ItemPtr;
    typedef ThrItem&                ItemRef;
public:
	typedef size_t size_type;
	
	explicit HashIterator()                             //缺省构造函数
		: HashIteratorBase<KEY, ITEM>(0) {}
    explicit HashIterator (NodePtr node)
        : HashIteratorBase<KEY, ITEM>(node){}
    HashIterator (const Self& obj)    //拷贝构造函数
        : HashIteratorBase<KEY, ITEM>(obj.cur_node_) {}

    Self& operator = (const Self& obj);         //赋值操作符
    bool  operator == (const Self& obj) const;  //比较操作符,等式
    bool  operator != (const Self& obj) const;  //比较操作符,不等式
    Self& operator ++ (void);
    Self  operator ++ (int);
    ItemPtr operator -> (void) const;
    ItemRef operator * (void);
};
/******************************************
 * HASH 表,带两个模板参数,第一个为链表节点
 * 第二个模板为保持节点的链表
 * 用户可以通过输入修改默认的模板参数
 * 加同步机制,但具体由使用者决定。
 *****************************************/
template<typename KEY, typename ITEM >
class HashTable
{
public:
    typedef KEY             Key;
    typedef ITEM            Value;
    typedef HashIterator<KEY, ITEM> Iterator;
	typedef typename HashIterator<KEY, ITEM>::size_type    size_type;
    typedef HashTable<Key, Value >   Self;
    typedef HashFunc<Key>            KeyFunc;   //HASH函数
    typedef HashNode<Key, Value>     ThrNode;
    typedef ThrNode*                 NodePtr;
    typedef ThrNode&                 NodeRef;

	friend class HashIterator<Key, Value>;   //指定友元类      

    explicit HashTable(size_type buckets = 1024); //缺省
    HashTable(const Self& obj);       //拷贝构造函数
    ~HashTable();

    Self& operator = (const Self& obj);        //赋值操作符
    
    Iterator begin (size_type pos = size_npos) const;            //开始迭代器
    Iterator end () const;                           //结束迭代器
	
    typename HashTable<KEY, ITEM>::size_type  size ()const;                          //当前总元素
    typename HashTable<KEY, ITEM>::size_type   bucket_count()const;                   //当前被占用的桶数
    typename HashTable<KEY, ITEM>::size_type bucket_size() const { return bucket_size_;}
    typename HashTable<KEY, ITEM>::size_type bucket_elems(size_type bucket)const;      //指定的桶中的元素个数
    typename HashTable<KEY, ITEM>::size_type bucket_pos(const Key& key) const;       //根据KEY返回所处的桶位置

    Iterator insert (const Key& key, const Value& val); //根据key插入对象
    Iterator insert_with_replace (const Key& key, const Value& val); //根据key插入对象,不存在就创建
    void     insert (const Iterator& first, const Iterator& last);
	
	Iterator find (const Key& key) const;           //根据KEY值进行查找
	Iterator operator [] (const Key& key) const;
    bool     is_end(Iterator& it) const { return end() == it; }
    
    typename HashTable<KEY, ITEM>::size_type erase (const Key& key);
	typename HashTable<KEY, ITEM>::size_type erase (Iterator it);
	typename HashTable<KEY, ITEM>::size_type erase (Iterator it1, Iterator it2);
	
	void     clear ();
private:
    typename HashTable<KEY, ITEM>::size_type get_key_num (const Key& key) const   //根据KEY值生成索引
    { return key_func_(key); }
	const NodePtr  end_node () const              //标识一个链表的末尾
	{	return (NodePtr)0;	}
	NodePtr  create_node ()                 //构造一个新节点,目前只是简单的new
	{
		NodePtr o = new ThrNode;
		o->bucket_nums_ = 0;
		o->bucket_top_ = 0;
		o->next_ = 0;
		elements_++;
		return o;
	}
	void     release_node (NodePtr node)    //释放一个节点
	{	delete node; elements_--; }
	void     init_buckets();
	void     unini_buckets();
private:
    typename HashTable<KEY, ITEM>::size_type bucket_size_;  //桶数组的边界
    typename HashTable<KEY, ITEM>::size_type elements_;     //总元素个数
    NodePtr* buckets_;      //桶数组,双指针
    KeyFunc  key_func_;     //实例化HASH函数
};

#include "hash_table.inl"

#pragma pack()

#ifdef UNITTEST
#include <cppunit/extensions/HelperMacros.h>
class HashTableTest : public CPPUNIT_NS::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(HashTableTest);
        CPPUNIT_TEST(test_hashtable);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void test_hashtable();
};
#endif

#endif
