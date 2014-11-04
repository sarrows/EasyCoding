/******************************************
 * author: ���ǿ
 * date: 2005-8-12
 * desc: ʵ�ֶ��м�����������ģ�庯��
 * ��include��loop_list.h�ļ���
 *****************************************/



/*******************************************
 *��ֵ����������
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
 * ����������������ǰ׺++������
 ****************************************/
template<class ITEM>
LoopListIterator<ITEM> &
LoopListIterator<ITEM>::operator++ (void)
{
	this->index_ = ++this->index_ % ((ListPtr)this->list_ptr_)->max_size_;
	return *this;
}
/******************************************
 * ������������׺++
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
 * ��ʽ�ȽϺ���
 ********************************************/
template<class ITEM>
bool
LoopListIterator<ITEM>::operator == (const LoopListIterator& obj) const
{
	return (this->index_ == obj.index_);
}
/******************************************
 * ����ʽ�ȽϺ���
 ********************************************/
template<class ITEM>
bool
LoopListIterator<ITEM>::operator != (const LoopListIterator& obj) const
{
	return (this->index_ != obj.index_);
}
/******************************************
 * ָ�������
 * Ϊ��Ч�ʲ����б߽���
 ********************************************/
template<class ITEM>
ITEM*
LoopListIterator<ITEM>::operator-> (void) const
{
	return &(((ListPtr)this->list_ptr_)->elements_[this->index_].item_);
}
/******************************************
 * *�Ų�����
 * Ϊ��Ч�ʲ����б߽���
 ********************************************/
template<class ITEM>
ITEM&
LoopListIterator<ITEM>::operator*(void)
{
	return ((ListPtr)this->list_ptr_)->elements_[this->index_].item_;
}






/******************************************************
 * LoopList��, ���캯��
 *****************************************************/

template<class ITEM>
LoopList<ITEM>::LoopList(ulong bound)
: max_size_(bound), head_pos_(0), tail_pos_(0)
{
	create_buffer();
}
/**************************************
 *�������캯��
 *************************************/
template<class ITEM>
LoopList<ITEM>::LoopList(const LoopList<ITEM>& obj)
{
	*this = obj;
}
/**************************************
 *�����������ͷ���Դ
 *************************************/
template<class ITEM>
LoopList<ITEM>::~LoopList()
{
	release_buffer();
}
/**************************************
 *��ֵ������
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
 *���ӣ������ĩβ���һ��Ԫ��
 *�ɹ�ʱ����0�����򷵻أ�1
 ************************************/
template<class ITEM>
int
LoopList<ITEM>::append (const ITEM& obj)
{
	if ( !full() ) {  //����δ�����������Ԫ��
		Node node;
		node.item_ = obj;
		this->elements_[this->tail_pos_ % this->max_size_] = node;
		this->tail_pos_ = ++this->tail_pos_ % this->max_size_;
		return 0;
	}
	return -1;
}
/*************************************
 *�Ƴ�Ԫ�أ��Ѷ�����Ԫ�شӶ������Ƴ�
 *�ɹ�ʱ����0�����򷵻أ�1
 ************************************/
template<class ITEM>
int
LoopList<ITEM>::remove (ITEM & obj)
{
	if ( !empty() ) { //����Ϊ��ʱ���޷��Ƴ���Ԫ��
		obj = this->elements_[this->head_pos_ % this->max_size_].item_;
		this->head_pos_ = ++this->head_pos_ % this->max_size_;
		return 0;
	}
	return -1;
}
/*************************************
 *�ж��Ƿ�Ϊ�գ�������������������ж�
 ************************************/
template<class ITEM>
bool
LoopList<ITEM>::empty () const
{
	return (this->head_pos_ == this->tail_pos_);
}
/*************************************
 *�ж��Ƿ�������������������������ж�
 ************************************/
template<class ITEM>
bool
LoopList<ITEM>::full () const
{
	return (this->head_pos_ - this->tail_pos_ + this->max_size_) % this->max_size_ == 1;
}
/*************************************
 * ��ն���
 ************************************/
template<class ITEM>
void
LoopList<ITEM>::clear()
{
	this->head_pos_ = this->tail_pos_ = 0;   //������ʼ����ֹ���ʾ���
}
/*************************************
 *���ض��е�ǰԪ�صĸ���
 ************************************/
template<class ITEM>
typename LoopList<ITEM>::size_type
LoopList<ITEM>::size () const
{
	return ((this->tail_pos_ - this->head_pos_ + this->max_size_ ) % this->max_size_);
}
/*************************************
 *���ݶ��е�һ��Ԫ�ص�λ�ã����ض�Ӧ�ĵ�����
 ************************************/
template<class ITEM>
typename LoopList<ITEM>::Iterator
LoopList<ITEM>::begin () const
{
	return Iterator((Self*)this, this->head_pos_);
}
/*************************************
 *���ݶ��е�һ��Ԫ�ص�λ�ã����ض�Ӧ�ĵ�����
 ************************************/
template<class ITEM>
typename LoopList<ITEM>::Iterator
LoopList<ITEM>::end () const
{
	return Iterator((Self*)this, this->tail_pos_);
}
/******************************************
 * ��ȡ��ǰλ�õ���ʼ���ľ���
 ********************************************/
template<class ITEM>
typename LoopList<ITEM>::size_type
LoopList<ITEM>::distance (const Iterator& it) const
{
	return ((it.index_ % this->max_size_) - this->head_pos_ + this->max_size_) % this->max_size_;
}
/******************************************
 * ��ǰ�ƶ�ָ��size��λ��
 ********************************************/
template<class ITEM>
void
LoopList<ITEM>::advance (Iterator& it, size_type size) const
{
	it.index_ = (it.index_ + size) % this->max_size_;
}
