#ifndef USE_PONGBALL
#define USE_PONGBALL
#include "GameObject.h"
#include "PlayerController.h"
class PongBall : public GameObject
{
public:
	void Init();
	void NewBall(bool ServerPlayer);
	void MovePlayer(bool player, bool up);
	void ResetGame();
protected:
	
	void Update();
	int lifetime;
	void InitVisuals();
	void CheckCollision();

	bool TryCollide(PlayerController* player);

	void BounceBat();
	PlayerController* player0;
	PlayerController* player1;
	void Bounce(Vector2 SurfaceNormal);
	
};


#endif // !USE_PONGBALL
