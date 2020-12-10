#pragma once
#include <exception>

class empty_exception : public std::exception {

public:
	empty_exception() throw() : exception("empty exception", 1) {



	}

};