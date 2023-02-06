/*#include "Camera.h"
#include <map>
#include <list>
#include <functional>
#include "GLFW/glfw3.h"
#include "AcornEngine.cpp"

class InputHandler {
public:

	InputHandler();

	void handleInput(GLFWwindow* window);


private:

	const enum CONTEXTS {
		CNTXT_1,
		CNTXT_2,
		CNTXT_3,
	};
	
	
	std::map<int, Handler> default_cntxt1_mappings;
	std::map<int, Handler> default_cntxt2_mappings;
	std::list<void(*)()> exectueList;





};

struct Handler
{
    template <typename T>
    Handler(T fn)
        : f((void(*)())(fn))
        , info(typeid(T))
    {
    }

    template <typename... Args>
    void operator()(Args&&... args)
    {
        using Fn = void(Args...);
        assert(info.hash_code() == typeid(Fn*).hash_code());
        return ((Fn*)(f))(std::forward<Args>(args)...);
    }
    void (*f)();
    const std::type_info& info;
};*/