#ifndef __DILINKLIST_INL__
#define __DILINKLIST_INL__

/***************************************
 * 迭代器类,实现模板类的函数
 **************************************/

/***************************************
 * 递增函数,类似++X
 **************************************/
template<class ITEM>
DiLinkListIterator<ITEM> &
DiLinkListIterator<ITEM>::operator++ (void)
{
	this->prev_node_ = this->cur_node_;
	this->cur_node_  = this->cur_node_->next_;
	return *this;
}
/***************************************
 * 递增函数,类似X++
 **************************************/
template<class ITEM>
DiLinkListIterator<ITEM>
DiLinkListIterator<ITEM>::operator++ (int)
{
	DiLinkListIterator<ITEM> temp = *this;
	this->prev_node_ = this->cur_node_;
	this->cur_node_  = this->cur_node_->next_;
	return temp;
}
/***************************************
 * 赋值操作
 **************************************/
template<class ITEM>
DiLinkListIterator<ITEM> &
DiLinkListIterator<ITEM>::operator = (const DiLinkListIterator & obj)
{
	this->prev_node_ = obj.prev_node_;
	this->cur_node_  = obj.cur_node_;
	this->list_ptr_  = obj.list_ptr_;
	return *this;
}
/***************************************
 * 比较操作,是否相等
 **************************************/
template<class ITEM>
bool
DiLinkListIterator<ITEM>::operator == (const DiLinkListIterator & obj) const
{
	return this->cur_node_ == obj.cur_node_;
}
/***************************************
 * 比较操作,是否小于
 **************************************/
template<class ITEM>
bool
DiLinkListIterator<ITEM>::operator != (const DiLinkListIterator & obj) const
{
	return this->cur_node_ != obj.cur_node_;
}
/***************************************
 * 取值操作,返回元素指针
 **************************************/
template<class ITEM>
ITEM&
DiLinkListIterator<ITEM>::operator * (void)
{
	return ((DiListNode<ITEM>*)this->cur_node_)->item_;
}
/***************************************
 * 指针操作
 **************************************/
template<class ITEM>
ITEM*
DiLinkListIterator<ITEM>::operator -> (void) const
{
	return &(((DiListNode<ITEM>*)this->cur_node_)->item_);
}






/*************************************************
 * 类: DiLinkList 单向链表实现
 ************************************************/


/***************************************
 * 缺省构造函数
 **************************************/
template<class ITEM>
DiLinkList<ITEM>::DiLinkList()
: end_node_(0), cur_size_(0)
{
    critical_ = 0;
	this->end_node_ = (EndNode*)create_node();
	this->end_node_->next_ = this->end_node_;
	this->end_node_->prev_ = this->end_node_;
}
/***************************************
 * 拷贝构造函数
 **************************************/
template<class ITEM>
DiLinkList<ITEM>::DiLinkList(const DiLinkList<ITEM>& obj)
{
	*this = obj;
}
/***************************************
 * 赋值操作符
 **************************************/
template<class ITEM>
DiLinkList<ITEM> &
DiLinkList<ITEM>::operator = (const DiLinkList<ITEM> &obj)
{
	clear();

	NodePtr node = obj.end_node_->next_;
	for (;node != obj.end_node_; node = node->next_)
		append ( ((ThrNode*)node)->item_ );
	return *this;
}
/***************************************
 * 根据开始元素,返回起始迭代器
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::Iterator
DiLinkList<ITEM>::begin () const
{
	return Iterator((Self*)this, end_node(), first_node() );
}
/***************************************
 * 根据最后一个元素,返回最大迭代器
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::Iterator
DiLinkList<ITEM>::end() const
{
	return Iterator((Self*)this, this->end_node_->prev_, end_node() );
}
/***************************************
 * 向队列的末尾增加一个元素,
 * 成功时元素个数 ;失败-1
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::append (const ITEM & item)
{
	return insert (end(), item);
}
/***************************************
 * 从队列移除首元素
 * 成功为0失败-1
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::remove (ITEM & item)
{
	if (this->end_node_->next_ && (this->end_node_->next_ != this->end_node_)) {
		item = ((ThrNode*)this->end_node_->next_)->item_;
		Iterator it = begin();
		erase (it); //删除第一个元素
		return 0;
	}
	return -1;
}
/***************************************
 * 向队列插入一个元素,插入所给迭代器后面
 * 成功时返回节点数;失败时返回-1
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::insert (const Iterator& it, const ITEM & item)
{
	//构造出节点对象
	NodePtr node = create_node ();
	((ThrNode*)node)->item_  = item;

	//插入到当前位置的后面,如果it是end则插入到前面
	if (it.cur_node_ == this->end_node_ ) {
		node->next_      = this->end_node_;
		this->end_node_->prev_->next_ = node;
		this->end_node_->prev_ = node;
	} else {
		node->next_         = it.cur_node_->next_;
		it.cur_node_->next_ = node;
		if (it.cur_node_ == end_node_->prev_)
			this->end_node_->prev_ = node;
	}
	return ++cur_size_;
}
/***************************************
 * 根据迭代器从队列中删除一个元素
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::erase (Iterator& it)
{
	if (it.cur_node_ == this->end_node_)  //最后一个节点不能删除
		return -1;
	/*释放当前节点并更新当前节点为下一个节点*/
	it.prev_node_->next_ = it.cur_node_->next_;
	release_node(it.cur_node_);
	it.cur_node_ = it.prev_node_->next_;
	

	/*如果下一个节点为end_node则调整end_node的前向指针*/
	if (it.cur_node_ == this->end_node_) {
		this->end_node_->prev_ = it.prev_node_;
	}
	return --(this->cur_size_);
}
/***************************************
 * 根据迭代器从队列中删除一组元素
 * 成功时返回剩余节点数,失败时-1
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::erase (const Iterator& itbegin, const Iterator& itend)
{
	for (Iterator it = itbegin; it != itend; )
		erase(it);
}
/***************************************
 * 清空所有节点,只剩下end_node_
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::clear ()
{
	erase (begin (), end());
}
/***************************************
 * 返回是否为空
 **************************************/
template<class ITEM>
bool
DiLinkList<ITEM>::empty () const
{
	return this->cur_size_ == 0 ? true : false;
}
/***************************************
 * 返回是否已满
 **************************************/
template<class ITEM>
bool
DiLinkList<ITEM>::full () const
{
	return false;
}
/***************************************
 * 针对每个元素执行传入函数，遇false返回
 **************************************/
template<class ITEM>
bool
DiLinkList<ITEM>::do_each_element(std::function<bool(ITEM&)> f)
{
	for (Iterator it = begin(); it != end(); it++)
		if (f(*it)) return false;
	return true;
}
/***************************************
 * 针对每个元素以传入函数判断，遇true返回
 **************************************/
template<class ITEM>
bool
DiLinkList<ITEM>::search_element(Iterator& oit, std::function<bool(ITEM&)> f) const
{
	Iterator it = begin();
	for (; it != end(); it++) {
		if (f(*it)) {
			oit = it;
			return true;
		}
	}
	return false;
}
/***************************************
 * 返回元素个数
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::size_type
DiLinkList<ITEM>::size () const
{
	return this->cur_size_;
}
/***************************************
 * 获取第一个节点
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::NodePtr
DiLinkList<ITEM>::first_node() const
{
	return this->end_node_->next_;
}
/***************************************
 * 获取最后一个元素
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::NodePtr
DiLinkList<ITEM>::end_node() const
{
	return this->end_node_;
}
/***************************************
 * 构造一个节点
 * 目前采用new方式,以后可考虑采用构造器
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::NodePtr
DiLinkList<ITEM>::create_node()
{
	return new ThrNode;
}
/***************************************
 * 释放一个节点
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::release_node(typename DiLinkList<ITEM>::NodePtr node)
{
	delete node;
}
/***************************************
 * 返回当前位置相对起始位置的距离
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::size_type
DiLinkList<ITEM>::distance(const Iterator & it) const
{
	size_type size  = 0;
	NodePtr node = first_node();
	for (;node != it.cur_node_; node = node->next_, size++);  //递增size直到当前的node
	return size;
}
/***************************************
 * 根据输入值,把当前位置向前移动size单位
 * 如果超出边界,则当前位置为end
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::advance(Iterator& it, size_type size) const
{
	//往前递增,但不能超过end节点
	while (size-- > 0 && it.cur_node_ != end_node() ) {
		it.prev_node_ = it.cur_node_;
		it.cur_node_  = it.cur_node_->next_;
	}
}
#endif
