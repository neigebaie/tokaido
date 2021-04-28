#ifndef SQUARE_DRAW_H_
#define SQUARE_DRAW_H_

#include <stdio.h>

#include <game.h>
#include <gui.h>

#define INN_FRAMES 6
#define SHOP_FRAMES 3

#define PAN_RICE_CARDS 3
#define PAN_MOUNT_CARDS 4
#define PAN_SEA_CARDS 5


typedef enum
{
	CONTENT_FOOD,
	CONTENT_ITEM
} ContentType;

typedef union {
	Food food;
	Item item;
} Content;


typedef struct
{
	AnchorInfo ai;
	Text* title;
	Sprite bg;

	State state;

	Sprite coinIcon;
	Text* coinText;

	Sprite bundleTkIcon;
	Text* bundleTkText;

	Sprite itemCatIcon;

	ContentType contentType;
	Content content;

} Frame;

typedef struct
{
	Sprite* itemCatIcons[ITEM_CATS];
	Text* itemCatTexts[ITEM_CATS];
} CollectionFrame;


typedef struct
{
	Menu* menu;
	SquareId squareId;

	Frame** frames;
	int frameCount;

	union {
		CollectionFrame colFrame;
		Sprite* panorama;
	} special;

} SquareGui;


typedef struct
{
	Text* nick;
	Sprite travelerIcon;

	Sprite coinIcon;
	Text* coinText;

	Sprite bundleTkIcon;
	Text* bundleTkText;

	Sprite templeCoinIcon;
	Text* templeCoinText;
} Hud;

// SquareGui

SquareGui* new_inn_gui(Food** foods, int foodCount);
SquareGui* new_shop_gui(Item* items[]);
SquareGui* new_hot_spring_gui();
SquareGui* new_temple_gui();
SquareGui* new_encounter_gui();
SquareGui* new_farm_gui();
SquareGui* new_pan_rice_gui();
SquareGui* new_pan_mount_gui();
SquareGui* new_pan_sea_gui();

// HUD
Hud* new_hud(Player player);
void draw_hud(Hud* hud);

// FRAME
Frame* new_frame(AnchorInfo* ai, ContentType contentType, Content content);
void draw_frame(Frame* frame);

void draw_square_gui(SquareGui* sgui);

#endif
