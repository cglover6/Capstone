#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
//Player class

class Major {
private:
	int health;
	int lives;
	bool alive;
	int skill1;
	int skill2;
	int skill3;
	int boundx;
	int boundy;
	int x;
	int y;
	ALLEGRO_BITMAP* playerSprite;
	ALLEGRO_BITMAP* playerBack;


public:
	//Initialize Values
	Major();
	void ChooseMajor(int);
	void PlayerLocation(float passedx, float passedy);
	void compScience();
	void music();
	void nurse();
	void chemistry();
	void DrawPlayer()
	{
		al_draw_bitmap(playerSprite, x, y, 0);
	}

	//Runtime calls
	int getLives(Major& player)
	{
		return player.lives;
	}
	int getHealth(Major& player)
	{
		return player.health;
	}
	int getSpriteWidth(Major& player)
	{
		return al_get_bitmap_width(player.playerSprite);
	}
	int getSpriteHeight(Major& player)
	{
		return al_get_bitmap_height(player.playerSprite);
	}
	int getPlayerX(Major& player)
	{
		return x;
	}
	int getPlayerY(Major& player)
	{
		return y;
	}

	void drawPlayerBack(int x, int y);

};

Major::Major()
{
	health = 200;
	lives = 3;
	alive = true;
}

void Major::ChooseMajor(int selection)
{




}


void Major::PlayerLocation(float passedx, float passedy)
{
	x = passedx;
	y = passedy;
}

void Major::compScience()
{
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("hooper.jpg");
}

void Major::music()
{
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("hooper.jpg");
}

void Major::nurse()
{
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("nurse.jpg");
}

void Major::chemistry()
{
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("frontchemistrysprite.png");
	playerBack = al_load_bitmap("backchemistrysprite.png");
}

void Major::drawPlayerBack(int x, int y)
{
	al_draw_bitmap(playerBack, x, y, 0);
}


class Boss{
private:
	int health;
	int attack1;
	int attack2;
	int attack3;
	int x;
	int y;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* bossSprite;

public:
	void Basketball_Boss();
	void Football_Boss();
	void Final_Boss();
	void DrawBoss();
	void BossLocation();
	void GetHealth();
};


void Boss::Basketball_Boss()
{
	x = 640;
	y = 360;
	bossSprite = al_load_bitmap("basketballboss.png");
}

void Boss::Football_Boss()
{

}

void Boss::Final_Boss()
{



}

void Boss::DrawBoss()
{
	al_draw_bitmap(bossSprite, x, y, 0);
}

void Boss::BossLocation()
{


}

void Boss::GetHealth()
{



}

