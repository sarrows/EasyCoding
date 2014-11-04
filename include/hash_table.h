#ifndef __HASHTABLE_INCLUDE
#define __HASHTABLE_INCLUDE

/*******************************************
 * author: ���ǿ
 * date: 2006-1-10
 * desc: ʵ��HASH��,ÿ��Ͱ��������ʵ��
 * 
 ******************************************/
#include "config_platform.h"
#include "hash_fun.h"           //HASH����

#ifndef MY_ANDROID
#pragma warning(disable:4284)
#endif

#pragma pack(4)
/******************************************
 * HASH�������ڵ�,�ڵ㱣��KEY��VALUE
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
 * HASH ����������,�ṩ���õķ���
 *****************************************/
template<typename KEY, typename ITEM >
class HashIteratorBase
{
public:
    typedef HashTable<KEY, ITEM>* HashPtr;
	typedef HashNode<KEY, ITEM>*  NodePtr;
public:
    explicit HashIteratorBase(NodePtr node) //ȱʡ���캯��
        : cur_node_(node)
    {
    }
protected:
	NodePtr cur_node_;
};
/******************************************
 * HASH �������ӻ�������,ʵ�ֻ��෽��
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
	
	explicit HashIterator()                             //ȱʡ���캯��
		: HashIteratorBase<KEY, ITEM>(0) {}
    explicit HashIterator (NodePtr node)
        : HashIteratorBase<KEY, ITEM>(node){}
    HashIterator (const Self& obj)    //�������캯��
        : HashIteratorBase<KEY, ITEM>(obj.cur_node_) {}

    Self& operator = (const Self& obj);         //��ֵ������
    bool  operator == (const Self& obj) const;  //�Ƚϲ�����,��ʽ
    bool  operator != (const Self& obj) const;  //�Ƚϲ�����,����ʽ
    Self& operator ++ (void);
    Self  operator ++ (int);
    ItemPtr operator -> (void) const;
    ItemRef operator * (void);
};
/******************************************
 * HASH ��,������ģ�����,��һ��Ϊ����ڵ�
 * �ڶ���ģ��Ϊ���ֽڵ������
 * �û�����ͨ�������޸�Ĭ�ϵ�ģ�����
 * ��ͬ������,��������ʹ���߾�����
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
    typedef HashFunc<Key>            KeyFunc;   //HASH����
    typedef HashNode<Key, Value>     ThrNode;
    typedef ThrNode*                 NodePtr;
    typedef ThrNode&                 NodeRef;

	friend class HashIterator<Key, Value>;   //ָ����Ԫ��      

    explicit HashTable(size_type buckets = 1024); //ȱʡ
    HashTable(const Self& obj);       //�������캯��
    ~HashTable();

    Self& operator = (const Self& obj);        //��ֵ������
    
    Iterator begin (size_type pos = size_npos) const;            //��ʼ������
    Iterator end () const;                           //����������
	
    typename HashTable<KEY, ITEM>::size_type  size ()const;                          //��ǰ��Ԫ��
    typename HashTable<KEY, ITEM>::size_type   bucket_count()const;                   //��ǰ��ռ�õ�Ͱ��
    typename HashTable<KEY, ITEM>::size_type bucket_size() const { return bucket_size_;}
    typename HashTable<KEY, ITEM>::size_type bucket_elems(size_type bucket)const;      //ָ����Ͱ�е�Ԫ�ظ���
    typename HashTable<KEY, ITEM>::size_type bucket_pos(const Key& key) const;       //����KEY����������Ͱλ��

    Iterator insert (const Key& key, const Value& val); //����key�������
    Iterator insert_with_replace (const Key& key, const Value& val); //����key�������,�����ھʹ���
    void     insert (const Iterator& first, const Iterator& last);
	
	Iterator find (const Key& key) const;           //����KEYֵ���в���
	Iterator operator [] (const Key& key) const;
    bool     is_end(Iterator& it) const { return end() == it; }
    
    typename HashTable<KEY, ITEM>::size_type erase (const Key& key);
	typename HashTable<KEY, ITEM>::size_type erase (Iterator it);
	typename HashTable<KEY, ITEM>::size_type erase (Iterator it1, Iterator it2);
	
	void     clear ();
private:
    typename HashTable<KEY, ITEM>::size_type get_key_num (const Key& key) const   //����KEYֵ��������
    { return key_func_(key); }
	const NodePtr  end_node () const              //��ʶһ�������ĩβ
	{	return (NodePtr)0;	}
	NodePtr  create_node ()                 //����һ���½ڵ�,Ŀǰֻ�Ǽ򵥵�new
	{
		NodePtr o = new ThrNode;
		o->bucket_nums_ = 0;
		o->bucket_top_ = 0;
		o->next_ = 0;
		elements_++;
		return o;
	}
	void     release_node (NodePtr node)    //�ͷ�һ���ڵ�
	{	delete node; elements_--; }
	void     init_buckets();
	void     unini_buckets();
private:
    typename HashTable<KEY, ITEM>::size_type bucket_size_;  //Ͱ����ı߽�
    typename HashTable<KEY, ITEM>::size_type elements_;     //��Ԫ�ظ���
    NodePtr* buckets_;      //Ͱ����,˫ָ��
    KeyFunc  key_func_;     //ʵ����HASH����
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
