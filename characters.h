#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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
	ALLEGRO_BITMAP* animation1;
	ALLEGRO_BITMAP* animation2;
	ALLEGRO_BITMAP* animation3;
	ALLEGRO_FONT* skillFont;
	ALLEGRO_SAMPLE* audio1 = NULL;
	ALLEGRO_SAMPLE* audio2 = NULL;
	ALLEGRO_SAMPLE* audio3 = NULL;
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

	void DrawAnimation1()
	{
		al_draw_scaled_bitmap(animation1, 0, 0, 64, 64, 160, 220, 150, 150, 0);
	}

	void DrawAnimation2()
	{
		al_draw_scaled_bitmap(animation2, 0, 0, 64, 64, 160, 220, 150, 150, 0);
	}

	void DrawAnimation3()
	{
		al_draw_scaled_bitmap(animation3, 0, 0, 64, 64, 160, 220, 150, 150, 0);
	}

	void PlayAudio1()
	{
		al_play_sample(audio1, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	}

	void PlayAudio2()
	{
		al_play_sample(audio2, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	}

	void PlayAudio3()
	{
		al_play_sample(audio3, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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
	skill1 = 900; 
	skill2 = 140;
	skill3 = 120;
	playerSprite = al_load_bitmap("computersciencesprite.png");
	skill1Sprite = al_load_bitmap("computerscienceskill1.png");
	skill2Sprite = al_load_bitmap("computerscienceskill2.png");
	skill3Sprite = al_load_bitmap("computerscienceskill3.png");
	animation1 = al_load_bitmap("computerscienceanimation1.png");
	animation2 = al_load_bitmap("computerscienceanimation2.png");
	animation3 = al_load_bitmap("computerscienceanimation3.png");
	audio1 = al_load_sample("computerscienceaudio1.wav");
	audio2 = al_load_sample("computerscienceaudio2.wav");
	audio3 = al_load_sample("computerscienceaudio3.wav");
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
	animation1 = al_load_bitmap("musicanimation1.png");
	animation2 = al_load_bitmap("musicanimation2.png");
	animation3 = al_load_bitmap("musicanimation3.png");
	audio1 = al_load_sample("musicianaudio1.wav");
	audio2 = al_load_sample("musicianaudio2.wav");
	audio3 = al_load_sample("musicianaudio3.wav");

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
	animation1 = al_load_bitmap("nurseanimation1.png");
	animation2 = al_load_bitmap("nurseanimation2.png");
	animation3 = al_load_bitmap("nurseanimation3.png");
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	audio1 = al_load_sample("nurseaudio1.wav");
	audio2 = al_load_sample("nurseaudio2.wav");
	audio3 = al_load_sample("nurseaudio3.wav");
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
	animation1 = al_load_bitmap("chemistryanimation1.png");
	animation2 = al_load_bitmap("chemistryanimation2.png");
	animation3 = al_load_bitmap("chemistryanimation3.png");
	audio1 = al_load_sample("chemistaudio1.wav");
	audio2 = al_load_sample("chemistaudio2.wav");
	audio3 = al_load_sample("chemistaudio3.wav");
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