#pragma once
#include "pch.h"
class base_progress
{
private:
	int status;
public:
	virtual int excute() = 0; 
	base_progress();
	~base_progress();
};

