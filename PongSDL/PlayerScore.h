#ifndef USE_VIEWSCORE
#define USE_VIEWSCORE
#include "GameObject.h"
#include "SDL_ttf.h"
class PlayerScore : public GameObject
{
public:
	
	void Init();
	void InitVisuals();
	void SetPos(Vector2 newPos);
	void operator++() {
		score++;
		UpdateTexture();
	}
	void operator++(int) {
		score++;
		UpdateTexture();
	}
	void operator=(int newScore) {
		score = newScore;
		UpdateTexture();
	}
protected:
	const int CHAR_WIDTH = 40;
	const int CHAR_HEIGHT = 72;
	int score;
	void Update();
	void UpdateTexture();
	TTF_Font* scoreFont;
};
#endif // !USE_VIEWSCORE
