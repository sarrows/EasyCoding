
#pragma once

#include "config_platform.h"

namespace EasyCoding {

	class ECExport Interval
	{
	public:
		Interval(uint64 msec = 0);
		Interval(const Interval& obj) {
			miniseconds_ = obj.msec();
		}
		void settime(uint64 minisec) {
			miniseconds_ = minisec;
		}
		uint64 sec() const { return miniseconds_/1000; }
		uint64 msec() const { return miniseconds_; }
		int64 operator- (const Interval& obj) {
			int64 interval = miniseconds_ - obj.msec();
			miniseconds_ -= obj.msec();
			return interval;
		}
	private:
		uint64 miniseconds_;
	};

}
