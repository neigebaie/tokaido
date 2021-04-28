#include <square_draw.h>

SquareGui* new_inn_gui(Food* foods[], int foodCount)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	sgui->menu = base_menu(0, 1, 0, 1);
	ContentType contentType = CONTENT_FOOD;
	Content content;

	sgui->menu->texts[0] = new_text("Relai", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->frameCount = foodCount;

	sgui->frames = (Frame**)malloc(sizeof(Frame*) * foodCount);
	AnchorInfo ai;
	ai.at = AT_CENTER;
	ai.size = (Size){220, 330};

	for (int i = 0; i < foodCount; i++) {
		ai.offset.x = ((i % 3) - 1) * 320;
		ai.offset.y = 400 * (int)(i/3) - 200;
		content.food = *foods[i];

		sgui->frames[i] = new_frame(&ai, contentType, content);

		sprintf(sgui->frames[i]->title->content, "%s", foods[i]->name);
		update_text(sgui->frames[i]->title);

		sprintf(sgui->frames[i]->coinText->content, "%d", foods[i]->price);
		update_text(sgui->frames[i]->coinText);

		strcpy(sgui->frames[i]->bundleTkText->content, "+6");
		update_text(sgui->frames[i]->bundleTkText);

	}

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_shop_gui(Item* items[]/*, Player* player*/)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	sgui->menu = base_menu(0, 1, 0, 1);
	ContentType contentType = CONTENT_ITEM;
	Content content;

	sgui->menu->texts[0] = new_text("Échoppe", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;


	sgui->frameCount = 3;

	sgui->frames = (Frame**)malloc(sizeof(Frame*) * sgui->frameCount);
	AnchorInfo ai;
	ai.at = AT_CENTER;
	ai.size = (Size){220, 330};

	for (int i = 0; i < sgui->frameCount; i++) {
		ai.offset.x = (i - 1) * 320;
		ai.offset.y = 0;
		content.item = *items[i];

		sgui->frames[i] = new_frame(&ai, contentType, content);

		sprintf(sgui->frames[i]->title->content, "%s", items[i]->name);
		update_text(sgui->frames[i]->title);

		sprintf(sgui->frames[i]->coinText->content, "%d", items[i]->price);
		update_text(sgui->frames[i]->coinText);

		// todo, points en fonction de la collection
		strcpy(sgui->frames[i]->bundleTkText->content, "+1");
		update_text(sgui->frames[i]->bundleTkText);
	}
	//
	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

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
Hud* new_hud(Player player)
{
	Hud* hud = (Hud*)malloc(sizeof(Hud));
	int x = 20;

	hud->travelerIcon = player.traveler.sprite;
	hud->travelerIcon.ai = (AnchorInfo){AT_TOP_LEFT, {x, 10}, {50, 50}};
	x += hud->travelerIcon.ai.size.w + 10;


	hud->nick = new_text(player.nickname, 0, 0, 0, 0.5);
	hud->nick->sprite->ai = (AnchorInfo){AT_TOP_LEFT, {x, 5}, {hud->nick->sprite->ai.size.w, hud->nick->sprite->ai.size.h}};
	x += hud->nick->sprite->ai.size.w + 30;

	hud->coinIcon = textureMgr->coinIcon;
	hud->coinIcon.ai = (AnchorInfo){AT_TOP_LEFT, {x, 10}, {50, 50}};
	x += hud->coinIcon.ai.size.w + 5;

	hud->coinText = new_text("0", 0, 0, 0, 0.5);
	sprintf(hud->coinText->content, "%d", player.coins);
	update_text(hud->coinText);
	hud->coinText->sprite->ai = (AnchorInfo){AT_TOP_LEFT, {x, 5}, {hud->coinText->sprite->ai.size.w, hud->coinText->sprite->ai.size.h}};
	x += hud->coinText->sprite->ai.size.w + 30;

	hud->bundleTkIcon   = textureMgr->bundleTkIcon;
	hud->bundleTkIcon.ai = (AnchorInfo){AT_TOP_LEFT, {x, 0}, {70, 70}};
	x += hud->bundleTkIcon.ai.size.w + 5;

	hud->bundleTkText   = new_text("0", 0, 0, 0, 0.5);
	sprintf(hud->bundleTkText->content, "%d", player.bundleToken);
	update_text(hud->bundleTkText);
	hud->bundleTkText->sprite->ai = (AnchorInfo){AT_TOP_LEFT, {x, 5}, {hud->bundleTkText->sprite->ai.size.w, hud->bundleTkText->sprite->ai.size.h}};
	x += hud->bundleTkText->sprite->ai.size.w + 30;

	hud->templeCoinIcon = textureMgr->templeCoinIcon;
	hud->templeCoinIcon.ai = (AnchorInfo){AT_TOP_LEFT, {x, 0}, {70, 70}};
	x += hud->templeCoinIcon.ai.size.w + 5;

	hud->templeCoinText = new_text("0", 0, 0, 0, 0.5);
	sprintf(hud->templeCoinText->content, "%d", player.templeCoins);
	update_text(hud->templeCoinText);
	hud->templeCoinText->sprite->ai = (AnchorInfo){AT_TOP_LEFT, {x, 5}, {hud->templeCoinText->sprite->ai.size.w, hud->templeCoinText->sprite->ai.size.h}};
	x += hud->templeCoinText->sprite->ai.size.w;

	return hud;
}

void draw_hud(Hud* hud)
{
	AnchorInfo ai = {AT_TOP_LEFT, {0, 0}, {0, 70}};
	SDL_Rect rect = anchored_rect(ai, NULL);
	rect.w = windowAnchor.size.w;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
	SDL_RenderFillRect(renderer, &rect);
	draw_sprite(&hud->travelerIcon);
	draw_sprite(hud->nick->sprite);

	draw_sprite(&hud->coinIcon);
	draw_sprite(hud->coinText->sprite);

	draw_sprite(&hud->bundleTkIcon);
	draw_sprite(hud->bundleTkText->sprite);

	draw_sprite(&hud->templeCoinIcon);
	draw_sprite(hud->templeCoinText->sprite);
}

void destroy_hud(Hud* hud)
{
	free(hud);
}

// FRAME
Frame* new_frame(AnchorInfo* ai, ContentType contentType, Content content)
{
	Frame* frame = (Frame*)malloc(sizeof(Frame));

	frame->ai = *ai;

	frame->state = STATE_IDLE;
	frame->contentType = contentType;
	frame->content = content;
	if (frame->contentType == CONTENT_FOOD)
	{
		frame->content.food.sprite->parent = &frame->ai;
		frame->content.food.sprite->ai.offset.x = 0;
		frame->content.food.sprite->ai.offset.y = 35;
		frame->content.food.sprite->ai.at = AT_TOP_CENTER;
	}
	else if (frame->contentType == CONTENT_ITEM)
	{
		frame->content.item.sprite->parent = &frame->ai;
		frame->content.item.sprite->ai.offset.x = 0;
		frame->content.item.sprite->ai.offset.y = 35;
		frame->content.item.sprite->ai.at = AT_TOP_CENTER;
	}

	frame->bg = textureMgr->frame;
	frame->bg.parent = &frame->ai;
	frame->bg.ai.at = AT_TOP_CENTER;
	frame->bg.ai.offset.x = -3;
	frame->bg.ai.offset.y = -20;
	frame->bg.ai.size.w = frame->ai.size.w + 40;
	frame->bg.ai.size.h = frame->ai.size.h + 40;

	frame->title = new_text("Lorem Ipsum", 255, 255, 255, 0.5);
	frame->title->sprite->parent = &frame->ai;
	frame->title->sprite->ai.offset.y = 70;
	frame->title->sprite->ai.at = AT_CENTER;

	frame->coinIcon = textureMgr->coinIcon;
	frame->coinIcon.parent = &frame->ai;
	frame->coinIcon.ai.at = AT_BOTTOM_LEFT;
	frame->coinIcon.ai.offset.x = 20;
	frame->coinIcon.ai.offset.y = -10;

	frame->coinText = new_text("0", 255, 255, 255, 0.4);
	frame->coinText->sprite->parent = &frame->ai;
	frame->coinText->sprite->ai.at = AT_BOTTOM_LEFT;
	frame->coinText->sprite->ai.offset.x = frame->coinIcon.ai.offset.x + 50;
	frame->coinText->sprite->ai.offset.y = 10;

	frame->bundleTkIcon = textureMgr->bundleTkIcon;
	frame->bundleTkIcon.parent = &frame->ai;
	frame->bundleTkIcon.ai.at = AT_BOTTOM_LEFT;
	frame->bundleTkIcon.ai.offset.y = -10;
	frame->bundleTkIcon.ai.offset.x = frame->coinIcon.ai.offset.x + 90;

	frame->bundleTkText = new_text("0", 255, 255, 255, 0.4);
	frame->bundleTkText->sprite->parent = &frame->ai;
	frame->bundleTkText->sprite->ai.at = AT_BOTTOM_LEFT;
	frame->bundleTkText->sprite->ai.offset.x = frame->bundleTkIcon.ai.offset.x + 50;
	frame->bundleTkText->sprite->ai.offset.y = 10;

	return frame;
}

void draw_frame(Frame* frame)
{
	// printf("food\n");
	// print_ai(&frame->content.food.sprite->ai);
	// printf("bg\n");
	// print_ai(&frame->bg.ai);
	// printf("coinIcon\n");
	// print_ai(&frame->coinIcon.ai);
	// printf("coinText\n");
	// print_ai(&frame->coinText->sprite->ai);
	// printf("bundleTkIcon\n");
	// print_ai(&frame->bundleTkIcon.ai);
	// printf("bundleTkText\n");
	// print_ai(&frame->bundleTkText->sprite->ai);
	// printf("title\n");
	// print_ai(&frame->title->sprite->ai);

	state_color_mod(frame->bg.tex, frame->state);
	draw_sprite(&frame->bg);
	SDL_SetTextureColorMod(frame->bg.tex, 255, 255, 255);

	draw_sprite(frame->title->sprite);

	draw_sprite(&frame->coinIcon);
	draw_sprite(frame->coinText->sprite);

	draw_sprite(&frame->bundleTkIcon);
	draw_sprite(frame->bundleTkText->sprite);

	if (frame->contentType == CONTENT_FOOD)
	{
		draw_sprite(frame->content.food.sprite);
		// print_ai(&frame->content.food.sprite->ai);
	}
	else if (frame->contentType == CONTENT_ITEM)
	{
		draw_sprite(frame->content.item.sprite);
	}
}

void draw_square_gui(SquareGui* sgui)
{
	// printf("%d %d %d %d\n", sgui->menu->spriteCount, sgui->menu->textCount, sgui->menu->textboxCount, sgui->menu->buttonCount);
	draw_menu(sgui->menu);

	if (sgui->frames != NULL)
	{
		for (int i = 0; i < sgui->frameCount; i++)
		{
			draw_frame(sgui->frames[i]);
		}
	}
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
