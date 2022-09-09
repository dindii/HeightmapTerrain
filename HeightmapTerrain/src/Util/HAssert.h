#pragma once
#include <iostream>

//We will not worry about performance since it is just an assert and it is not meant to be called every frame or so. With this in mind, let's have some flexibility.
#define HT_ASSERT(Expr, Msg) \
    HAssert(Expr, __FILE__, __LINE__, Msg)

inline void HAssert(bool expression, const char* file, int line, const char* msg)
{
	if (!expression)
	{
		//I will use std::cout with std::endl here because I want the assert message to be immediate. 
		std::cout << "Assert failed: " << msg << "\n" << "Source: " << file << ", line " << line << "\n" << std::endl;
		__debugbreak();
	}
}