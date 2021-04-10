#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "characters.h"
#include "map.h"

//Global Variables
int screenWidth = 640;
int screenHeight = 640;


int TitleScreen();
Major SinglePlayer_CharSelect();
void cameraUpdate(float* cameraPosition, float x, float y, int width, int height);


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

	//display option
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
	
	//font things
	ALLEGRO_FONT* livesFont;
	livesFont = al_load_font("helloworld.ttf", 48, 0);



	int selection = 0;
	selection = TitleScreen();
	
	//object variables
	Major player1;

	Boss basketballBoss;
	basketballBoss.Basketball_Boss();

	Background mapScreen;
	mapScreen.grassBackground();



	if (selection == 1)
	{
		player1 = SinglePlayer_CharSelect();
	}
	

	int bitmap_width;
	int bitmap_height;

	bitmap_width = player1.getSpriteWidth(player1);
	bitmap_height = player1.getSpriteHeight(player1);

	

	bool running = true;
	float x = 640 / 2, y = 640;

	float cameraPosition[2] = { 0, 0 };

	bool redraw = true;

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

					cameraUpdate(cameraPosition, x, y, bitmap_width, bitmap_height);

					al_identity_transform(&camera);
					al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
					al_use_transform(&camera);

					redraw = true;
				}
			
				if (redraw)
				{
					
					redraw = false;
					mapScreen.drawBackground();

					basketballBoss.DrawBoss();
					player1.PlayerLocation(x, y);
					player1.DrawPlayer();
					al_draw_textf(livesFont, al_map_rgb(255, 255, 255), 10, 0, 0, "Lives: %i", player1.getLives(player1));
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

void cameraUpdate(float* cameraPosition, float x, float y, int playerWidth, int playerHeight)
{
	cameraPosition[0] = -(screenWidth / 2) + (x + playerWidth / 2);
	cameraPosition[1] = -(screenHeight / 2) + (y + playerHeight / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;
	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;
	if (cameraPosition[0] > screenWidth)
		cameraPosition[0] = screenWidth;
	if (cameraPosition[1] > screenHeight)
		cameraPosition[1] = screenHeight;

}





int TitleScreen()
{
	//main menu
	ALLEGRO_BITMAP* mainScreen;
	mainScreen = al_load_bitmap("halo.jpg");
	assert(mainScreen != NULL);


	int selection = 0;

	int mainScreen_Width = al_get_bitmap_width(mainScreen);
	int mainScreen_Height = al_get_bitmap_height(mainScreen);

	while (!selection) {
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) { return false; }

		al_draw_scaled_bitmap(mainScreen, 0, 0, mainScreen_Width, mainScreen_Height, 0, 0, screenWidth, screenHeight, 0);
		al_flip_display();

		if (al_key_down(&keyState, ALLEGRO_KEY_1)) {selection = 1;}
	}

	al_destroy_bitmap(mainScreen);

	return selection;
}

Major SinglePlayer_CharSelect()
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

		if (al_key_down(&keyState, ALLEGRO_KEY_1)) { choice = 1; }

		if (al_key_down(&keyState, ALLEGRO_KEY_2)) { choice = 2; }

		if (al_key_down(&keyState, ALLEGRO_KEY_3)) { choice = 3; }

		if (al_key_down(&keyState, ALLEGRO_KEY_4)) { choice = 4; }
	}

	if (choice == 1)
	{
		Major player1;
		player1.compScience();

		return player1;
	}

	else if(choice == 2)
	{
		Major player1;
		player1.music();

		return player1;
	}

	else if (choice == 3)
	{
		Major player1;
		player1.nurse();

		return player1;
	}

	else if (choice == 4)
	{
		Major player1;
		player1.chemistry();

		return player1;
	}
}

