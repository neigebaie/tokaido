#include <square_draw.h>

SquareGui* new_inn_gui(Food* foods)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	Menu* menu = base_menu(1, 1, 0, 1);
	ContentType ct = CONTENT_FOOD;

	menu->texts[0] = new_text("Relai", 0, 0, 0, 1);
	menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;

	sgui->frames = (Frame*)malloc(sizeof(Frame) * INN_FRAMES);
	AnchorInfo ai;
	ai.at = AT_CENTER;
	ai.size = {200, 300};

	for (int i = 0; i < INN_FRAMES; i++) {
		ai.offset.x = ((i % 3) - 1) * 320;
		ai.offset.y = 360 * (1 - (int)(i/3));
		sgui->frames[i] = new_frame(ai, ct, foods[i]);

		char price[2];
		sprintf(price, "%d", foods[i].price);
		strcpy(innGui->foodFrames[i]->coinText->text, price);
		update_text(innGui->foodFrames[i]->coinText);

		strcpy(innGui->foodFrames[i]->bundleTkText->text, "+6");
		update_text(innGui->foodFrames[i]->bundleTkText);
	}

	innGui->backBtn = res->backBtn;
	innGui->backBtn->bg->rect->x = WINDOW_WIDTH - innGui->backBtn->bg->rect->w - 20;
	innGui->backBtn->bg->rect->y = WINDOW_HEIGHT - innGui->backBtn->bg->rect->h - 20;
	center_rect(innGui->backBtn->text->rect, innGui->backBtn->bg->rect);
}

// SquareGui* new_shop_gui();
//
// SquareGui* new_hot_spring_gui();
//
// SquareGui* new_temple_gui();
//
// SquareGui* new_encounter_gui();
//
// SquareGui* new_farm_gui();
//
// SquareGui* new_pan_rice_gui();
//
// SquareGui* new_pan_mount_gui();
//
// SquareGui* new_pan_sea_gui();

// HUD
Hud* new_hud()
{
	Hud* hud = (Hud*)malloc(sizeof(Hud));

	hud->travelerIcon = (Sprite*)malloc(sizeof(Sprite));
	hud->travelerIcon->rect = new_rect(10, 10, 50, 50);

	hud->nick = (Sprite*)malloc(sizeof(Sprite));

	hud->coinIcon = textureMgr->coinIcon;
	// hud->coinIcon->rect->y = 10;
	// hud->coinIcon->rect->w = 50;
	// hud->coinIcon->rect->h = 50;

	hud->coinText = new_text(255, 255, 255, 1);
	// hud->coinText->sprite->rect->y = 10;

	hud->bundleTkIcon   = textureMgr->bundleTkIcon;
	// hud->bundleTkIcon->rect->y = 10;
	// hud->bundleTkIcon->rect->w = 50;
	// hud->bundleTkIcon->rect->h = 50;

	hud->bundleTkText   = new_text_info(255, 255, 255, 1);
	// hud->bundleTkText->sprite->rect->y = 10;

	hud->templeCoinIcon = textureMgr->templeCoinIcon;
	// hud->templeCoinIcon->rect->y = 10;
	// hud->templeCoinIcon->rect->w = 50;
	// hud->templeCoinIcon->rect->h = 50;

	hud->templeCoinText = new_text(255, 255, 255, 1);
	// hud->templeCoinText->sprite->rect->y = 10;

	return hud;
}
void update_hud(Hud* hud, Player* player);

// FRAME
Frame new_frame(AnchorInfo ai, ContentType contentType, Content content)
{
	Frame frame;

	frame.ai = ai;

	frame.state = STATE_IDLE;

	frame.bg = textureMgr.frame;
	frame.bg.parentAi = &frame.ai;
	frame.bg.ai.at = AT_TOP_LEFT;
	frame.bg.ai.offset.x = -23;
	frame.bg.ai.offset.y = -20;
	frame.bg.ai.size.w = frame.frameRect->w + 40;
	frame.bg.ai.size.h = frame.frameRect->h + 40;

	frame.coinIcon = textureMgr.frame;
	frame.coinIcon.parentAi = &frame.ai;
	// frame.coinIcon->rect->x = frame.frameRect->x + 16 + 100;
	// frame.coinIcon->rect->y = frame.frameRect->y + frame.frameRect->h - 45;
	// frame.coinIcon->rect->w = 32;
	// frame.coinIcon->rect->h = 32;

	frame.coinText = new_text_info(255, 255, 255, 1);
	frame.coinText.parentAi = &frame.ai;
	// frame.coinText->sprite->rect->x = frame.frameRect->x + 16 + 40 + 100;
	// frame.coinText->sprite->rect->y = frame.frameRect->y + frame.frameRect->h - 50;

	frame.bundleTkIcon = sprite_copy(res->bundleTkIcon);
	frame.bundleTkIcon.parentAi = &frame.ai;
	// frame.bundleTkIcon->rect->x = frame.frameRect->x + 16;
	// frame.bundleTkIcon->rect->y = frame.frameRect->y + frame.frameRect->h - 45;
	// frame.bundleTkIcon->rect->w = 32;
	// frame.bundleTkIcon->rect->h = 32;

	frame.bundleTkText = new_text_info(255, 255, 255, 1);
	frame.bundleTkText.parentAi = &frame.ai;
	// frame.bundleTkText->sprite->rect->x = frame.frameRect->x + 16 + 35;
	// frame.bundleTkText->sprite->rect->y = frame.frameRect->y + frame.frameRect->h - 50;

	return &frame;
}

void draw_frame(Frame* frame)
{
	state_color_mod(frame->bg->tex, frame->state);
	draw_sprite(frame->bg);
	SDL_SetTextureColorMod(frame->bg->tex, 255, 255, 255);

	draw_sprite(frame->title);

	draw_sprite(frame->coinIcon);
	draw_sprite(frame->coinText->sprite);

	draw_sprite(frame->bundleTkIcon);
	draw_sprite(frame->bundleTkText->sprite);

	if (frame->food)
	{
		draw_sprite(frame->food->sprite);
	}
}

void draw_square_gui(SquareGui* sgui)
{
	draw_menu(sgui->menu);
}


// void set_content_in_frame(Frame* frame, Content* content)
// {
// 	frame.title = new_sprite_from_str(food->name, 255, 255, 255, 0.4);
// 	center_rect(frame.title->rect, new_rect(frame.frameRect->x, frame.frameRect->y + frame.frameRect->w, frame.frameRect->w, 50));
// 	// frame.food = food;
// 	frame.content->sprite = sprite_copy(food->sprite);
// 	center_rect(frame.food->sprite->rect, new_rect(frame.frameRect->x + 20, frame.frameRect->y + 20, frame.frameRect->w - 40, frame.frameRect->w - 40));
// }

// NEW GUI FOR EACH SQUARE TYPE

// ShopGui* new_shop_gui(SquareGuiRes* res)
// {
// 	ShopGui* shopGui = (ShopGui*)malloc(sizeof(ShopGui));
// 	shopGui->title = new_sprite_from_str("Échoppe", 0, 0, 0, 1);
// 	center_rect(shopGui->title->rect, new_rect(0, 0, WINDOW_WIDTH, 300));
//
// 	for (int i = 0; i < 3; i++) {
// 		SDL_Rect frameRect = {WINDOW_WIDTH/2 - (1 - i) * 320 - 200/2, WINDOW_HEIGHT/2 - 100, 200, 300};
// 		shopGui->itemFrames[i] = new_item_frame(res, &frameRect);
//
// 		char price[2];
// 		sprintf(price, "%d", rand() % 3 + 1);
// 		strcpy(shopGui->itemFrames[i]->coinText->text, price);
// 		text_info_update(shopGui->itemFrames[i]->coinText);
// 		shopGui->itemFrames[i]->coinText->sprite->rect->w *= 0.75;
// 		shopGui->itemFrames[i]->coinText->sprite->rect->h *= 0.75;
//
// 		strcpy(shopGui->itemFrames[i]->bundleTkText->text, "1/3/5/7");
// 		text_info_update(shopGui->itemFrames[i]->bundleTkText);
// 		shopGui->itemFrames[i]->bundleTkText->sprite->rect->w *= 0.75;
// 		shopGui->itemFrames[i]->bundleTkText->sprite->rect->h *= 0.75;
// 	}
//
// 	shopGui->backBtn = res->backBtn;
// 	shopGui->backBtn->bg->rect->x = WINDOW_WIDTH - shopGui->backBtn->bg->rect->w - 20;
// 	shopGui->backBtn->bg->rect->y = WINDOW_HEIGHT - shopGui->backBtn->bg->rect->h - 20;
// 	center_rect(shopGui->backBtn->text->rect, shopGui->backBtn->bg->rect);
//
// 	return shopGui;
// }
