#ifndef USE_PONGBALL
#define USE_PONGBALL
#include "GameObject.h"
class PongBall : public GameObject
{
public:
	void Init();
	void NewBall();
protected:
	
	void Update();
	void MoveVisuals();
	int lifetime;
	void InitVisuals();
	void CheckCollision();

	void BounceBat();

	void Bounce();
	
};


#endif // !USE_PONGBALL
