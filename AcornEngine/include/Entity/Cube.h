#ifndef CUBE_H
#define CUBE_H

#include "Entity/Entity_Impl.h"

class Cube : public EntityImpl
{
private:
	uint8_t CUBE_TYPE;
public:
	Cube(std::string _debugName, uint8_t _x, uint8_t _y, uint8_t _z);
	virtual ~Cube();
	void onCreate() override;
	void onDelete() override;
	void onUpdate() override;
	void onEvent(Event& event) override;
};

#endif // CUBE_H