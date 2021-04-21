#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "characters.h"
#include "map.h"
using namespace std;


//Global Variables
int screenWidth = 640;
int screenHeight = 640;

//function prototypes
int TitleScreen();
Major CharSelect();
void LoadScreen();
void cameraUpdate(float* cameraPosition, float x, float y, int width, int height, bool basketballCollision, bool footballCollision, bool finalCollision, Boss footballBoss, Boss basketballBoss);
bool BasketballCollisionDetection(Boss basketballBoss, float x, float y, int playerWidth, int playerHeight);
bool FootballCollisionDetection(Boss footballBoss, float x, float y, int width, int height);
bool FinalCollisionDetection(Boss finalBoss, float player1_x, float player1_y, int bitmap_width, int bitmap_height);
int BasketballBossBattle(Major player, Boss basketballBoss, float &x, float &y);
int FootballBossBattle(Major player, Boss footballBoss, float& x, float& y);
int FinalBossBattle(Major player, Boss finalBoss, float& x, float& y);

int main()
{
	
	//must initialize allegro to use any library functions
	al_init();

	
	//create pointer to display, event queue, timer, font and variable for a transformation - camera
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* livesFont;
	ALLEGRO_TRANSFORM camera;	
	ALLEGRO_SAMPLE* worldMusic = NULL;
	ALLEGRO_SAMPLE* battleMusic = NULL;
	ALLEGRO_SAMPLE_INSTANCE* battleInstance = NULL;
	ALLEGRO_SAMPLE_INSTANCE* songInstance = NULL;


	
	//initialize display, queue, timer, and font pointers
	display = al_create_display(screenWidth, screenHeight);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	
	//must initialize everything before it is used
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	

	//queue is first in first out, this tells the computer where the event queue will be taking events from, and events are just when any state is changed such as a timer ticks or a key is pressed or released
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	
	livesFont = al_load_font("helloworld.ttf", 48, 0);


	//Function checking if the user wants single player, co-op or to exit the game. This is the main screen/first screen.
	int selection = 0;
	selection = TitleScreen();
	
	//object variables
	Major player1;
	Major player2;

	//main menu selection
	//if user chooses 1 the function returns 1 which is for 1 player
	if (selection == 1)
	{
		player1 = CharSelect();
	}
	//if user chooses 2 the function returns 2 which is for 2 player
	if (selection == 2)
	{
		player1 = CharSelect();
		player2 = CharSelect();
	}
	//if user chooses 3 it is then closed
	if (selection == 3)
	{
		return 0;
	}


	//intialize the bosses
	Boss basketballBoss;
	basketballBoss.Basketball_Boss();

	Boss footballBoss;
	footballBoss.Football_Boss();

	Boss finalBoss;
	finalBoss.Final_Boss();

	//initialize the overworld screen
	Background mapScreen;
	mapScreen.MapBackground();
	 
	//define int values for length and width of player sprite
	int bitmap_width;
	int bitmap_height;
	//initialize ints for player width and height
	bitmap_width = player1.getSpriteWidth();
	bitmap_height = player1.getSpriteHeight();

	
	//initialize running which is the condition statement for the overworld rendor loop
	bool running = true;
	//initialize where both players will start at when they first start the game
	float player1_x = 30, player1_y = 340;
	float player2_x = 80, player2_y = 340;

	//float values that hold the x and y for camera coordinates
	float cameraPosition[2] = { 0, 0 };

	//initialize redraw which is a condition in a later if statement
	bool redraw = true;
	//checks collision between player and all three bosses, initialized at false because player isn't near boss
	bool basketballCollision = false;
	bool footballCollision = false;
	bool finalCollision = false;

	al_reserve_samples(20);

	worldMusic = al_load_sample("worldsong.wav");
	battleMusic = al_load_sample("battlesong.wav");

	songInstance = al_create_sample_instance(worldMusic);
	battleInstance = al_create_sample_instance(battleMusic);
	
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(battleInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(battleInstance, al_get_default_mixer());

//map loop
	//overworld for single player mode
	if (selection == 1)
	{
		
		// Playing main backgroud music
		al_play_sample_instance(songInstance);

		//timer must be started or no movement will happen since we want our player to move in 60 fps
		al_start_timer(timer);

		//overworld render loop
		while (running) {

			//if the display is closed close the game, doesn't automatically happen must be programmed in which is cool to note
			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				running = false;

			//checking variable called keyState polls the keyboard
			ALLEGRO_KEYBOARD_STATE keyState;
			al_get_keyboard_state(&keyState);

			//game movement works with arrow keys
			if (event.type == ALLEGRO_EVENT_TIMER) {
				if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) { player1_x += 3; }

				if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) { player1_x -= 3; }

				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) { player1_y += 3; }

				if (al_key_down(&keyState, ALLEGRO_KEY_UP)) { player1_y -= 3; }

				//these functions return true or false if there is collision between the player and any of the bosses
				basketballCollision = BasketballCollisionDetection(basketballBoss, player1_x, player1_y, bitmap_width, bitmap_height);
				footballCollision = FootballCollisionDetection(footballBoss, player1_x, player1_y, bitmap_width, bitmap_height);
				finalCollision = FinalCollisionDetection(finalBoss, player1_x, player1_y, bitmap_width, bitmap_height);
				//This sets the camera to move with the player 
				cameraUpdate(cameraPosition, player1_x, player1_y, bitmap_width, bitmap_height, basketballCollision, footballCollision, finalCollision, footballBoss, basketballBoss);
				al_identity_transform(&camera);
				al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
				al_use_transform(&camera);

				//redraw is set to true so whenever redraw is true our if statement will enter, 
				//this has to do with making sure our player and camera move properly. 
				//This deal with the queue, so if it is currently busy doing this then nothing in the if statement coming up will be drawn so there is no lag with the player movement. 
				//This just makes the game run smoother making sure it doesn't get two events at the same time and if it does how to deal with it.
				redraw = true;
			}

			//sets the map bounds so the player can not go off the screen
			if (player1_x <= 0 - 18)
			{
				player1_x = 0 - 18;
			}
			if (player1_x >= 1280 - 46)
			{
				player1_x = 1280 - 46;
			}
			if (player1_y >= 640 - 64)
			{
				player1_y = 640 - 64;
			}
			if (player1_y <= 0)
			{
				player1_y = 0;
			}

			ALLEGRO_KEYBOARD_STATE state;
			al_get_keyboard_state(&state);
				//helps the game to run smoother I could remove the if statement and the only thing that would change is performance
				if (redraw)
				{
					//if colliding with basketball boss and enter is pressed
					if (basketballCollision == true && al_key_down(&state, ALLEGRO_KEY_ENTER))
					{
						// STOPPING THE MUSIC 
						al_stop_sample_instance(songInstance);
						// Playing Battle song 
						al_play_sample_instance(battleInstance);

						LoadScreen();
						int lives = BasketballBossBattle(player1, basketballBoss, player1_x, player1_y);
						player1_x = 20;
						player1_y = 340;
						player1.setLives(lives);
						LoadScreen();
						// Stop playing battle Song 
						al_stop_sample_instance(battleInstance);
						//PLAY MUSIC AGAIN
						al_play_sample_instance(songInstance);

					}
					//if colliding with football boss and enter is pressed
					if (footballCollision == true && al_key_down(&state, ALLEGRO_KEY_ENTER))
					{
						// STOPPING THE MUSIC 
						al_stop_sample_instance(songInstance);

						// Playing Battle song 
						al_play_sample_instance(battleInstance);

						LoadScreen();
						int lives = FootballBossBattle(player1, footballBoss, player1_x, player1_y);
						player1_x = 20;
						player1_y = 340;
						player1.setLives(lives);
						LoadScreen();

						// Stop playing battle Song 
						al_stop_sample_instance(battleInstance);

						//PLAY MUSIC AGAIN
						al_play_sample_instance(songInstance);
					}
					//if colliding with final boss and enter is pressed
					if (finalCollision == true && al_key_down(&state, ALLEGRO_KEY_ENTER))
					{
						// STOPPING THE MUSIC 
						al_stop_sample_instance(songInstance);

						// Playing Battle song 
						al_play_sample_instance(battleInstance);

						LoadScreen();
						int lives = FinalBossBattle(player1, finalBoss, player1_x, player1_y);
						player1_x = 20;
						player1_y = 340;
						player1.setLives(lives);
						LoadScreen();

						// Stop playing battle Song 
						al_stop_sample_instance(battleInstance);

						//PLAY MUSIC AGAIN
						al_play_sample_instance(songInstance);
					}
						redraw = false;
						//This is where everything is actually drawn at
						mapScreen.drawMapBackground();

						basketballBoss.DrawBoss();
						footballBoss.DrawBoss();
						finalBoss.DrawBoss();
					
						player1.PlayerLocation(player1_x, player1_y);
						player1.DrawPlayer();
						al_draw_textf(livesFont, al_map_rgb(255, 255, 255), 10, 0, 0, "Lives: %i", player1.getLives());
						//Had so many errors because I forgot to flip the display, everything is drawn to the back buffer and isn't brought to the front buffer until you flip the display. Very Important spents days on different erros because of this.
						al_flip_display();			

				}	
			}
	}

	//destroy each thing created still working on this :P
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_timer(timer);
	al_destroy_sample(worldMusic);
	al_destroy_sample_instance(songInstance);

	return 0;
}

void cameraUpdate(float* cameraPosition, float x, float y, int playerWidth, int playerHeight, bool basektballCollision, bool footballCollision, bool finalCollision, Boss footballBoss, Boss basketballBoss)
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

	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);

	if (basektballCollision == true && al_key_down(&state, ALLEGRO_KEY_ENTER))
	{
		cameraPosition[0] = 0;
		cameraPosition[1] = 0;
	}

	if (footballCollision == true && al_key_down(&state, ALLEGRO_KEY_ENTER))
	{
		cameraPosition[0] = 0;
		cameraPosition[1] = 0;
	}

	if (finalCollision == true && al_key_down(&state, ALLEGRO_KEY_ENTER))
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

bool FootballCollisionDetection(Boss footballBoss, float x, float y, int width, int height)
{
	bool collision;

	if (x + width < footballBoss.BossX() || x > footballBoss.BossX() + width || y + height < footballBoss.BossY() || y > footballBoss.BossY() + 72)
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

bool FinalCollisionDetection(Boss finalBoss, float x, float y, int width, int height)
{
	bool collision;

	if (x + width < finalBoss.BossX() || x > finalBoss.BossX() + width || y + height < finalBoss.BossY() || y > finalBoss.BossY() + 72)
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

//DAN AUDIO NEEDS TO GO HERE
int TitleScreen()
{
	//main menu
	ALLEGRO_BITMAP* mainScreen;
	ALLEGRO_SAMPLE* titleMusic = NULL;
	ALLEGRO_SAMPLE_INSTANCE* menuInstance = NULL;

	mainScreen = al_load_bitmap("MENU.PNG");
	//stops my code if no address is read from main screen
	assert(mainScreen != NULL);

	

	int selection = 0;

	int mainScreen_Width = al_get_bitmap_width(mainScreen);
	int mainScreen_Height = al_get_bitmap_height(mainScreen);
	//DAN PUT MAIN MENU AUDIO HERE
	// Playing Menu Song 

	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(1);

	titleMusic = al_load_sample("titlesong.wav");

	menuInstance = al_create_sample_instance(titleMusic);

	al_set_sample_instance_playmode(menuInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(menuInstance, al_get_default_mixer());

	al_play_sample_instance(menuInstance);
 
	while (!selection) {
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		al_draw_scaled_bitmap(mainScreen, 0, 0, mainScreen_Width, mainScreen_Height, 0, 0, screenWidth, screenHeight, 0);
		al_flip_display();

		if (al_key_down(&keyState, ALLEGRO_KEY_1)) {selection = 1;
		al_stop_sample_instance(menuInstance);
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_2)) { selection = 2;
		al_stop_sample_instance(menuInstance);
		}

		if (al_key_down(&keyState, ALLEGRO_KEY_3)) { selection = 3;
		al_stop_sample_instance(menuInstance);
		}
	}

	al_destroy_bitmap(mainScreen);

	return selection;
}

//This function just prints a black screen which serves as our loading screen
void LoadScreen()
{
	bool running = true;
	while (running)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();
		al_rest(2.0);
		running = false;
	}
}

//DAN AUDIO NEEDS TO GO HERE
Major CharSelect()
{
	//This bitmap specifically is just an image but it looks like a character selection screen
	ALLEGRO_BITMAP* charSelect;
	ALLEGRO_EVENT_QUEUE* queue;
	queue = al_create_event_queue();

	al_register_event_source(queue, al_get_keyboard_event_source());
	charSelect = al_load_bitmap("characterselect.png");
	
	int choice = 0;
	//DAN LOAD SCREEN NEEDS TO GO HERE

	while(!choice)
	{
		al_draw_bitmap(charSelect, 0, 0, 0);
		al_flip_display();
		
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

	

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			choice = false;

		if (al_key_down(&keyState, ALLEGRO_KEY_1)) { choice = 1; }

		if (al_key_down(&keyState, ALLEGRO_KEY_2)) { choice = 2; }

		if (al_key_down(&keyState, ALLEGRO_KEY_3)) { choice = 3; }

		if (al_key_down(&keyState, ALLEGRO_KEY_4)) { choice = 4; }
	}

	//Depending on the choice initializes the character you choose, this gets your character sprite, skills, health and damage they do
	if (choice == 1)
	{
		Major player;
		player.compScience();

		return player;
	}

	else if(choice == 2)
	{
		Major player;
		player.nurse();

		return player;
	}

	else if (choice == 3)
	{
		Major player;
		player.music();

		return player;
	}

	else if (choice == 4)
	{
		Major player;
		player.chemistry();

		return player;
	}
}

//DAN WE NEED AUDIO IN ALL OF THESE 3
int BasketballBossBattle(Major player, Boss basketballBoss, float &x, float &y)
{
	ALLEGRO_BITMAP* playerSprite;
	ALLEGRO_BITMAP* bossSprite;
	ALLEGRO_FONT* skillFont;
	ALLEGRO_FONT* healthFont;
	ALLEGRO_FONT* minusHealthFont;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* FPS;

	
	Background basketballBattle;
	basketballBattle.BattleBackground();

	event_queue = al_create_event_queue();
	FPS = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(FPS));


	//initialize fonts
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	healthFont = al_load_font("battlehealthfont.ttf", 36, 0);
	minusHealthFont = al_load_font("battlehealthfont.ttf", 24, 0);
	
	bossSprite = al_load_bitmap("basketballboss.png");
	int bossHealth = basketballBoss.GetHealth();
	int playerHealth = player.GetHealth();
	bool turn = true;
	int turnCount = 0;
	bool endingScene = false;


	bool running = true;

	al_start_timer(FPS);
	// WriteSkill1
	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			basketballBattle.drawBattleBackground();
			player.DrawPlayerBattle();
			basketballBoss.DrawBattleBoss();
			player.WriteSkill1();
			player.WriteSkill2();
			player.WriteSkill3();
			player.DrawSkill1();
			player.DrawSkill2();
			player.DrawSkill3();
			al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
			al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
			al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", basketballBoss.GetHealth());
			al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
			if (turnCount < 2)
			{
				al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
			}
			if (playerHealth == 0)
			{
				endingScene = true;
			}
			if (bossHealth == 0)
			{
				endingScene = true;
			}
			if (playerHealth <= 0 && endingScene == true)
			{
				al_draw_text(minusHealthFont, al_map_rgb(0, 0, 0), 100, 40, 0, "Now give me your lunch money loser!");
				al_flip_display();
				al_rest(2.0);

				running = false;
				player.LoseLife();
			}

			if (bossHealth <= 0 && endingScene == true) // WIN AGAINST BOSS 
			{

				al_draw_text(minusHealthFont, al_map_rgb(0, 0, 0), 100, 40, 0, "You may have beat me but you will never win!");
				al_flip_display();
				al_rest(2.0);

				running = false;
			}
			al_flip_display();

		

			ALLEGRO_KEYBOARD_STATE keyState;
			al_get_keyboard_state(&keyState);
	
			if (turn == true && bossHealth > 0 && endingScene != true)
			{
				//BASED ON THE USERS INPUT WE NEED AN AUDIO FOR EACH CHOICE, EACH CHOICE IS A SKILL
				if (al_key_down(&keyState, ALLEGRO_KEY_1))
				{
					basketballBoss.LoseHealth(player.useSkill1());
					bossHealth = basketballBoss.GetHealth();

					//DAN AUDIO NEEDS TO BE HERE
					player.PlayAudio1();
	
					al_clear_to_color(al_map_rgb(255, 255, 255));
					basketballBattle.drawBattleBackground();
					basketballBoss.DrawBattleBoss();
					player.WriteSkill1();
					player.WriteSkill2();
					player.WriteSkill3();
					player.DrawSkill1();
					player.DrawSkill2();
					player.DrawSkill3();
					
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", basketballBoss.GetHealth());
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
					if (turnCount < 2)
					{
						al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
					}
					al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill1());
					player.DrawAnimation1();
					al_flip_display();
					turn = false;
					turnCount++;
					
					al_rest(2.0);
				}

				if (al_key_down(&keyState, ALLEGRO_KEY_2))
				{
					basketballBoss.LoseHealth(player.useSkill2());
					bossHealth = basketballBoss.GetHealth();
					
					//DAN AUDIO NEEDS TO BE HERE
					player.PlayAudio2();

					al_clear_to_color(al_map_rgb(255, 255, 255));
					basketballBattle.drawBattleBackground();
					basketballBoss.DrawBattleBoss();
					player.WriteSkill1();
					player.WriteSkill2();
					player.WriteSkill3();
					player.DrawSkill1();
					player.DrawSkill2();
					player.DrawSkill3();
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", basketballBoss.GetHealth());
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
					if (turnCount < 2)
					{
						al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
					}
					al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill2());
					player.DrawAnimation2();
					al_flip_display();
					turn = false;
					turnCount++;
					al_rest(2.0);
				}

				if (al_key_down(&keyState, ALLEGRO_KEY_3))
				{
					basketballBoss.LoseHealth(player.useSkill3());
					bossHealth = basketballBoss.GetHealth();
					
					//DAN AUDIO GOES HERE
					player.PlayAudio3();

					al_clear_to_color(al_map_rgb(255, 255, 255));
					basketballBattle.drawBattleBackground();
					basketballBoss.DrawBattleBoss();
					player.WriteSkill1();
					player.WriteSkill2();
					player.WriteSkill3();
					player.DrawSkill1();
					player.DrawSkill2();
					player.DrawSkill3();
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", basketballBoss.GetHealth());
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());

					if (turnCount < 2)
					{
						al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
					}

					al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill3());
					player.DrawAnimation3();
					al_flip_display();
					turn = false;
					turnCount++;
					al_rest(2.0);
				}

				if (turnCount < 2)
				{
					if (al_key_down(&keyState, ALLEGRO_KEY_4))
					{
						return player.getLives();
					}
				}
			}
		}
		
		else if(turn == false && playerHealth > 0 && endingScene != true)
		{
			player.LoseHealth(basketballBoss.UseAttack1());
			playerHealth = player.GetHealth();
			al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 150, 230, 0, "-%i", basketballBoss.UseAttack1());
			al_flip_display();
			al_rest(1.0);


			turn = true;
		}
	
	}
	// BATTLE  MUSIC 
	return player.getLives();
}

int FootballBossBattle(Major player, Boss footballBoss, float& x, float& y)
{
	
		ALLEGRO_BITMAP* playerSprite;
		ALLEGRO_BITMAP* bossSprite;
		ALLEGRO_FONT* skillFont;
		ALLEGRO_FONT* healthFont;
		ALLEGRO_FONT* minusHealthFont;
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* FPS;


		Background footballBattle;
		footballBattle.BattleBackground();

		event_queue = al_create_event_queue();
		FPS = al_create_timer(1.0 / 60);

		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_timer_event_source(FPS));


		//initialize fonts
		skillFont = al_load_font("skillsFont.ttf", 24, 0);
		healthFont = al_load_font("battlehealthfont.ttf", 36, 0);
		minusHealthFont = al_load_font("battlehealthfont.ttf", 24, 0);

		bossSprite = al_load_bitmap("basketballboss.png");
		int bossHealth = footballBoss.GetHealth();
		int playerHealth = player.GetHealth();
		bool turn = true;
		int turnCount = 0;
		bool endingScene = false;


		bool running = true;
		al_start_timer(FPS);

		while (running)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(event_queue, &event);

			if (event.type == ALLEGRO_EVENT_TIMER)
			{
				footballBattle.drawBattleBackground();
				player.DrawPlayerBattle();
				footballBoss.DrawBattleBoss();
				player.WriteSkill1();
				player.WriteSkill2();
				player.WriteSkill3();
				player.DrawSkill1();
				player.DrawSkill2();
				player.DrawSkill3();
				al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
				al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
				al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", footballBoss.GetHealth());
				al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
				if (turnCount < 2)
				{
					al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
				}
				if (playerHealth == 0)
				{
					endingScene = true;
				}
				if (bossHealth == 0)
				{
					endingScene = true;
				}
				if (playerHealth <= 0 && endingScene == true)
				{
					al_draw_text(minusHealthFont, al_map_rgb(0, 0, 0), 100, 40, 0, "Now give me your lunch money loser!");
					al_flip_display();
					al_rest(2.0);

					running = false;
					player.LoseLife();
				}

				if (bossHealth <= 0 && endingScene == true)
				{

					al_draw_text(minusHealthFont, al_map_rgb(0, 0, 0), 100, 40, 0, "You may have beat me but you will never win!");
					al_flip_display();
					al_rest(2.0);

					running = false;
				}
				al_flip_display();



				ALLEGRO_KEYBOARD_STATE keyState;
				al_get_keyboard_state(&keyState);

				if (turn == true && bossHealth > 0 && endingScene != true)
				{

					if (al_key_down(&keyState, ALLEGRO_KEY_1))
					{
						footballBoss.LoseHealth(player.useSkill1());
						bossHealth = footballBoss.GetHealth();

						// Play Audio
						player.PlayAudio1();

						al_clear_to_color(al_map_rgb(255, 255, 255));
						footballBattle.drawBattleBackground();
						footballBoss.DrawBattleBoss();
						player.WriteSkill1();
						player.WriteSkill2();
						player.WriteSkill3();
						player.DrawSkill1();
						player.DrawSkill2();
						player.DrawSkill3();
						al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
						al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
						al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", footballBoss.GetHealth());
						al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
						if (turnCount < 2)
						{
							al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
						}
						al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill1());
						player.DrawAnimation1();
						al_flip_display();
						turn = false;
						turnCount++;

						al_rest(2.0);
					}

					if (al_key_down(&keyState, ALLEGRO_KEY_2))
					{
						footballBoss.LoseHealth(player.useSkill2());
						bossHealth = footballBoss.GetHealth();
						al_clear_to_color(al_map_rgb(255, 255, 255));


						// play Audio
						player.PlayAudio2();


						footballBattle.drawBattleBackground();
						footballBoss.DrawBattleBoss();
						player.WriteSkill1();
						player.WriteSkill2();
						player.WriteSkill3();
						player.DrawSkill1();
						player.DrawSkill2();
						player.DrawSkill3();
						
						al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
						al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
						al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", footballBoss.GetHealth());
						al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
						if (turnCount < 2)
						{
							al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
						}
						al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill2());
						player.DrawAnimation2();
						al_flip_display();
						turn = false;
						turnCount++;
						al_rest(2.0);
					}

					if (al_key_down(&keyState, ALLEGRO_KEY_3))
					{
						footballBoss.LoseHealth(player.useSkill3());
						bossHealth = footballBoss.GetHealth();

						// Play Audio for skill 3
						player.PlayAudio3();

						al_clear_to_color(al_map_rgb(255, 255, 255));
						footballBattle.drawBattleBackground();
						footballBoss.DrawBattleBoss();
						player.WriteSkill1();
						player.WriteSkill2();
						player.WriteSkill3();
						player.DrawSkill1();
						player.DrawSkill2();
						player.DrawSkill3();
						al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
						al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
						al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", footballBoss.GetHealth());
						al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());

						if (turnCount < 2)
						{
							al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
						}

						al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill3());
						player.DrawAnimation3();
						al_flip_display();
						turn = false;
						turnCount++;
						al_rest(2.0);
					}

					if (turnCount < 2)
					{
						if (al_key_down(&keyState, ALLEGRO_KEY_4))
						{
							return player.getLives();
						}
					}
				}
			}

			else if (turn == false && playerHealth > 0 && endingScene != true)
			{
				player.LoseHealth(footballBoss.UseAttack1());
				playerHealth = player.GetHealth();
				al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 150, 230, 0, "-%i", footballBoss.UseAttack1());
				al_flip_display();
				al_rest(1.0);

				turn = true;
			}

		}

		return player.getLives();
}

int FinalBossBattle(Major player, Boss finalBoss, float& x, float& y)
{
	ALLEGRO_BITMAP* playerSprite;
	ALLEGRO_BITMAP* bossSprite;
	ALLEGRO_FONT* skillFont;
	ALLEGRO_FONT* healthFont;
	ALLEGRO_FONT* minusHealthFont;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* FPS;


	Background finalBattle;
	finalBattle.BattleBackground();

	event_queue = al_create_event_queue();
	FPS = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(FPS));


	//initialize fonts
	skillFont = al_load_font("skillsFont.ttf", 24, 0);
	healthFont = al_load_font("battlehealthfont.ttf", 36, 0);
	minusHealthFont = al_load_font("battlehealthfont.ttf", 24, 0);

	bossSprite = al_load_bitmap("basketballboss.png");
	int bossHealth = finalBoss.GetHealth();
	int playerHealth = player.GetHealth();
	bool turn = true;
	int turnCount = 0;
	bool endingScene = false;


	bool running = true;
	al_start_timer(FPS);

	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			finalBattle.drawBattleBackground();
			player.DrawPlayerBattle();
			finalBoss.DrawBattleBoss();
			player.WriteSkill1();
			player.WriteSkill2();
			player.WriteSkill3();
			player.DrawSkill1();
			player.DrawSkill2();
			player.DrawSkill3();
			al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
			al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
			al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", finalBoss.GetHealth());
			al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
			if (turnCount < 2)
			{
				al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
			}
			if (playerHealth == 0)
			{
				endingScene = true;
			}
			if (bossHealth == 0)
			{
				endingScene = true;
			}
			if (playerHealth <= 0 && endingScene == true)
			{
				al_draw_text(minusHealthFont, al_map_rgb(0, 0, 0), 100, 40, 0, "Now give me your lunch money loser!");
				al_flip_display();
				al_rest(2.0);

				running = false;
				player.LoseLife();
			}

			if (bossHealth <= 0 && endingScene == true)
			{

				al_draw_text(minusHealthFont, al_map_rgb(0, 0, 0), 100, 40, 0, "You may have beat me but you will never win!");
				al_flip_display();
				al_rest(2.0);

				running = false;
			}
			al_flip_display();



			ALLEGRO_KEYBOARD_STATE keyState;
			al_get_keyboard_state(&keyState);

			if (turn == true && bossHealth > 0 && endingScene != true)
			{

				if (al_key_down(&keyState, ALLEGRO_KEY_1))
				{
					finalBoss.LoseHealth(player.useSkill1());
					bossHealth = finalBoss.GetHealth();

					al_clear_to_color(al_map_rgb(255, 255, 255));
					finalBattle.drawBattleBackground();
					finalBoss.DrawBattleBoss();

					// Play skill 1 sound 
					player.PlayAudio1();

					player.WriteSkill1();
					player.WriteSkill2();
					player.WriteSkill3();
					player.DrawSkill1();
					player.DrawSkill2();
					player.DrawSkill3();
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", finalBoss.GetHealth());
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
					if (turnCount < 2)
					{
						al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
					}
					al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill1());
					player.DrawAnimation1();
					al_flip_display();
					turn = false;
					turnCount++;

					al_rest(2.0);
				}

				if (al_key_down(&keyState, ALLEGRO_KEY_2))
				{
					finalBoss.LoseHealth(player.useSkill2());
					bossHealth = finalBoss.GetHealth();
					al_clear_to_color(al_map_rgb(255, 255, 255));

					finalBattle.drawBattleBackground();
					finalBoss.DrawBattleBoss();
					// Play skill 2 sound 
					player.PlayAudio2();

					player.WriteSkill1();
					player.WriteSkill2();
					player.WriteSkill3();
					player.DrawSkill1();
					player.DrawSkill2();
					player.DrawSkill3();
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", finalBoss.GetHealth());
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());
					if (turnCount < 2)
					{
						al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
					}
					al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill2());
					player.DrawAnimation2();
					al_flip_display();
					turn = false;
					turnCount++;
					al_rest(2.0);
				}

				if (al_key_down(&keyState, ALLEGRO_KEY_3))
				{
					finalBoss.LoseHealth(player.useSkill3());
					bossHealth = finalBoss.GetHealth();

					al_clear_to_color(al_map_rgb(255, 255, 255));
					finalBattle.drawBattleBackground();
					finalBoss.DrawBattleBoss();

					// Play skill 3 sound 
					player.PlayAudio3();

					player.WriteSkill1();
					player.WriteSkill2();
					player.WriteSkill3();
					player.DrawSkill1();
					player.DrawSkill2();
					player.DrawSkill3();
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 480, 15, 0, "Health:");
					al_draw_text(healthFont, al_map_rgb(0, 0, 0), 25, 400, 0, "Health:");
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 570, 15, 0, "%i", finalBoss.GetHealth());
					al_draw_textf(healthFont, al_map_rgb(0, 0, 0), 120, 400, 0, "%i", player.GetHealth());

					if (turnCount < 2)
					{
						al_draw_text(skillFont, al_map_rgb(255, 255, 255), 340, 580, 0, "4) RUN!!!");
					}

					al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 340, 80, 0, "-%i", player.useSkill3());
					player.DrawAnimation3();
					al_flip_display();
					turn = false;
					turnCount++;
					al_rest(2.0);
				}

				if (turnCount < 2)
				{
					if (al_key_down(&keyState, ALLEGRO_KEY_4))
					{
						return player.getLives();
					}
				}
			}
		}

		else if (turn == false && playerHealth > 0 && endingScene != true)
		{
			player.LoseHealth(finalBoss.UseAttack1());
			playerHealth = player.GetHealth();
			al_draw_textf(minusHealthFont, al_map_rgb(0, 0, 0), 150, 230, 0, "-%i", finalBoss.UseAttack1());
			al_flip_display();
			al_rest(1.0);

			turn = true;
		}

	}

	return player.getLives();
}