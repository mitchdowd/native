// Local Dependencies
#include "../include/exception.h"
#include "../include/mutex.h"

namespace native
{
	Mutex::Mutex()
	{
		throw NotImplementedException();
	}

	Mutex::Mutex(const String& name)
	{
		throw NotImplementedException();
	}

	Mutex::~Mutex()
	{
	}

	void Mutex::lock()
	{
		throw NotImplementedException();
	}

	bool Mutex::tryLock()
	{
		throw NotImplementedException();
	}

	void Mutex::release()
	{
		throw NotImplementedException();
	}
}

