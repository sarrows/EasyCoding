/*
 * StreamBuffer make a size block buffer which is a loop buffer
 *
 * by liguoqiang
 *
 *
 */
#ifndef __STREAM_BUFFER_H__
#define __STREAM_BUFFER_H__

#include "config_platform.h"
#include <functional>

class StreamBuffer
{
public:	
	StreamBuffer(uint32 size = 10*1024)
		: _head(0), _tail(0), _length(0)
	{
		_buf_size = size;
		_buffer = new uchar[_buf_size];
	}
	StreamBuffer(const StreamBuffer& sb)
	{
		_head = sb._head;
		_tail = sb._tail;
		_length = sb._length;
		_buf_size = sb._buf_size;
		_buffer = new uchar[_buf_size];
		memcpy(_buffer, sb._buffer, _buf_size);
	}
	~StreamBuffer()
	{
		if(_buffer) {
			delete [] _buffer;
		}
	}

	int read(uchar* buf, uint32 len);
	int remove(uchar* buf, uint32 len);
	int append(uchar* buf, uint32 len);
	bool empty() const
	{
		return (_length == 0);
	}
	bool full() const
	{
		return (_length == _buf_size);
	}
	uint32 length() const
	{
		return _length;
	}
	
	uint32 total_size() const {
		return _buf_size;
	}

	uint32 remain_size() const;
	
	void clear()
	{
		this->_head = this->_tail = 0;
		_length = 0;
	}
	StreamBuffer & operator++ (void);      //前缀++
	StreamBuffer operator++ (int);         //后缀++
	uchar operator*(void);       //操作符函数
	void advance(uint32 len);
public:
	uint32  _buf_size;
	uint32  _head;
	uint32  _tail;
	uchar * _buffer;
	uint32  _length;
};

#include "stream_buffer.inl"

#endif
