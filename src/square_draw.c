#include <square_draw.h>

// SQUARE GUI INIT

// todo
SquareGui* init_square_gui(char* nick, TextureMgr* textureMgr)
{
	SquareGui* squareGui = (SquareGui*)malloc(sizeof(SquareGui));

	SquareGuiRes* res = (SquareGuiRes*)malloc(sizeof(SquareGuiRes));

	Sprite* btn = new_sprite(textureMgr->guiTex, new_rect(0, 0, 1319, 307));
	btn->rect->w *= 0.25;
	btn->rect->h *= 0.25;

	res->bundleTkIcon = new_sprite(textureMgr->iconTex, new_rect(256, 0, 256, 256));
	res->coinIcon = new_sprite(textureMgr->iconTex, new_rect(0, 0, 256, 256));
	for (int i = 0; i < ITEM_CATS; i++) {
		res->itemCatIcons[i] = new_sprite(textureMgr->iconTex, new_rect(128 * i, 384, 128, 128));
	}
	res->templeCoinIcon = new_sprite(textureMgr->iconTex, new_rect(0, 265, 128, 128));
	res->frameBg = new_sprite(textureMgr->guiTex, new_rect(1320, 0, 643, 882));

	res->backBtn = new_button("Retour", 255, 255, 255, btn, 0.5);

	squareGui->hud = new_hud(res, nick);

	squareGui->innGui       = new_inn_gui(res);
	squareGui->shopGui      = new_shop_gui(res);
	squareGui->hotSpringGui = new_hot_spring_gui(res);
	squareGui->templeGui    = new_temple_gui(res);
	squareGui->encounterGui = new_encounter_gui(res);
	squareGui->farmGui      = new_farm_gui(res);
	squareGui->panRiceGui   = new_pan_rice_gui(res);
	squareGui->panMountGui  = new_pan_mount_gui(res);
	squareGui->panSeaGui    = new_pan_sea_gui(res);

	printf("\e[36m [DEBUG] SquareGui loaded !\e[37m\n");
	return squareGui;
}

// NEW FRAME

ItemFrame* new_item_frame(SquareGuiRes* res)
{
	ItemFrame* itemFrame = (ItemFrame*)malloc(sizeof(ItemFrame));
	return itemFrame;
}

void set_item_in_frame(ItemFrame* itemFrame, Item* item)
{
	itemFrame->item = item;
}

FoodFrame* new_food_frame(SquareGuiRes* res, SDL_Rect* frameRect)
{
	FoodFrame* foodFrame = (FoodFrame*)malloc(sizeof(FoodFrame));

	foodFrame->frameRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	foodFrame->frameRect->x = frameRect->x;
	foodFrame->frameRect->y = frameRect->y;
	foodFrame->frameRect->w = frameRect->w;
	foodFrame->frameRect->h = frameRect->h;
	foodFrame->title = NULL;
	foodFrame->bg = sprite_copy(res->frameBg);
	foodFrame->bg->rect->x = foodFrame->frameRect->x - 23;
	foodFrame->bg->rect->y = foodFrame->frameRect->y - 20;
	foodFrame->bg->rect->w = foodFrame->frameRect->w + 40;
	foodFrame->bg->rect->h = foodFrame->frameRect->h + 40;

	foodFrame->coinIcon = sprite_copy(res->coinIcon);
	foodFrame->coinIcon->rect->x = foodFrame->frameRect->x + 16 + 100;
	foodFrame->coinIcon->rect->y = foodFrame->frameRect->y + foodFrame->frameRect->h - 45;
	foodFrame->coinIcon->rect->w = 32;
	foodFrame->coinIcon->rect->h = 32;

	foodFrame->coinText = new_text_info(255, 255, 255, 1);
	foodFrame->coinText->sprite->rect->x = foodFrame->frameRect->x + 16 + 40 + 100;
	foodFrame->coinText->sprite->rect->y = foodFrame->frameRect->y + foodFrame->frameRect->h - 50;

	foodFrame->bundleTkIcon = sprite_copy(res->bundleTkIcon);
	foodFrame->bundleTkIcon->rect->x = foodFrame->frameRect->x + 16;
	foodFrame->bundleTkIcon->rect->y = foodFrame->frameRect->y + foodFrame->frameRect->h - 45;
	foodFrame->bundleTkIcon->rect->w = 32;
	foodFrame->bundleTkIcon->rect->h = 32;

	foodFrame->bundleTkText = new_text_info(255, 255, 255, 1);
	foodFrame->bundleTkText->sprite->rect->x = foodFrame->frameRect->x + 16 + 35;
	foodFrame->bundleTkText->sprite->rect->y = foodFrame->frameRect->y + foodFrame->frameRect->h - 50;

	foodFrame->food = (Food*)malloc(sizeof(Food));

	return foodFrame;
}

void set_food_in_frame(FoodFrame* foodFrame, Food* food)
{
	foodFrame->title = new_sprite_from_str(food->name, 255, 255, 255, 0.4);
	center_rect(foodFrame->title->rect, new_rect(foodFrame->frameRect->x, foodFrame->frameRect->y + foodFrame->frameRect->w, foodFrame->frameRect->w, 50));
	// foodFrame->food = food;
	foodFrame->food->sprite = sprite_copy(food->sprite);
	center_rect(foodFrame->food->sprite->rect, new_rect(foodFrame->frameRect->x + 20, foodFrame->frameRect->y + 20, foodFrame->frameRect->w - 40, foodFrame->frameRect->w - 40));
}

// NEW GUI FOR EACH SQUARE TYPE

Hud* new_hud(SquareGuiRes* res, char* nick)
{
	Hud* hud = (Hud*)malloc(sizeof(Hud));

	hud->nick = new_sprite_from_str(nick, 250, 250, 250, 0.4);
	hud->nick->rect->x = 10;
	hud->nick->rect->y = 10;

	hud->coinIcon       = sprite_copy(res->coinIcon);
	hud->coinText       = new_text_info(0, 0, 0, 1);

	hud->bundleTkIcon   = sprite_copy(res->bundleTkIcon);
	hud->bundleTkText   = new_text_info(0, 0, 0, 1);

	hud->templeCoinIcon = sprite_copy(res->templeCoinIcon);
	hud->templeCoinText = new_text_info(0, 0, 0, 1);

	return hud;
}

// todo
InnGui* new_inn_gui(SquareGuiRes* res)
{
	InnGui* innGui = (InnGui*)malloc(sizeof(InnGui));
	innGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	center_rect(innGui->title->rect, new_rect(0, 0, 1920, 300));
	for (int i = 0; i < INN_FRAMES; i++) {
		SDL_Rect frameRect = {WINDOW_WIDTH/2 - (1 - i) * 320 - 320 * 3 * (int)(i/3) - 200/2, 100 + WINDOW_HEIGHT/2 - 360 * (1 - (int)(i/3)), 200, 300};
		innGui->foodFrames[i] = new_food_frame(res, &frameRect);

		char price[2];
		sprintf(price, "%d", rand() % 3 + 1);
		strcpy(innGui->foodFrames[i]->coinText->text, price);
		text_info_update(innGui->foodFrames[i]->coinText);
		innGui->foodFrames[i]->coinText->sprite->rect->w *= 0.75;
		innGui->foodFrames[i]->coinText->sprite->rect->h *= 0.75;

		strcpy(innGui->foodFrames[i]->bundleTkText->text, "+6");
		text_info_update(innGui->foodFrames[i]->bundleTkText);
		innGui->foodFrames[i]->bundleTkText->sprite->rect->w *= 0.75;
		innGui->foodFrames[i]->bundleTkText->sprite->rect->h *= 0.75;
	}

	innGui->backBtn = res->backBtn;
	innGui->backBtn->bg->rect->x = WINDOW_WIDTH - innGui->backBtn->bg->rect->w - 20;
	innGui->backBtn->bg->rect->y = WINDOW_HEIGHT - innGui->backBtn->bg->rect->h - 20;
	center_rect(innGui->backBtn->text->rect, innGui->backBtn->bg->rect);

	return innGui;
}

// todo
ShopGui* new_shop_gui(SquareGuiRes* res)
{
	ShopGui* shopGui = (ShopGui*)malloc(sizeof(ShopGui));
	shopGui->title = new_sprite_from_str("Échoppe", 0, 0, 0, 1);
	for (int i = 0; i < 3; i++) {
		shopGui->itemFrames[i] = new_item_frame(res);
	}
	return shopGui;
}

// todo
HotSpringGui* new_hot_spring_gui(SquareGuiRes* res)
{
	HotSpringGui* hotSpringGui = (HotSpringGui*)malloc(sizeof(HotSpringGui));
	hotSpringGui->title = new_sprite_from_str("Source Chaude", 0, 0, 0, 1);
	return hotSpringGui;
}

// todo
TempleGui* new_temple_gui(SquareGuiRes* res)
{
	TempleGui* templeGui = (TempleGui*)malloc(sizeof(TempleGui));
	templeGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	return templeGui;
}

// todo
EncounterGui* new_encounter_gui(SquareGuiRes* res)
{
	EncounterGui* encounterGui = (EncounterGui*)malloc(sizeof(EncounterGui));
	encounterGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	return encounterGui;
}

// todo
FarmGui* new_farm_gui(SquareGuiRes* res)
{
	FarmGui* farmGui = (FarmGui*)malloc(sizeof(FarmGui));
	farmGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	return farmGui;
}

// todo
PanRiceGui* new_pan_rice_gui(SquareGuiRes* res)
{
	PanRiceGui* panRiceGui = (PanRiceGui*)malloc(sizeof(PanRiceGui));
	panRiceGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	return panRiceGui;
}

// todo
PanMountGui* new_pan_mount_gui(SquareGuiRes* res)
{
	PanMountGui* panMountGui = (PanMountGui*)malloc(sizeof(PanMountGui));
	panMountGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	return panMountGui;
}

// todo
PanSeaGui* new_pan_sea_gui(SquareGuiRes* res)
{
	PanSeaGui* panSeaGui = (PanSeaGui*)malloc(sizeof(PanSeaGui));
	panSeaGui->title = new_sprite_from_str("Relai", 0, 0, 0, 1);
	return panSeaGui;
}

// DRAW FRAME

void draw_item_frame(ItemFrame* itemFrame)
{

}

void draw_food_frame(FoodFrame* foodFrame)
{
	draw_sprite(foodFrame->bg);
	draw_sprite(foodFrame->title);

	draw_sprite(foodFrame->coinIcon);
	draw_sprite(foodFrame->coinText->sprite);

	draw_sprite(foodFrame->bundleTkIcon);
	draw_sprite(foodFrame->bundleTkText->sprite);

	if (foodFrame->food)
	{
		draw_sprite(foodFrame->food->sprite);
	}

	// SDL_Rect debugRect = {0, 0, 0, 0};
	// debugRect.x = foodFrame->frameRect->x;
	// debugRect.y = foodFrame->frameRect->y;
	// debugRect.w = foodFrame->frameRect->w;
	// debugRect.h = foodFrame->frameRect->h;
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// SDL_RenderDrawRect(renderer, &debugRect);
	// debugRect.x = foodFrame->bg->rect->x;
	// debugRect.y = foodFrame->bg->rect->y;
	// debugRect.w = foodFrame->bg->rect->w;
	// debugRect.h = foodFrame->bg->rect->h;
	// SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	// SDL_RenderDrawRect(renderer, &debugRect);
}

// DRAW FOR EACH SQUARE TYPE

void draw_inn(InnGui* innGui)
{
	draw_sprite(innGui->title);
	for (int i = 0; i < INN_FRAMES; i++) {
		draw_food_frame(innGui->foodFrames[i]);
	}
	draw_button(innGui->backBtn);
}

void draw_shop(ShopGui* shopGui)
{
	draw_sprite(shopGui->title);
}

void draw_hot_spring(HotSpringGui* hotSpringGui)
{
	draw_sprite(hotSpringGui->title);
}

void draw_temple(TempleGui* templeGui)
{
	draw_sprite(templeGui->title);
}

void draw_encounter(EncounterGui* encounterGui)
{
	draw_sprite(encounterGui->title);
}

void draw_farm(FarmGui* farmGui)
{
	draw_sprite(farmGui->title);
}

void draw_pan_rice(PanRiceGui* panRiceGui)
{
	draw_sprite(panRiceGui->title);
}

void draw_pan_mount(PanMountGui* panMountGui)
{
	draw_sprite(panMountGui->title);
}

void draw_pan_sea(PanRiceGui* panSeaGui)
{
	draw_sprite(panSeaGui->title);
}
