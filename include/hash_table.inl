/******************************************
 * HASH 表迭代器实现
 *****************************************/

/**********************************
 * 赋值操作符
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
 * 比较操作符,等式
 *********************************/
template<typename KEY, typename ITEM>
bool
HashIterator<KEY, ITEM>::operator == (const Self& obj) const
{
	return (this->cur_node_ == obj.cur_node_);
}
/**********************************
 * 比较操作符,不等式
 *********************************/
template<typename KEY, typename ITEM>
bool
HashIterator<KEY, ITEM>::operator != (const Self& obj) const
{
	return (this->cur_node_ != obj.cur_node_);
}
/**********************************
 * 递增操作符类似++x
 * 如果下一个节点为空则找下一个桶
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
 * 递增操作符,类似x++
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
 * 指针操作符
 *********************************/
template<typename KEY, typename ITEM>
typename HashIterator<KEY, ITEM>::ItemPtr
HashIterator<KEY, ITEM>::operator -> (void) const
{
	return &(this->cur_node_->item_);
}
/**********************************
 * *操作符
 *********************************/
template<typename KEY, typename ITEM>
typename HashIterator<KEY, ITEM>::ItemRef
HashIterator<KEY, ITEM>::operator * (void)
{
	return (this->cur_node_->item_);
}





/******************************************
 * HASH 表实现
 *****************************************/

/**********************************
 * 缺省构造函数
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::HashTable(size_type buckets)
: bucket_size_(buckets), elements_(0)
{
	init_buckets();
}
/**********************************
 * 拷贝构造函数
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::HashTable(const Self& obj)
: bucket_size_(obj.bucket_size_), elements_(0)
{
	init_buckets();
	/*向桶内添加传递对象的元素*/
	insert(obj.begin(), obj.end());
}
/**********************************
 * 析构函数
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>::~HashTable()
{
	unini_buckets();
}

/**********************************
 * 赋值操作符
 *********************************/
template<typename KEY, typename ITEM>
HashTable<KEY, ITEM>&
HashTable<KEY, ITEM>::operator = (const Self& obj)
{
	clear();    //先清空元素
	/*如果桶的总数不相等,则释放原来的桶数组,重新构造新桶数组*/
	if (bucket_size_ != obj.bucket_size_) {
		unini_buckets();
		bucket_size_ = obj.bucket_size_;
		init_buckets();
	}
	/*向桶内添加传递对象的元素*/
	insert(obj.begin(), obj.end());
	return *this;
}
/**********************************
 * 返回开始迭代器
 * 即第一个有元素桶的第一个元素
 * 如果没有任何元素则返回end迭代器
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
 * 返回最后一个迭代器
 * 最后迭代器用NULL表示
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::end () const
{
	return Iterator (end_node() );
}
/**********************************
 * 返回HASH表目前存放的元素总和
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::size () const
{
	return elements_;
}
/**********************************
 * 返回目前已经有内容的桶个数
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::bucket_count() const
{
	size_type sum = 0;
	/*计算有内容的桶*/
	for ( size_type n = 0; n < bucket_size_; n++) {
		if(buckets_[n]->bucket_nums_ > 0) {
			sum++;
		}
	}
	return sum;
}
/**********************************
 * 返回指定桶中元素的个数
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::bucket_elems(size_type bucket) const
{
	return buckets_[bucket % bucket_size_]->bucket_nums_;
}
/**********************************
 * 返回KEY所处桶的位置
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::bucket_pos(const Key& key) const
{
	size_type pos = get_key_num(key);
	return (pos % bucket_size_);
}
/**********************************
 * 根据KEY向对应的桶内添加元素
 * 为了插入的效率,每次都插入到首元素
 * 成功时返回当前元素,否则end_node
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
 * 向桶数组中连续插入元素
 * 成功时返回总数,否则-1
 *********************************/
template<typename KEY, typename ITEM>
void
HashTable<KEY, ITEM>::insert (const Iterator& first, const Iterator& last)
{
	for (Iterator it = first; it != last; it++)
		insert (it->key_, it->val_);
}
/**********************************
 * 根据KEY向对应的桶内添加元素
 * 如果没找到则返回创建
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
 * 根据KEY值查找桶中的元素
 * 首先根据KEY确定所处的桶
 * 再遍历桶中元素直到找到节点
 * 如果没找到则返回end
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
 * 根据KEY值查找桶中的元素
 * 如果没找到则创建之
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::Iterator
HashTable<KEY, ITEM>::operator [] (const Key& key) const
{
	return find(key);
}
/**********************************
 * 根据KEY从桶中删除一个元素
 * 删除方法和删除链表节点相似
 * 返回剩余的元素个数
 *********************************/
template<typename KEY, typename ITEM>
typename HashTable<KEY, ITEM>::size_type
HashTable<KEY, ITEM>::erase (const Key& key)
{
	size_type  pos  = bucket_pos(key);
	NodePtr node = buckets_[pos]->next_;
	NodePtr node_prev = buckets_[pos];

	//如果没有元素则直接返回
	if(buckets_[pos]->bucket_nums_ == 0) {
		return elements_;
	}
	
	/*循环比对KEY值相等的元素*/
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
 * 根据给定的迭代器删除对应位置的节点
 * 返回剩余的元素个数
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
 * 清空所有的元素
 *********************************/
template<typename KEY, typename ITEM>
void
HashTable<KEY, ITEM>::clear ()
{
	erase(begin(), end());
}

/**********************************
 * 初始化桶
 * 根据总数构造桶,并初始化它
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
 * uninitialize桶
 * 先清空桶中的元素,再释放桶
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

