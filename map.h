#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>

class Background {
private:
	ALLEGRO_BITMAP* background;

public:
	void grassBackground()
	{
		background = al_load_bitmap("grassbackground.png");
	}
	
	void drawBackground()
	{
		al_draw_bitmap(background, 0, 0, 0);
	}

};