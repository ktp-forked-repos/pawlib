#ifndef __TEST_ACCESSOR_COMMON_H
#define __TEST_ACCESSOR_COMMON_H

#include "../unittestbase.h"

class TestAccessorObject
{
public:
	explicit TestAccessorObject(int value = 0) : n(value) {
	}

public:
	int n;
};

#endif
