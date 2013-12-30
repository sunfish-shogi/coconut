//
//  SharedBuffer.hpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/21.
//
//

#ifndef coconut_SharedBuffer_hpp
#define coconut_SharedBuffer_hpp

#include <memory>

namespace coconut {

	struct SharedBuffer {
	private:
		std::shared_ptr<char> _buffer;
		unsigned _size;
	public:
		explicit SharedBuffer(unsigned size) :
				_buffer(std::shared_ptr<char>(new char[size], std::default_delete<char[]>())),
				_size(size) {
		}
		explicit SharedBuffer(char* buffer, unsigned size) :
				_buffer(std::shared_ptr<char>(buffer, std::default_delete<char[]>())),
				_size(size) {
		}
		SharedBuffer(const SharedBuffer& src) :
				_buffer(src._buffer),
				_size(src._size) {
		}
		SharedBuffer() {
		}
		void init(unsigned size) {
			_buffer = std::shared_ptr<char>(new char[size], std::default_delete<char[]>());
			_size = size;
		}
		void init(char * buffer, unsigned size) {
			_buffer = std::shared_ptr<char>(buffer, std::default_delete<char[]>());
			_size = size;
		}
		void init(const SharedBuffer& src) {
			_buffer = src._buffer;
			_size = src._size;
		}
		char* buffer() {
			return _buffer.get();
		}
		const char* buffer() const {
			return _buffer.get();
		}
		unsigned size() const {
			return _size;
		}
	};

}

#endif
