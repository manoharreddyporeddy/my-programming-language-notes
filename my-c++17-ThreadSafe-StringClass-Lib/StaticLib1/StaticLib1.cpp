// StaticLib1.cpp

#include "StaticLib1.h"

#include "iostream"
#include "algorithm"
using namespace std;

namespace NsString {

	String::String() {
		lock_guard<mutex> gg(_mut1);

		_len = 0;
	}
	String::String(char const* s) {
		lock_guard<mutex> gg(_mut1);

		if (_buf) {
			delete[]_buf;
			_buf = NULL;
		}

		_len = strlen(s) + 1;
		_buf = new char[_len];
		strncpy_s(_buf, _len, s, _len - 1);
	}
	String::String(String const& s) {
		lock_guard<mutex> gg(_mut1);

		if (_buf) {
			delete[]_buf;
			_buf = NULL;
		}

		_len = s._len;
		_buf = new char[_len];
		strncpy_s(_buf, _len, s._buf, _len);
	}

	String& String::operator=(String& s) {
		lock_guard<mutex> gg(_mut1);

		if (_buf) {
			delete[]_buf;
			_buf = NULL;
		}

		_len = s._len;
		_buf = new char[_len];
		strncpy_s(_buf, _len, s._buf, _len);

		return *this;
	}

	String::String(String && s) {
		lock_guard<mutex> gg(_mut1);

		_len = s._len;
		s._len = 0;

		_buf = s._buf;
		s._buf = NULL;
	}
	String::~String() {
		lock_guard<mutex> gg(_mut1);

		if (_buf) {
			delete[] _buf;
			_buf = NULL;
		}
	}


	size_t String::size() {
		lock_guard<mutex> gg(_mut1);
		return _len;
	}


	int String::_compare(const char* p, const char* q, size_t n) {
		while (n--) {
			if (*p != *q) {
				return (*p - *q);
				// return (*p < *q) ? -1 : 1;
			}
			++p;
			++q;
		}
		return 0;
	}

	int String::compare(String const& q) {
		lock_guard<mutex> gg(_mut1);

		int diff = _compare(_buf, q._buf, min(_len - 1, q._len - 1));
		if (diff == 0) {
			if (_len < q._len) {
				// cout << "EQUAL, BUT LENS NOT EQUAL - <" << endl;
				return -1;
			}
			else if (_len > q._len) {
				// cout << "EQUAL, BUT LENS NOT EQUAL - >" << endl;
				return 1;
			}
		}
		return diff;
	}

	std::ostream& operator<<(std::ostream& os, String& obj) {
		lock_guard<mutex> gg(obj._mut1);

		if (obj._buf) {
			os << obj._buf;
		}
		return os;
	}

}
