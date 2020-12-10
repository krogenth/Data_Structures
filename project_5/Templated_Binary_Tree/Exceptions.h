//Daniel Kelley
//File: Exceptions.h
//Date: 12/19/2019
//Purpose: To create customs exceptions that can be used

#pragma once
#include <exception>

class RetrieveOnEmptyException : public std::exception {

public:
	RetrieveOnEmptyException() throw() : exception("Retrieved on Empty", 1) {



	}

};

class RetrieveOnNULLException : public std::exception {

public:
	RetrieveOnNULLException() throw() : exception("Retrieved on NULL Pointer", 1) {



	}

};

class DuplicateKeyException : public std::exception {

public:
	DuplicateKeyException() throw() : exception("Duplicate Key", 1) {



	}

};

class OutOfMemoryException : public std::exception {

public:
	OutOfMemoryException() throw() : exception("Out of Memory", 1) {



	}

};