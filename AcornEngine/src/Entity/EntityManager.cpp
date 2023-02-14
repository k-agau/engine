#include "Entity/EntityManager.h"

EntityManager* EntityManager::inst = nullptr;

EntityManager* EntityManager::instance()
{
	if (EntityManager::inst == nullptr)
	{
		inst = new EntityManager();
	}
	return inst;
}

EntityManager::~EntityManager()
{

}
