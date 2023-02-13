class Entity
{
protected:
	uint8_t type;
	std::string debugName;

	uint8_t x;
	uint8_t y;
	uint8_t z;
public:
	Entity();
	virtual ~Entity() {};

	void onCreate() = 0;
	void onDelete() = 0;
};