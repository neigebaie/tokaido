#include <square_draw.h>

SquareGui* new_inn_gui(Food** foods, int foodCount)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	sgui->menu = base_menu(1, 1, 0, 1);
	ContentType contentType = CONTENT_FOOD;
	Content content;

	sgui->menu->sprites[0] = &textureMgr->bg[4];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Relai", 255, 255, 255, 0.9);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->frameCount = foodCount;

	sgui->frames = (Frame**)malloc(sizeof(Frame*) * foodCount);
	AnchorInfo ai;
	ai.at = AT_CENTER;
	ai.size = (Size){220, 330};

	int j = 0;
	for (int i = 0; i < foodCount; i++)
	{
		ai.offset.x = ((i % 3) - 1) * 320;
		ai.offset.y = 400 * (int)(i/3) - 180;

		if (foods[i] == NULL)
		{
			sgui->frameCount--;
			content.food = *resources.foods[0];
			sgui->frames[j] = new_frame(&ai, contentType, content);
			sgui->frames[j]->sold = SDL_TRUE;
			sgui->frames[j]->state = STATE_DISABLED;
			printf("\e[36m[Inn] Empty Frame\e[37m\n");
		}
		else
		{
			content.food = *foods[i];

			sgui->frames[j] = new_frame(&ai, contentType, content);
			sgui->frames[j]->sold = SDL_FALSE;
			printf("\e[35m[Inn] New Frame : %s\e[37m\n", foods[i]->name);

			sprintf(sgui->frames[j]->title->content, "%s", foods[i]->name);
			update_text(sgui->frames[j]->title);

			sprintf(sgui->frames[j]->coinText->content, "%d", foods[i]->price);
			update_text(sgui->frames[j]->coinText);

			strcpy(sgui->frames[j]->bundleTkText->content, "+6");
			update_text(sgui->frames[j]->bundleTkText);

			j++;
		}
	}

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_shop_gui(Item* items[], Player* player)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	sgui->menu = base_menu(1, 1, 0, 1);
	ContentType contentType = CONTENT_ITEM;
	Content content;

	sgui->menu->sprites[0] = &textureMgr->bg[4];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Échoppe", 255, 255, 255, 0.9);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;


	sgui->frameCount = 3;

	sgui->frames = (Frame**)malloc(sizeof(Frame*) * sgui->frameCount);
	AnchorInfo ai;
	ai.at = AT_CENTER;
	ai.size = (Size){220, 330};

	for (int i = 0; i < sgui->frameCount; i++)
	{
		ai.offset.x = (i - 1) * 320;
		ai.offset.y = 0;
		content.item = *items[i];

		sgui->frames[i] = new_frame(&ai, contentType, content);
		sgui->frames[i]->sold = SDL_FALSE;

		sprintf(sgui->frames[i]->title->content, "%s", items[i]->name);
		update_text(sgui->frames[i]->title);

		sprintf(sgui->frames[i]->coinText->content, "%d", items[i]->price);
		update_text(sgui->frames[i]->coinText);

		sprintf(sgui->frames[i]->bundleTkText->content, "%d", tk_from_collection(*items[i], player->items, player->itemCount));
		update_text(sgui->frames[i]->bundleTkText);
	}
	//
	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_hot_spring_gui(int bundleToken)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	char obtained[256];

	sprintf(obtained, "Vous avez obtenu %d points de victoire.", bundleToken);

	sgui->menu = base_menu(1, 2, 0, 1);

	sgui->menu->sprites[0] = &textureMgr->bg[0];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Source Chaude", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->menu->texts[1] = new_text(obtained, 0, 0, 0, 0.8);
	sgui->menu->texts[1]->sprite->ai.at = AT_CENTER;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_temple_gui()
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));

	sgui->menu = base_menu(1, 1, 0, 2);

	sgui->menu->sprites[0] = &textureMgr->bg[0];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Temple", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Donner une pièce", 0.5, ACTION_TEMPLE, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_CENTER;

	sgui->menu->buttons[1] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[1]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[1]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_encounter_gui(int encounterId, char* obtained)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));

	sgui->menu = base_menu(1, 3, 0, 1);

	sgui->menu->sprites[0] = &textureMgr->bg[0];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Rencontre", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->menu->texts[1] = new_text("Vous avez obtenu :", 0, 0, 0, 0.8);
	sgui->menu->texts[1]->sprite->ai.at = AT_CENTER;
	sgui->menu->texts[1]->sprite->ai.offset.y = -80;
	sgui->menu->texts[2] = new_text(obtained, 0, 0, 0, 0.8);
	sgui->menu->texts[2]->sprite->ai.at = AT_CENTER;
	sgui->menu->texts[2]->sprite->ai.offset.y = 80;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_farm_gui()
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));

	sgui->menu = base_menu(1, 2, 0, 1);

	sgui->menu->sprites[0] = &textureMgr->bg[0];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Ferme", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->menu->texts[1] = new_text("Vous avez obtenu 3 pièces.", 0, 0, 0, 0.8);
	sgui->menu->texts[1]->sprite->ai.at = AT_CENTER;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_pan_rice_gui(int nb)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	char obtained[256];

	sprintf(obtained, "Rizière : %d/3", nb);

	sgui->menu = base_menu(1, 2, 0, 1);

	sgui->menu->sprites[0] = &textureMgr->bg[1];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Panorama", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->menu->texts[1] = new_text(obtained, 0, 0, 0, 0.8);
	sgui->menu->texts[1]->sprite->ai.at = AT_CENTER;
	sgui->menu->texts[1]->sprite->ai.offset.y = 200;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_pan_mount_gui(int nb)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	char obtained[256];

	sprintf(obtained, "Montagne : %d/4", nb);

	sgui->menu = base_menu(1, 2, 0, 1);

	sgui->menu->sprites[0] = &textureMgr->bg[2];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Panorama", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->menu->texts[1] = new_text(obtained, 0, 0, 0, 0.8);
	sgui->menu->texts[1]->sprite->ai.at = AT_CENTER;
	sgui->menu->texts[1]->sprite->ai.offset.y = 200;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

SquareGui* new_pan_sea_gui(int nb)
{
	SquareGui* sgui = (SquareGui*)malloc(sizeof(SquareGui));
	char obtained[256];

	sprintf(obtained, "Mer : %d/5", nb);

	sgui->menu = base_menu(1, 2, 0, 1);

	sgui->menu->sprites[0] = &textureMgr->bg[3];
	sgui->menu->sprites[0]->ai.at = AT_CENTER;

	sgui->menu->texts[0] = new_text("Panorama", 0, 0, 0, 1);
	sgui->menu->texts[0]->sprite->ai.at = AT_TOP_CENTER;
	sgui->menu->texts[0]->sprite->ai.offset.y = 80;

	sgui->menu->texts[1] = new_text(obtained, 0, 0, 0, 0.8);
	sgui->menu->texts[1]->sprite->ai.at = AT_CENTER;
	sgui->menu->texts[1]->sprite->ai.offset.y = 200;

	sgui->frameCount = 0;
	sgui->frames = NULL;

	sgui->menu->buttons[0] = new_button("Retour", 0.5, ACTION_END_TURN, MENU_NONE);
	sgui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	sgui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return sgui;
}

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

void update_hud(Hud* hud, Player player)
{
	sprintf(hud->coinText->content, "%d", player.coins);
	sprintf(hud->bundleTkText->content, "%d", player.bundleToken);
	sprintf(hud->templeCoinText->content, "%d", player.templeCoins);
	update_text(hud->coinText);
	update_text(hud->bundleTkText);
	update_text(hud->templeCoinText);
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
	frame->sold = SDL_FALSE;
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
	if (frame->sold)
		return;

	state_color_mod(frame->bg.tex, &frame->state);
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
