/******************************************
 * HASH �������ʵ��
 *****************************************/

/**********************************
 * ��ֵ������
 *********************************/
template<typename KEY, typename ITEM>
HashIterator<KEY, ITEM>&
HashIterator<KEY, ITEM>::operator = (const Self& obj)
{
	if (this != &obj) {
		this->cur_node_   = obj.cur_node_;
	}
	return *this;
}
/**********************************
 * �Ƚϲ�����,��ʽ
 *********************************/
template<typename KEY, typename ITEM>
bool
HashIterator<KEY, ITEM>::operator == (const Self& obj) const
{
	return (this->cur_node_ == obj.cur_node_);
}
/**********************************
 * �Ƚϲ�����,����ʽ
 *********************************/
template<typename KEY, typename ITEM>
bool
HashIterator<KEY, ITEM>::operator != (const Self& obj) const
{
	return (this->cur_node_ != obj.cur_node_);
}
/**********************************
 * ��������������++x
 * �����һ���ڵ�Ϊ��������һ��Ͱ
 *********************************/
template<typename KEY, typename ITEM>
HashIterator<KEY, ITEM>&
HashIterator<KEY, ITEM>::operator ++ (void)
{
	if (this->cur_node_) {
		do {
			this->cur_node_ = this->cur_node_->next_;
		}while(this->cur_node_ && (this->cur_node_->bucket_top_ == 1));
	}
	return *this;
}
/**********************************
 * ����������,����x++
 *********************************/
template<typename KEY, typename ITEM>
HashIterator<KEY, ITEM>
HashIterator<KEY, ITEM>::operator ++ (int)
{
	Self tmp = *this;
	operator ++ ();
	return tmp;
}
/**********************************
 * ָ�������
 *********************************/
template<typename KEY, typename ITEM>
typename HashIterator<KEY, ITEM>::ItemPtr
HashIterator<KEY, ITEM>::operator -> (void) const
{
	return &(this->cur_node_->item_);
}
/**********************************
 * *������
 *********************************/
template<typename KEY, typename ITEM>
typename HashIterator<KEY, ITEM>::ItemRef
HashIterator<KEY, ITEM>::operator * (void)
{
	return (this->cur_node_->item_);
}





/******************************************
 * HASH ��ʵ��
 *****************************************/

/**********************************
 * ȱʡ���캯��
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::HashTable(size_type buckets)
: bucket_size_(buckets), elements_(0)
{
	init_buckets();
}
/**********************************
 * �������캯��
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::HashTable(const Self& obj)
: bucket_size_(obj.bucket_size_), elements_(0)
{
	init_buckets();
	/*��Ͱ����Ӵ��ݶ����Ԫ��*/
	insert(obj.begin(), obj.end());
}
/**********************************
 * ��������
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::~HashTable()
{
	unini_buckets();
}

/**********************************
 * ��ֵ������
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>&
HashTable<KEY, ITEM>::operator = (const Self& obj)
{
	clear();    //�����Ԫ��
	/*���Ͱ�����������,���ͷ�ԭ����Ͱ����,���¹�����Ͱ����*/
	if (bucket_size_ != obj.bucket_size_) {
		unini_buckets();
		bucket_size_ = obj.bucket_size_;
		init_buckets();
	}
	/*��Ͱ����Ӵ��ݶ����Ԫ��*/
	insert(obj.begin(), obj.end());
	return *this;
}
/**********************************
 * ���ؿ�ʼ������
 * ����һ����Ԫ��Ͱ�ĵ�һ��Ԫ��
 * ���û���κ�Ԫ���򷵻�end������
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::begin (size_type pos) const
{
	NodePtr node = 0;
	if (pos == size_npos) {
		for (pos = 0; pos < bucket_size_; pos++) {
			if (buckets_[pos]->bucket_nums_ > 0) {
				node = buckets_[pos]->next_;
				break;
			}
		}
	}
	
	return Iterator(node);
}
/**********************************
 * �������һ��������
 * ����������NULL��ʾ
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::end () const
{
	return Iterator (end_node() );
}
/**********************************
 * ����HASH��Ŀǰ��ŵ�Ԫ���ܺ�
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::size () const
{
	return elements_;
}
/**********************************
 * ����Ŀǰ�Ѿ������ݵ�Ͱ����
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::bucket_count() const
{
	size_type sum = 0;
	/*���������ݵ�Ͱ*/
	for ( size_type n = 0; n < bucket_size_; n++) {
		if(buckets_[n]->bucket_nums_ > 0) {
			sum++;
		}
	}
	return sum;
}
/**********************************
 * ����ָ��Ͱ��Ԫ�صĸ���
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::bucket_elems(size_type bucket) const
{
	return buckets_[bucket % bucket_size_]->bucket_nums_;
}
/**********************************
 * ����KEY����Ͱ��λ��
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::bucket_pos(const Key& key) const
{
	size_type pos = get_key_num(key);
	return (pos % bucket_size_);
}
/**********************************
 * ����KEY���Ӧ��Ͱ�����Ԫ��
 * Ϊ�˲����Ч��,ÿ�ζ����뵽��Ԫ��
 * �ɹ�ʱ���ص�ǰԪ��,����end_node
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::insert (const Key& key, const Value& val)
{
	size_type  pos  = bucket_pos(key);
	NodePtr node = 0;
	
	node = create_node();
	node->item_.key_  = key;
	node->item_.val_  = val;
	node->next_ = 0;
	
	node->next_ = buckets_[pos]->next_;
	buckets_[pos]->next_ = node;
	buckets_[pos]->bucket_nums_++;
	
	return Iterator(node);
}
/**********************************
 * ��Ͱ��������������Ԫ��
 * �ɹ�ʱ��������,����-1
 *********************************/
template<typename KEY, typename ITEM>
void
HashTable<KEY, ITEM>::insert (const Iterator& first, const Iterator& last)
{
	for (Iterator it = first; it != last; it++)
		insert (it->key_, it->val_);
}
/**********************************
 * ����KEY���Ӧ��Ͱ�����Ԫ��
 * ���û�ҵ��򷵻ش���
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::insert_with_replace (const Key& key, const Value& val)
{
	Iterator it = find(key);
	if (it->is_end()) it = insert(key, val);
	else *it = val;
}
/**********************************
 * ����KEYֵ����Ͱ�е�Ԫ��
 * ���ȸ���KEYȷ��������Ͱ
 * �ٱ���Ͱ��Ԫ��ֱ���ҵ��ڵ�
 * ���û�ҵ��򷵻�end
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::find (const Key& key) const
{
	size_type  pos  = bucket_pos(key);
	NodePtr node = buckets_[pos];
	if(buckets_[pos]->bucket_nums_ == 0) {
		return Iterator(end_node());
	}

	int find = 0;
	node = buckets_[pos]->next_;
	
	for (uint i = 0;
		node != end_node() && i < buckets_[pos]->bucket_nums_;
		node = node->next_, i++) {
		if (node->item_.key_ == key) {
			find = 1;
			break;
		}
	}

	if(!find) {
		node = end_node();
	}
	
	return Iterator(node);
}
/**********************************
 * ����KEYֵ����Ͱ�е�Ԫ��
 * ���û�ҵ��򴴽�֮
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::operator [] (const Key& key) const
{
	return find(key);
}
/**********************************
 * ����KEY��Ͱ��ɾ��һ��Ԫ��
 * ɾ��������ɾ������ڵ�����
 * ����ʣ���Ԫ�ظ���
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::erase (const Key& key)
{
	size_type  pos  = bucket_pos(key);
	NodePtr node = buckets_[pos]->next_;
	NodePtr node_prev = buckets_[pos];

	//���û��Ԫ����ֱ�ӷ���
	if(buckets_[pos]->bucket_nums_ == 0) {
		return elements_;
	}
	
	/*ѭ���ȶ�KEYֵ��ȵ�Ԫ��*/
	for (uint i = 0;
		node != end_node() && i < buckets_[pos]->bucket_nums_;
		node = node_prev->next_, i++ ) {
		
		if (node->item_.key_ == key && node->bucket_top_ == 0) {
			node_prev->next_ = node->next_;
			release_node (node);
			buckets_[pos]->bucket_nums_--;
			break;
		}
		node_prev = node;
	}
	return elements_;
}
/**********************************
 * ���ݸ����ĵ�����ɾ����Ӧλ�õĽڵ�
 * ����ʣ���Ԫ�ظ���
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::erase (Iterator it)
{
	return erase(it->key_);
}

template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::erase (Iterator it1, Iterator it2)
{
	for (; it1 != it2; ) {
		erase(it1++);
	}
	return elements_;
}

/**********************************
 * ������е�Ԫ��
 *********************************/
template<typename KEY, typename ITEM>
void
HashTable<KEY, ITEM>::clear ()
{
	erase(begin(), end());
}

/**********************************
 * ��ʼ��Ͱ
 * ������������Ͱ,����ʼ����
 *********************************/
template<typename KEY, typename ITEM>
void
HashTable<KEY, ITEM>::init_buckets()
{
	uint i;
	buckets_ = new NodePtr[bucket_size_];
	
	buckets_[0] = new ThrNode;
	buckets_[0]->bucket_top_ = 1;
	buckets_[0]->bucket_nums_ = 0;
	buckets_[0]->next_ = 0;
	
	for(i = 1; i < bucket_size_; i++) {
		buckets_[i] = new ThrNode;
		buckets_[i]->bucket_top_ = 1;
		buckets_[i]->bucket_nums_ = 0;
		buckets_[i]->next_ = 0;
		buckets_[i-1]->next_ = buckets_[i];
	}

	elements_ = 0;
}
/**********************************
 * uninitializeͰ
 * �����Ͱ�е�Ԫ��,���ͷ�Ͱ
 *********************************/
template<typename KEY, typename ITEM>
void
HashTable<KEY, ITEM>::unini_buckets()
{
	clear();
	for(uint i = 0; i < bucket_size_; i++) {
		delete buckets_[i];
	}
	delete [] buckets_;
}

