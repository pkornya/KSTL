#pragma once

#ifndef LISTEXCEPTION_H
#define LISTEXCEPTION_H

#include <exception>

class ListException : public std::exception
{
public:
	ListException(const char* what_arg) :
		std::exception(what_arg) {}
	ListException(const char* what_arg, const int value) :
		std::exception(what_arg, value) {}
	~ListException() {}
};

#endif // !LISTEXCEPTION_H