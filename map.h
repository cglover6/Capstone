#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>

class Background {
private:
	ALLEGRO_BITMAP* mapBackground;
	ALLEGRO_BITMAP* battleBackground;

public:
	void MapBackground()
	{
		mapBackground = al_load_bitmap("grassbackground.png");
	}
	
	void drawMapBackground()
	{
		al_draw_bitmap(mapBackground, 0, 0, 0);
	}
	
	void BattleBackground()
	{
		battleBackground = al_load_bitmap("battleBackground.png");
	}

	void drawBattleBackground()
	{
		al_draw_bitmap(battleBackground, 0, 0, 0);
	}
};