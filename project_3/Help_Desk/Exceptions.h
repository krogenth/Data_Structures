#pragma once
#include <exception>

class empty_exception : public std::exception {

public:
	empty_exception() throw() : exception("empty exception", 1) {



	}

};

//Used to see if the list is empty:
class EmptyException : public std::exception {



};
