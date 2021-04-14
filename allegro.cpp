#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "characters.h"
#include "map.h"
using namespace std;


//Global Variables
int screenWidth = 640;
int screenHeight = 640;


int TitleScreen();
Major CharSelect();
void cameraUpdate(float* cameraPosition, float x, float y, int width, int height, bool collision);
bool BasketballCollisionDetection(Boss basketballBoss, float x, float y, int playerWidth, int playerHeight);
int BasketballBossBattle(Major player, Boss basketballBoss);

int main()
{
	
	//must initialize everything
	al_init();

	
	//create display, event queue, timer, and bitmap
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_TRANSFORM camera;
	

	display = al_create_display(screenWidth, screenHeight);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	
	//font things
	ALLEGRO_FONT* livesFont;
	livesFont = al_load_font("helloworld.ttf", 48, 0);


	//Checking if the user wants single player, co-op or to exit the game. This is the main screen.
	int selection = 0;
	selection = TitleScreen();
	
	//object variables
	Major player1;
	Major player2;

	if (selection == 1)
	{
		player1 = CharSelect();
	}
	if (selection == 2)
	{
		player1 = CharSelect();
		player2 = CharSelect();
	}
	if (selection == 3)
	{
		return 0;
	}

	Boss basketballBoss;
	basketballBoss.Basketball_Boss();

	Background mapScreen;
	mapScreen.MapBackground();

	

	int bitmap_width;
	int bitmap_height;

	bitmap_width = player1.getSpriteWidth();
	bitmap_height = player1.getSpriteHeight();

	

	bool running = true;
	float x = 640 / 2, y = 640 / 2;

	float cameraPosition[2] = { 0, 0 };

	bool redraw = true;
	bool collision = false;

//map loop
	if (running)
	{
		al_start_timer(timer);
			//game render loop
		while (running) {

			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				running = false;


			ALLEGRO_KEYBOARD_STATE keyState;
			al_get_keyboard_state(&keyState);


			if (event.type == ALLEGRO_EVENT_TIMER) {
				if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) { x += 3; }

				if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) { x -= 3; }

				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) { y += 3; }

				if (al_key_down(&keyState, ALLEGRO_KEY_UP)) { y -= 3; }

				collision = BasketballCollisionDetection(basketballBoss, x, y, bitmap_width, bitmap_height);
				cameraUpdate(cameraPosition, x, y, bitmap_width, bitmap_height, collision);

			

				al_identity_transform(&camera);
				al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
				al_use_transform(&camera);

				

			
				redraw = true;
			}

			if (x <= 0 - 18)
			{
				x = 0 - 18;
			}
			if (x >= 1280 - 46)
			{
				x = 1280 - 46;
			}
			if (y >= 640 - 64)
			{
				y = 640 - 64;
			}
			if (y <= 0)
			{
				y = 0;
			}

				if (redraw)
				{
					if (collision)
					{
						int lives = BasketballBossBattle(player1, basketballBoss);
						player1.setLives(lives);
					}

				
						redraw = false;
						mapScreen.drawMapBackground();

						basketballBoss.DrawBoss();
						player1.PlayerLocation(x, y);
						player1.DrawPlayer();
						al_draw_textf(livesFont, al_map_rgb(255, 255, 255), 10, 0, 0, "Lives: %i", player1.getLives());
						al_flip_display();			

				}	
			}
	}

	//destroy each thing created
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_timer(timer);


	return 0;
}

void cameraUpdate(float* cameraPosition, float x, float y, int playerWidth, int playerHeight, bool collision)
{
	cameraPosition[0] = -(screenWidth / 2) + (x + playerWidth / 2);
	cameraPosition[1] = -(screenHeight / 2) + (y + playerHeight / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;
	if (cameraPosition[0] > screenWidth)
		cameraPosition[0] = screenWidth;
	if (cameraPosition[1] > 0)
		cameraPosition[1] = 0;

	if (collision)
	{
		cameraPosition[0] = 0;
		cameraPosition[1] = 0;
	}
}


bool BasketballCollisionDetection(Boss basketBoss, float x, float y, int width, int height)
{
	bool collision;

	if (x + width < basketBoss.BossX() || x > basketBoss.BossX() + width || y + height < basketBoss.BossY() || y > basketBoss.BossY() + 72)
	{
		// No collision
		collision = false;
	}
	else
	{
		collision = true;
	}
	return collision;
}


int TitleScreen()
{
	//main menu
	ALLEGRO_BITMAP* mainScreen;
	mainScreen = al_load_bitmap("MENU.PNG");
	assert(mainScreen != NULL);


	int selection = 0;

	int mainScreen_Width = al_get_bitmap_width(mainScreen);
	int mainScreen_Height = al_get_bitmap_height(mainScreen);

	while (!selection) {
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		al_draw_scaled_bitmap(mainScreen, 0, 0, mainScreen_Width, mainScreen_Height, 0, 0, screenWidth, screenHeight, 0);
		al_flip_display();

		if (al_key_down(&keyState, ALLEGRO_KEY_1)) {selection = 1;}

		if (al_key_down(&keyState, ALLEGRO_KEY_2)) { selection = 2; }

		if (al_key_down(&keyState, ALLEGRO_KEY_3)) { selection = 3; }

	}

	al_destroy_bitmap(mainScreen);

	return selection;
}

Major CharSelect()
{

	ALLEGRO_EVENT_QUEUE* queue;
	queue = al_create_event_queue();

	al_register_event_source(queue, al_get_keyboard_event_source());
	
	ALLEGRO_FONT* font = al_load_font("helloworld.ttf", 24, 0);
	int choice = 0;

	while(!choice)
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_text(font, al_map_rgb(0, 0, 100), 375, 50, 0, "Select the character you would like to play as using 1-4.");
		
		
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		al_flip_display();

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			choice = false;

		if (al_key_down(&keyState, ALLEGRO_KEY_1)) { choice = 1; }

		if (al_key_down(&keyState, ALLEGRO_KEY_2)) { choice = 2; }

		if (al_key_down(&keyState, ALLEGRO_KEY_3)) { choice = 3; }

		if (al_key_down(&keyState, ALLEGRO_KEY_4)) { choice = 4; }
	}

	if (choice == 1)
	{
		Major player;
		player.compScience();

		return player;
	}

	else if(choice == 2)
	{
		Major player;
		player.music();

		return player;
	}

	else if (choice == 3)
	{
		Major player;
		player.nurse();

		return player;
	}

	else if (choice == 4)
	{
		Major player;
		player.chemistry();

		return player;
	}
}

int BasketballBossBattle(Major player, Boss basketballBoss)
{
	
	ALLEGRO_BITMAP* playerSprite;
	ALLEGRO_BITMAP* bossSprite;
	ALLEGRO_FONT* skills_font;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* FPS;

	Background basketballBattle;
	basketballBattle.BattleBackground();

	event_queue = al_create_event_queue();

	FPS = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(FPS));

	

	playerSprite = al_load_bitmap("frontchemistrysprite.png");
	bossSprite = al_load_bitmap("basketballboss.png");


	int bossHealth;




	bool running = true;

	al_start_timer(FPS);

	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			if (al_key_down(&keyState, ALLEGRO_KEY_1))
			{
				basketballBoss.LoseHealth(player.useSkill1());
				bossHealth = basketballBoss.GetHealth();
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_2))
			{
				basketballBoss.LoseHealth(player.useSkill2());
				bossHealth = basketballBoss.GetHealth();
			}

			if (al_key_down(&keyState, ALLEGRO_KEY_3))
			{
				basketballBoss.LoseHealth(player.useSkill3());
				bossHealth = basketballBoss.GetHealth();
			}


			if (al_key_down(&keyState, ALLEGRO_KEY_4))
			{
				return player.getLives();
			}

		}
			
		basketballBattle.drawBattleBackground();
		al_draw_scaled_bitmap(playerSprite, 0, 0, player.getSpriteWidth(),  player.getSpriteHeight(), 160, 220, 150, 150, 0);
		al_draw_scaled_bitmap(bossSprite, 0, 0, basketballBoss.getBossWidth(), basketballBoss.getBossHeight(), 350, 70, 140, 170, 0);
		player.DrawSkill2();
		player.DrawSkill3();
		al_flip_display();
	}

	return player.getLives();
}

