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

// FRAMES

typedef struct
{
	SDL_Rect* frameRect;
	Sprite* title;
	Sprite* bg;

	Sprite* coinIcon;
	TextInfo* coinText;

	Sprite* bundleTkIcon;
	TextInfo* bundleTkText;

	Food* food;
} FoodFrame;

typedef struct
{
	SDL_Rect* frameRect;
	Sprite* title;
	Sprite* bg;

	Sprite* coinIcon;
	TextInfo* coinText;

	Sprite* bundleTkIcon;
	TextInfo* bundleTkText;

	Item* item;
} ItemFrame;

typedef struct
{
	Sprite* itemCatIcons[ITEM_CATS];
	TextInfo* itemCatTexts[ITEM_CATS];
} CollectionFrame;
// GUI FOR EACH SQUARE

typedef struct
{
	Sprite* title;
	FoodFrame* foodFrames[INN_FRAMES];
	Button* backBtn;
} InnGui;

typedef struct
{
	Sprite* title;
	ItemFrame* itemFrames[SHOP_FRAMES];
	CollectionFrame* colFrame;
	Button* backBtn;
} ShopGui;

typedef struct
{
	Sprite* title;
	Sprite* obtained;
	Button* backBtn;
} HotSpringGui;

typedef struct
{
	Sprite* title;
	Button* giveBtn;
	Button* backBtn;
} TempleGui;

typedef struct
{
	Sprite* title;
	TextInfo textInfo;
	Button* backBtn;
} EncounterGui;

typedef struct
{
	Sprite* title;
	Sprite* obtained;
	Button* backBtn;
} FarmGui;

typedef struct
{
	Sprite* title;
	Sprite* panorama[PAN_RICE_CARDS];
	Button* backBtn;
} PanRiceGui;

typedef struct
{
	Sprite* title;
	Sprite* panorama[PAN_MOUNT_CARDS];
	Button* backBtn;
} PanMountGui;

typedef struct
{
	Sprite* title;
	Sprite* panorama[PAN_SEA_CARDS];
	Button* backBtn;
} PanSeaGui;

typedef struct
{
	Sprite* nick;

	Sprite* coinIcon;
	TextInfo* coinText;

	Sprite* bundleTkIcon;
	TextInfo* bundleTkText;

	Sprite* templeCoinIcon;
	TextInfo* templeCoinText;
} Hud;


// SQUARE GUI

typedef struct
{
	Sprite* bundleTkIcon;
	Sprite* coinIcon;
	Sprite* itemCatIcons[ITEM_CATS];
	Sprite* templeCoinIcon;
	Sprite* frameBg;
	Button* backBtn;
} SquareGuiRes;

typedef struct
{
	SquareGuiRes* res;

	Hud*          hud;

	InnGui*       innGui;
	ShopGui*      shopGui;
	HotSpringGui* hotSpringGui;
	TempleGui*    templeGui;
	EncounterGui* encounterGui;
	FarmGui*      farmGui;
	PanRiceGui*   panRiceGui;
	PanMountGui*  panMountGui;
	PanSeaGui*    panSeaGui;

} SquareGui;


// INIT SQUARE GUI
SquareGui* init_square_gui(char* nick, TextureMgr* textureMgr);

// NEW FRAME
ItemFrame* new_item_frame(SquareGuiRes* res);
void set_item_in_frame(ItemFrame* itemFrame, Item* item);
FoodFrame* new_food_frame(SquareGuiRes* res, SDL_Rect* frameRect);
void set_food_in_frame(FoodFrame* foodFrame, Food* food);

// NEW GUI FOR EACH SQUARE
Hud*          new_hud(SquareGuiRes* res, char* nick);
InnGui*       new_inn_gui(SquareGuiRes* res);
ShopGui*      new_shop_gui(SquareGuiRes* res);
HotSpringGui* new_hot_spring_gui(SquareGuiRes* res);
TempleGui*    new_temple_gui(SquareGuiRes* res);
EncounterGui* new_encounter_gui(SquareGuiRes* res);
FarmGui*      new_farm_gui(SquareGuiRes* res);
PanRiceGui*   new_pan_rice_gui(SquareGuiRes* res);
PanMountGui*  new_pan_mount_gui(SquareGuiRes* res);
PanSeaGui*    new_pan_sea_gui(SquareGuiRes* res);

// DRAW FRAME
void draw_item_frame(ItemFrame* itemFrame);
void draw_food_frame(FoodFrame* foodFrame);

// DRAW FOR EACH SQUARE
void draw_inn(InnGui* innGui);
void draw_shop(ShopGui* shopGui);
void draw_hot_spring(HotSpringGui* hotSpringGui);
void draw_temple(TempleGui* templeGui);
void draw_encounter(EncounterGui* encounterGui);
void draw_farm(FarmGui* farmGui);
void draw_pan_rice(PanRiceGui* panRiceGui);
void draw_pan_mount(PanMountGui* panMountGui);
void draw_pan_sea(PanRiceGui* panSeaGui);

#endif
