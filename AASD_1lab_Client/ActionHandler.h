#pragma once
#include "Patient.h"

class ActionHandler
{

public:
	Patient GetPatient(std::string str)
	{
		if (str.length() == 0) return Patient();
		return Patient(str);
	}
	
};

