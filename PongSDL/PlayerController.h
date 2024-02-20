#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
class PlayerController : public GameObject
{
public:
	//things
	void Init(bool _playerNo);
	void MoveUp();
	void MoveDown();
protected:
	bool PlayerNo;
	void Update();

	void InitVisuals();
};

#endif // !USE_PLAYERCONTROLLER

