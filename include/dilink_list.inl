#ifndef __DILINKLIST_INL__
#define __DILINKLIST_INL__

/***************************************
 * ��������,ʵ��ģ����ĺ���
 **************************************/

/***************************************
 * ��������,����++X
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
 * ��������,����X++
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
 * ��ֵ����
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
 * �Ƚϲ���,�Ƿ����
 **************************************/
template<class ITEM>
bool
DiLinkListIterator<ITEM>::operator == (const DiLinkListIterator & obj) const
{
	return this->cur_node_ == obj.cur_node_;
}
/***************************************
 * �Ƚϲ���,�Ƿ�С��
 **************************************/
template<class ITEM>
bool
DiLinkListIterator<ITEM>::operator != (const DiLinkListIterator & obj) const
{
	return this->cur_node_ != obj.cur_node_;
}
/***************************************
 * ȡֵ����,����Ԫ��ָ��
 **************************************/
template<class ITEM>
ITEM&
DiLinkListIterator<ITEM>::operator * (void)
{
	return ((DiListNode<ITEM>*)this->cur_node_)->item_;
}
/***************************************
 * ָ�����
 **************************************/
template<class ITEM>
ITEM*
DiLinkListIterator<ITEM>::operator -> (void) const
{
	return &(((DiListNode<ITEM>*)this->cur_node_)->item_);
}






/*************************************************
 * ��: DiLinkList ��������ʵ��
 ************************************************/


/***************************************
 * ȱʡ���캯��
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
 * �������캯��
 **************************************/
template<class ITEM>
DiLinkList<ITEM>::DiLinkList(const DiLinkList<ITEM>& obj)
{
	*this = obj;
}
/***************************************
 * ��ֵ������
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
 * ���ݿ�ʼԪ��,������ʼ������
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::Iterator
DiLinkList<ITEM>::begin () const
{
	return Iterator((Self*)this, end_node(), first_node() );
}
/***************************************
 * �������һ��Ԫ��,������������
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::Iterator
DiLinkList<ITEM>::end() const
{
	return Iterator((Self*)this, this->end_node_->prev_, end_node() );
}
/***************************************
 * ����е�ĩβ����һ��Ԫ��,
 * �ɹ�ʱԪ�ظ��� ;ʧ��-1
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::append (const ITEM & item)
{
	return insert (end(), item);
}
/***************************************
 * �Ӷ����Ƴ���Ԫ��
 * �ɹ�Ϊ0ʧ��-1
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::remove (ITEM & item)
{
	if (this->end_node_->next_ && (this->end_node_->next_ != this->end_node_)) {
		item = ((ThrNode*)this->end_node_->next_)->item_;
		Iterator it = begin();
		erase (it); //ɾ����һ��Ԫ��
		return 0;
	}
	return -1;
}
/***************************************
 * ����в���һ��Ԫ��,������������������
 * �ɹ�ʱ���ؽڵ���;ʧ��ʱ����-1
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::insert (const Iterator& it, const ITEM & item)
{
	//������ڵ����
	NodePtr node = create_node ();
	((ThrNode*)node)->item_  = item;

	//���뵽��ǰλ�õĺ���,���it��end����뵽ǰ��
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
 * ���ݵ������Ӷ�����ɾ��һ��Ԫ��
 **************************************/
template<class ITEM>
int
DiLinkList<ITEM>::erase (Iterator& it)
{
	if (it.cur_node_ == this->end_node_)  //���һ���ڵ㲻��ɾ��
		return -1;
	/*�ͷŵ�ǰ�ڵ㲢���µ�ǰ�ڵ�Ϊ��һ���ڵ�*/
	it.prev_node_->next_ = it.cur_node_->next_;
	release_node(it.cur_node_);
	it.cur_node_ = it.prev_node_->next_;
	

	/*�����һ���ڵ�Ϊend_node�����end_node��ǰ��ָ��*/
	if (it.cur_node_ == this->end_node_) {
		this->end_node_->prev_ = it.prev_node_;
	}
	return --(this->cur_size_);
}
/***************************************
 * ���ݵ������Ӷ�����ɾ��һ��Ԫ��
 * �ɹ�ʱ����ʣ��ڵ���,ʧ��ʱ-1
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::erase (const Iterator& itbegin, const Iterator& itend)
{
	for (Iterator it = itbegin; it != itend; )
		erase(it);
}
/***************************************
 * ������нڵ�,ֻʣ��end_node_
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::clear ()
{
	erase (begin (), end());
}
/***************************************
 * �����Ƿ�Ϊ��
 **************************************/
template<class ITEM>
bool
DiLinkList<ITEM>::empty () const
{
	return this->cur_size_ == 0 ? true : false;
}
/***************************************
 * �����Ƿ�����
 **************************************/
template<class ITEM>
bool
DiLinkList<ITEM>::full () const
{
	return false;
}
/***************************************
 * ���ÿ��Ԫ��ִ�д��뺯������false����
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
 * ���ÿ��Ԫ���Դ��뺯���жϣ���true����
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
 * ����Ԫ�ظ���
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::size_type
DiLinkList<ITEM>::size () const
{
	return this->cur_size_;
}
/***************************************
 * ��ȡ��һ���ڵ�
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::NodePtr
DiLinkList<ITEM>::first_node() const
{
	return this->end_node_->next_;
}
/***************************************
 * ��ȡ���һ��Ԫ��
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::NodePtr
DiLinkList<ITEM>::end_node() const
{
	return this->end_node_;
}
/***************************************
 * ����һ���ڵ�
 * Ŀǰ����new��ʽ,�Ժ�ɿ��ǲ��ù�����
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::NodePtr
DiLinkList<ITEM>::create_node()
{
	return new ThrNode;
}
/***************************************
 * �ͷ�һ���ڵ�
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::release_node(typename DiLinkList<ITEM>::NodePtr node)
{
	delete node;
}
/***************************************
 * ���ص�ǰλ�������ʼλ�õľ���
 **************************************/
template<class ITEM>
typename DiLinkList<ITEM>::size_type
DiLinkList<ITEM>::distance(const Iterator & it) const
{
	size_type size  = 0;
	NodePtr node = first_node();
	for (;node != it.cur_node_; node = node->next_, size++);  //����sizeֱ����ǰ��node
	return size;
}
/***************************************
 * ��������ֵ,�ѵ�ǰλ����ǰ�ƶ�size��λ
 * ��������߽�,��ǰλ��Ϊend
 **************************************/
template<class ITEM>
void
DiLinkList<ITEM>::advance(Iterator& it, size_type size) const
{
	//��ǰ����,�����ܳ���end�ڵ�
	while (size-- > 0 && it.cur_node_ != end_node() ) {
		it.prev_node_ = it.cur_node_;
		it.cur_node_  = it.cur_node_->next_;
	}
}
#endif
