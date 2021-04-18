#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
//Player class

class Major {
private:
	int health;
	int lives;
	bool alive;
	bool isNurse;
	int skill1;
	int skill2;
	int skill3;
	int x;
	int y;
	ALLEGRO_BITMAP* playerSprite;
	ALLEGRO_BITMAP* playerBack;
	ALLEGRO_BITMAP* skill1Sprite;
	ALLEGRO_BITMAP* skill2Sprite;
	ALLEGRO_BITMAP* skill3Sprite;
	ALLEGRO_FONT* skillFont;
	const char* skill1Text;
	const char* skill2Text;
	const char* skill3Text;


public:
	//Initialize Values
	Major();
	void PlayerLocation(float passedx, float passedy);
	void compScience();
	void music();
	void nurse();
	void chemistry();
	void DrawPlayer()
	{
		al_draw_bitmap(playerSprite, x, y, 0);
	}
	void DrawPlayerBattle()
	{
		al_draw_scaled_bitmap(playerSprite, 0, 0, getSpriteWidth(), getSpriteHeight(), 160, 220, 150, 150, 0);
	}


	void DrawSkill1()
	{
		al_draw_bitmap(skill1Sprite, 250, 470, 0);
	}

	void DrawSkill2()
	{
		al_draw_bitmap(skill2Sprite, 250, 565, 0);
	}

	void DrawSkill3()
	{
		al_draw_bitmap(skill3Sprite, 570, 470, 0);
	}

	void WriteSkill1()
	{
		al_draw_textf(skillFont, al_map_rgb(255, 255, 255), 20, 490, 0, skill1Text);
	}

	void WriteSkill2()
	{
		al_draw_textf(skillFont, al_map_rgb(255, 255, 255), 20, 580, 0, skill2Text);
	}

	void WriteSkill3()
	{
		al_draw_textf(skillFont, al_map_rgb(255, 255, 255), 340, 490, 0, skill3Text);
	}

	int getLives()
	{
		return lives;
	}
	void LoseLife()
	{
		lives--;
	}
	void setLives(int num)
	{
		lives = num;
	}
	int GetHealth()
	{
		return health;
	}

	void LoseHealth(int damage)
	{
		health -= damage;
		if (health <= 0)
		{
			health = 0;
		}
	}

	int getSpriteWidth()
	{
		return al_get_bitmap_width(playerSprite);
	}
	int getSpriteHeight()
	{
		return al_get_bitmap_height(playerSprite);
	}
	int getPlayerX()
	{
		return x;
	}
	int getPlayerY()
	{
		return y;
	}

	bool isAlive()
	{
		return alive;
	}

	int useSkill1()
	{
		return skill1;
	}

	int useSkill2()
	{
		if (isNurse)
		{
			health += 40;
			if (health >= 200)
			{
				health = 200;
			}
			return 0;
		}
		
		else
		{
			return skill2;
		}
	}

	int useSkill3()
	{
		return skill3;
	}
};

Major::Major()
{
	health = 200;
	lives = 3;
	alive = true;
}

void Major::PlayerLocation(float passedx, float passedy)
{
	x = passedx;
	y = passedy;
}

void Major::compScience()
{
	isNurse = false;
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("computersciencesprite.png");
	skill1Sprite = al_load_bitmap("computerscienceskill1.png");
	skill2Sprite = al_load_bitmap("computerscienceskill2.png");
	skill3Sprite = al_load_bitmap("computerscienceskill3.png");
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	skill1Text = "1) Papercut";
	skill2Text = "2) Glasses Reflect";
	skill3Text = "3) Hack";
}

void Major::music()
{
	isNurse = false;
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("musiciansprite.png");
	skill1Sprite = al_load_bitmap("musicskill1.png");
	skill2Sprite = al_load_bitmap("musicskill2.png");
	skill3Sprite = al_load_bitmap("musicskill3.png");
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	skill1Text = "1) Cymbal Clash";
	skill2Text = "2) Drum";
	skill3Text = "3) Guitar Slam";
}

void Major::nurse()
{
	isNurse = true;
	skill1 = 90;
	skill2 = 0;
	skill3 = 120;
	playerSprite = al_load_bitmap("nursesprite.png");
	skill1Sprite = al_load_bitmap("nurseskill1.png");
	skill2Sprite = al_load_bitmap("nurseskill2.png");
	skill3Sprite = al_load_bitmap("nurseskill3.png");
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	skill1Text = "1) Bandage Wrap";
	skill2Text = "2) Heal";
	skill3Text = "3) Shot";
}


void Major::chemistry()
{
	isNurse = false;
	skill1 = 90;
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("frontchemistrysprite.png");
	skill1Sprite = al_load_bitmap("chemistryskill1.png");
	skill2Sprite = al_load_bitmap("chemistryskill2.png");
	skill3Sprite = al_load_bitmap("chemistryskill3.png");
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	skill1Text = "1) Stink Bomb";
	skill2Text = "2) Acid";
	skill3Text = "3) Potion of Death";
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
	int getBossWidth();
	int getBossHeight();
	void Football_Boss();
	void Final_Boss();
	void DrawBoss();
	void DrawBattleBoss();
	int BossX();
	int BossY();
	int GetHealth();
	void LoseHealth(int);
	int UseAttack1();
};


void Boss::Basketball_Boss()
{
	health = 400;
	x = 440;
	y = 475;
	attack1 = 150;
	bossSprite = al_load_bitmap("basketballboss.png");
}

void Boss::Football_Boss()
{
	health = 600;
	x = 680;
	y = 80;
	attack1 = 120;
	bossSprite = al_load_bitmap("footballsprite.png");
}

void Boss::Final_Boss()
{
	health = 1000;
	x = 1000;
	y = 320;
	attack1 = 60;
	bossSprite = al_load_bitmap("bodybuildersprite.png");

}

int Boss::getBossWidth()
{
	return al_get_bitmap_width(bossSprite);
}

int Boss::getBossHeight()
{
	return al_get_bitmap_height(bossSprite);
}


void Boss::DrawBoss()
{
	al_draw_bitmap(bossSprite, x, y, 0);
}

void Boss::DrawBattleBoss()
{
	al_draw_scaled_bitmap(bossSprite, 0, 0, getBossWidth(),getBossHeight(), 350, 70, 140, 170, 0);
}

int Boss::BossX()
{
	return x;
}

int Boss::BossY()
{
	return y;
}

int Boss::GetHealth()
{
	return health;
}

void Boss::LoseHealth(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		health = 0;
	}
}

int Boss::UseAttack1()
{
	return attack1;
}