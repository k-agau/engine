#ifndef ENTITY_EVENT_H
#define ENTITY_EVENT_H

#include "Event.h"

class EntityEvent : public Event
{
public:
	EntityEvent(int id) : uid(id){};
	int uid;
};

class ScaleEvent : public EntityEvent {

public:

	ScaleEvent(int id, const ENTITY_EVENT_MOD m) :
		EntityEvent(id),mod(m) {};
	ENTITY_EVENT_MOD getMod() const { return mod; }
	ENTITY_EVENT_MOD mod;


	

};
/*
class RotateEvent : public EntityEvent {

public:

	ScaleEvent(int id, const ENTITY_EVENT_MOD m) :
		EntityEvent(id), mod(m) {};
	ENTITY_EVENT_MOD getMod() const { return mod; }
	ENTITY_EVENT_MOD mod;




};*/
#endif // ENTITY_EVENT_H