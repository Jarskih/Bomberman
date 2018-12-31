#pragma once
#include "Helpers.h"

template <typename T>
class Service
{
private:
	static sp<T> m_instance;
	Service() {};
public:
	static void Set(sp<T> p_instance) { m_instance = p_instance; };
	static sp<T> Get() { return m_instance; };
};

template <typename T>
sp<T> Service<T>::m_instance = nullptr;
