/******************************************
 * author: 李国强
 * date: 2005-8-12
 * desc: 实现队列及其迭代器类的模板函数
 * 被include在loop_list.h文件中
 *****************************************/



/*******************************************
 *赋值操作符函数
 ******************************************/
template<class ITEM>
LoopListIterator<ITEM>&
LoopListIterator<ITEM>::operator= (const LoopListIterator<ITEM> & obj)
{
	this->list_ptr_ = obj.list_ptr_;
	this->index_    = obj.index_;
	return *this;
}
/*****************************************
 * 递增操作符函数，前缀++操作符
 ****************************************/
template<class ITEM>
LoopListIterator<ITEM> &
LoopListIterator<ITEM>::operator++ (void)
{
	this->index_ = ++this->index_ % ((ListPtr)this->list_ptr_)->max_size_;
	return *this;
}
/******************************************
 * 递增函数，后缀++
 ********************************************/
template<class ITEM>
LoopListIterator<ITEM>
LoopListIterator<ITEM>::operator ++ (int)
{
	LoopListIterator<ITEM> tmp(*this);
	this->index_ = ++this->index_ % ((ListPtr)this->list_ptr_)->max_size_;
	return tmp;
}
/******************************************
 * 等式比较函数
 ********************************************/
template<class ITEM>
bool
LoopListIterator<ITEM>::operator == (const LoopListIterator& obj) const
{
	return (this->index_ == obj.index_);
}
/******************************************
 * 不等式比较函数
 ********************************************/
template<class ITEM>
bool
LoopListIterator<ITEM>::operator != (const LoopListIterator& obj) const
{
	return (this->index_ != obj.index_);
}
/******************************************
 * 指针操作符
 * 为了效率不进行边界检查
 ********************************************/
template<class ITEM>
ITEM*
LoopListIterator<ITEM>::operator-> (void) const
{
	return &(((ListPtr)this->list_ptr_)->elements_[this->index_].item_);
}
/******************************************
 * *号操作符
 * 为了效率不进行边界检查
 ********************************************/
template<class ITEM>
ITEM&
LoopListIterator<ITEM>::operator*(void)
{
	return ((ListPtr)this->list_ptr_)->elements_[this->index_].item_;
}






/******************************************************
 * LoopList类, 构造函数
 *****************************************************/

template<class ITEM>
LoopList<ITEM>::LoopList(ulong bound)
: max_size_(bound), head_pos_(0), tail_pos_(0)
{
	create_buffer();
}
/**************************************
 *拷贝构造函数
 *************************************/
template<class ITEM>
LoopList<ITEM>::LoopList(const LoopList<ITEM>& obj)
{
	*this = obj;
}
/**************************************
 *析构函数，释放资源
 *************************************/
template<class ITEM>
LoopList<ITEM>::~LoopList()
{
	release_buffer();
}
/**************************************
 *赋值操作符
 *************************************/
template<class ITEM>
LoopList<ITEM>&
LoopList<ITEM>::operator = (const LoopList<ITEM>& obj)
{
	if (this != &obj) {
		this->max_size_ = obj.max_size_;
		this->head_pos_ = 0;
		this->tail_pos_ = 0;
		if (elements_)
			release_buffer();
		create_buffer();
		Iterator it = obj.begin();
		for(; it != obj.end(); ++it)
			append (*it);
	}
	return *this;
}
/*************************************
 *增加，向队列末尾添加一个元素
 *成功时返回0，否则返回－1
 ************************************/
template<class ITEM>
int
LoopList<ITEM>::append (const ITEM& obj)
{
	if ( !full() ) {  //队列未满，则添加新元素
		Node node;
		node.item_ = obj;
		this->elements_[this->tail_pos_ % this->max_size_] = node;
		this->tail_pos_ = ++this->tail_pos_ % this->max_size_;
		return 0;
	}
	return -1;
}
/*************************************
 *移除元素，把队列首元素从队列中移除
 *成功时返回0，否则返回－1
 ************************************/
template<class ITEM>
int
LoopList<ITEM>::remove (ITEM & obj)
{
	if ( !empty() ) { //队列为空时，无法移除首元素
		obj = this->elements_[this->head_pos_ % this->max_size_].item_;
		this->head_pos_ = ++this->head_pos_ % this->max_size_;
		return 0;
	}
	return -1;
}
/*************************************
 *判断是否为空，根据两个索引间距来判断
 ************************************/
template<class ITEM>
bool
LoopList<ITEM>::empty () const
{
	return (this->head_pos_ == this->tail_pos_);
}
/*************************************
 *判断是否已满，根据两个索引间距来判断
 ************************************/
template<class ITEM>
bool
LoopList<ITEM>::full () const
{
	return (this->head_pos_ - this->tail_pos_ + this->max_size_) % this->max_size_ == 1;
}
/*************************************
 * 清空队列
 ************************************/
template<class ITEM>
void
LoopList<ITEM>::clear()
{
	this->head_pos_ = this->tail_pos_ = 0;   //设置起始、终止点表示清空
}
/*************************************
 *返回队列当前元素的个数
 ************************************/
template<class ITEM>
typename LoopList<ITEM>::size_type
LoopList<ITEM>::size () const
{
	return ((this->tail_pos_ - this->head_pos_ + this->max_size_ ) % this->max_size_);
}
/*************************************
 *根据队列第一个元素的位置，返回对应的迭代器
 ************************************/
template<class ITEM>
typename LoopList<ITEM>::Iterator
LoopList<ITEM>::begin () const
{
	return Iterator((Self*)this, this->head_pos_);
}
/*************************************
 *根据队列第一个元素的位置，返回对应的迭代器
 ************************************/
template<class ITEM>
typename LoopList<ITEM>::Iterator
LoopList<ITEM>::end () const
{
	return Iterator((Self*)this, this->tail_pos_);
}
/******************************************
 * 获取当前位置到开始处的距离
 ********************************************/
template<class ITEM>
typename LoopList<ITEM>::size_type
LoopList<ITEM>::distance (const Iterator& it) const
{
	return ((it.index_ % this->max_size_) - this->head_pos_ + this->max_size_) % this->max_size_;
}
/******************************************
 * 向前移动指定size个位置
 ********************************************/
template<class ITEM>
void
LoopList<ITEM>::advance (Iterator& it, size_type size) const
{
	it.index_ = (it.index_ + size) % this->max_size_;
}
