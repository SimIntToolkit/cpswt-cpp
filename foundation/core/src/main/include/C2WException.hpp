/*
 * C2WException.hpp
 *
 *  Created on: Jul 17, 2011
 *      Author: c2wt
 */

#ifndef C2WEXCEPTION_HPP_
#define C2WEXCEPTION_HPP_

#include <string>
#include <typeinfo>
#include <utility>

class C2WException : public std::exception {
private:
	std::string _message;

public:
	explicit C2WException( std::string message ) : _message(std::move( message )) { }
	~C2WException() noexcept override = default;

	const char *what() const noexcept override {
		return _message.c_str();
	}
};

#endif /* C2WEXCEPTION_HPP_ */
