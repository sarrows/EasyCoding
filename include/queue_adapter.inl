/*在末尾添加元素*/
template<class ITEM, class LIST>
int
QueueAdapter<ITEM, LIST>::enqueue(const ITEM item)
{
    int ret = 0;
    Mutex::Guard guard(&this->mutex_);
    if ( -1 != (ret = this->queue_.append (item)) )
        this->sem_.release();
    return ret;
}
/*取首元素*/
template<class ITEM, class LIST>
int
QueueAdapter<ITEM, LIST>::dequeue(ITEM & item, timeval* val)
{
    if (-1 == this->sem_.acquire(val))
        return -1;
    Mutex::Guard guard(&this->mutex_);
    return this->queue_.remove(item);
}
/*返回元素个数*/
template<class ITEM, class LIST>
typename QueueAdapter<ITEM, LIST>::size_type
QueueAdapter<ITEM, LIST>::size() const
{
    return this->queue_.size();
}
/*是否已满*/
template<class ITEM, class LIST>
bool
QueueAdapter<ITEM, LIST>::full() const
{
    return this->queue_.full();
}
/*是否为空*/
template<class ITEM, class LIST>
bool
QueueAdapter<ITEM, LIST>::empty() const
{
    return this->queue_.empty();
}
template<class ITEM, class LIST>
void
QueueAdapter<ITEM, LIST>::clear()
{
    Mutex::Guard guard(&this->mutex_);
    this->queue_.clear();
}
template<class ITEM, class LIST>
void QueueAdapter<ITEM, LIST>::close()
{
	this->sem_.release();
	XOS::sleep(50);
	this->sem_.close();
}
