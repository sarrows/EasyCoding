inline uint32 StreamBuffer::remain_size() const
{
	return (total_size() - length());
}

/*
 * advance a length to new position
 *
 *
 */
inline void StreamBuffer::advance(uint32 len)
{
	if(_length >= len) {
		_head = (_head + len) % _buf_size;
		_length -= len;
	} else {
		_head = _tail;
		_length = 0;
	}
}

/*
 * read without removing from StreamBuff
 *
 *
 */
inline int StreamBuffer::read(uchar* buf, uint32 len)
{
	uint32 i = 0;
	uint32 size = 0;
	uint32 old_head = _head;
	if(length() < len) {
		return -1;
	}
	for(i = 0; i < len; i += size) {
		size = (old_head >= _tail ? _buf_size - old_head : _tail - old_head);
		if(size > len) {
			size = len;
		}
		memcpy(buf + i, _buffer + old_head, size);
		old_head = (old_head + size) % _buf_size;
	}
	
	return 0;
}

/*
 * read and remove from StreamBuff
 *
 *
 */
inline int StreamBuffer::remove(uchar * buf, uint32 len)
{
	uint32 i = 0;
	uint32 size = 0;
	uint32 needlen = 0;
	
	if(length() < len) {
		return -1;
	}
	needlen = len;
	for(i = 0; i < len; i += size) {
		size = (_head >= _tail ? _buf_size - _head : _tail - _head);
		if(size > needlen) {
			size = needlen;
		}
		memcpy(buf + i, _buffer + _head, size);
		_head = (_head + size) % _buf_size;
		_length -= size;
		needlen -= size;
	}
	return 0;
}

inline int StreamBuffer::append(uchar* buf, uint32 len)
{
	uint32 i = 0;
	uint32 size = 0;
	uint32 needlen = 0;
	if(remain_size() < len || full()) {
		return -1;
	}
	needlen = len;
	for(i = 0; i < len && !full(); i += size) {
		size = (_tail >= _head ? _buf_size - _tail : _head - _tail);
		if(size > needlen) {
			size = needlen;
		}
		memcpy(_buffer + _tail, buf + i, size);
		_tail = (_tail + size) % _buf_size;
		_length += size;
		needlen -= size;
	}
	return 0;
}

inline StreamBuffer & StreamBuffer::operator++ (void)      //前缀++
{
	_head = ++_head % _buf_size;
	_length--;
	return *this;
}

inline StreamBuffer StreamBuffer::operator++ (int)         //后缀++
{
	StreamBuffer temp = *this;
	_head = ++_head % _buf_size;
	_length--;
	return temp;
}

inline uchar StreamBuffer::operator*(void)       //操作符函数
{
	return *(_buffer + _head % _buf_size);
}

