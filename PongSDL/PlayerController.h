#ifndef USE_PLAYERCONTROLLER
#define USE_PLAYERCONTROLLER
#include "GameObject.h"
#include "PlayerScore.h"
class PlayerController : public GameObject
{
public:
	//things
	void Init();
	void SetPlayerNo(bool _playerNo);
	
	void Move(bool up);
	Vector2 GetSurfNormal();
	PlayerScore score;
protected:
	void MoveUp();
	void MoveDown();
	bool PlayerNo;
	void Update();

	void InitVisuals();
	
};

#endif // !USE_PLAYERCONTROLLER

