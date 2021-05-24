#include <square_draw.h>

SquareGui* new_inn_gui(Food** foods, int foodCount, Player* player)
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
	int alreadyTasted = 0;
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
			alreadyTasted = 0;
			for (int f = 0; f < player->foodCount; f++) {
				if (strcmp(player->foods[f].name, foods[i]->name) == 0)
				{
					alreadyTasted = 1;
					break;
				}
			}

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

			if (alreadyTasted || foods[i]->price > player->coins)
			{
				sgui->frames[j]->state = STATE_DISABLED;
			}

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

		if (items[i]->price > player->coins)
		{
			sgui->frames[i]->state = STATE_DISABLED;
		}
	}
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

// Game over
AchievementsGui* new_achievements_gui(Lboard* lboard, Player* players, int playerCount)
{
	AchievementsGui* achievementsGui = (AchievementsGui*)malloc(sizeof(AchievementsGui));
	achievementsGui->menu = base_menu(1, 0, 0, 1);
	int offsetX[] = {-468, -468, -468, -468, 312, 312, 312, 312};
	int offsetY[] = {-166, -24, 119, 261, -166, -24, 119, 261};
	achievementsGui->menu->sprites[0] = &textureMgr->bg[8];

	achievementsGui->playerIcons[0] = lboard->riceList[0]->traveler.sprite;
	printf("%s\n", lboard->riceList[0]->nickname);
	achievementsGui->playerIcons[1] = lboard->mountList[0]->traveler.sprite;
	printf("%s\n", lboard->mountList[0]->nickname);
	achievementsGui->playerIcons[2] = lboard->seaList[0]->traveler.sprite;
	printf("%s\n", lboard->seaList[0]->nickname);
	achievementsGui->playerIcons[3] = lboard->templeList[0]->traveler.sprite;
	printf("%s\n", lboard->templeList[0]->nickname);
	achievementsGui->playerIcons[4] = lboard->encounterList[0]->traveler.sprite;
	printf("%s\n", lboard->encounterList[0]->nickname);
	achievementsGui->playerIcons[5] = lboard->shopList[0]->traveler.sprite;
	printf("%s\n", lboard->shopList[0]->nickname);
	achievementsGui->playerIcons[6] = lboard->hotSpringList[0]->traveler.sprite;
	printf("%s\n", lboard->hotSpringList[0]->nickname);
	achievementsGui->playerIcons[7] = lboard->innList[0]->traveler.sprite;
	printf("%s\n", lboard->innList[0]->nickname);
	for (int i = 0; i < 8; i++) {
		achievementsGui->playerIcons[i].ai.offset.x = offsetX[i];
		achievementsGui->playerIcons[i].ai.offset.y = offsetY[i];
		achievementsGui->playerIcons[i].ai.at = AT_CENTER;
		achievementsGui->playerIcons[i].ai.size.w = 90;
		achievementsGui->playerIcons[i].ai.size.h = 90;
		printf("offset = %d %d\n", achievementsGui->playerIcons[i].ai.offset.x, achievementsGui->playerIcons[i].ai.offset.y);
	}

	achievementsGui->menu->buttons[0] = new_button("Suivant", 0.5, ACTION_NONE, MENU_NONE);
	achievementsGui->menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	achievementsGui->menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	return achievementsGui;
}

void draw_achievements_gui(AchievementsGui* achievementsGui)
{
	draw_menu(achievementsGui->menu);
	for (int i = 0; i < 8; i++) {
		draw_sprite(&achievementsGui->playerIcons[i]);
	}
}

Menu* new_game_over_gui(Player* players, int playerCount)
{
	Player** sortedPlayers = (Player**)malloc(sizeof(Player*) * playerCount);
	for (int row = 0; row < playerCount; row++) {
		sortedPlayers[row] = &players[row];
	}
	qsort(sortedPlayers, playerCount, sizeof(Player*), cmpfunc_bundle_tk);
	Menu* menu = base_menu(1 + playerCount, playerCount, 0, 1);
	int offsetX[] = {-600, -300, 0, 300, 600};
	int offsetY[] = {-30, 20, 70, 130, 130};
	menu->sprites[0] = &textureMgr->bg[7];
	menu->sprites[0]->ai.at = AT_CENTER;

	for (int i = 1; i < 1 + playerCount; i++) {
		menu->sprites[i] = &sortedPlayers[i - 1]->traveler.sprite;
		menu->sprites[i]->ai.at = AT_CENTER;
		menu->sprites[i]->ai.offset.x = offsetX[i - 1];
		menu->sprites[i]->ai.offset.y = offsetY[i - 1];
		menu->sprites[i]->ai.size.w = 150;
		menu->sprites[i]->ai.size.h = 150;

		menu->texts[i - 1] = new_text("0", 255, 255, 255, 0.8);
		menu->texts[i - 1]->sprite->ai.at = AT_CENTER;
		menu->texts[i - 1]->sprite->ai.offset.x = offsetX[i - 1] + 10;
		menu->texts[i - 1]->sprite->ai.offset.y = offsetY[i - 1] + 170 - 30 * (i>=4);
		sprintf(menu->texts[i - 1]->content, "%d", sortedPlayers[i - 1]->bundleToken);
		update_text(menu->texts[i - 1]);
	}

	menu->buttons[0] = new_button("Menu", 0.5, ACTION_NONE, MENU_MAIN);
	menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
	menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};

	// printf("it worked\n");
	return menu;
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

// LEADERBOARD
Lboard* new_lboard(Player* players, int playerCount)
{
	Lboard* lboard = (Lboard*)malloc(sizeof(Lboard));
	const int deltaX = 150;
	const int deltaY = 120;
	lboard->riceList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->mountList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->seaList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->templeList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->encounterList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->shopList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->hotSpringList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->innList = (Player**)malloc(sizeof(Player*) * playerCount);
	lboard->bundleTkList = (Player**)malloc(sizeof(Player*) * playerCount);

	for (int row = 0; row < playerCount; row++) {
		lboard->riceList[row] = &players[row];
		printf("%s\n", lboard->riceList[row]->nickname);
		lboard->mountList[row] = &players[row];
		lboard->seaList[row] = &players[row];
		lboard->templeList[row] = &players[row];
		lboard->encounterList[row] = &players[row];
		lboard->shopList[row] = &players[row];
		lboard->hotSpringList[row] = &players[row];
		lboard->innList[row] = &players[row];
		lboard->bundleTkList[row] = &players[row];
		for (int col = 0; col < 8; col++) {
			lboard->playerIcons[col][row] = players[row].traveler.sprite;
			lboard->playerIcons[col][row].ai.at = AT_CENTER;
			lboard->playerIcons[col][row].ai.offset.x = 0.5 * deltaX + (-0.5) * deltaX * 8 + col * deltaX;
			lboard->playerIcons[col][row].ai.offset.y = 180 + 60 + (-0.5) * deltaY * 5 + row * deltaY;
			lboard->playerIcons[col][row].ai.size.w *= .7 + .2 * (row == 0);
			lboard->playerIcons[col][row].ai.size.h *= .7 + .2 * (row == 0);
		}
		lboard->playerIcons[8][row] = players[row].traveler.sprite;
		lboard->playerIcons[8][row].ai.at = AT_CENTER;
		lboard->playerIcons[8][row].ai.offset.x = 0.5 * deltaX * 8/6 + (-0.5) * deltaX * 8 + (row + 1) * deltaX * 8/6;
		lboard->playerIcons[8][row].ai.offset.y = -50 + (-0.5) * deltaY * 5;
		lboard->playerIcons[8][row].ai.size.w *= .7 + .4 * (row == 0);
		lboard->playerIcons[8][row].ai.size.h *= .7 + .4 * (row == 0);
	}

	lboard->bg = textureMgr->bg[5];
	for (int col = 0; col < 8; col++) {
		lboard->colIcons[col] = textureMgr->lbIcons[col];
		lboard->colIcons[col].ai.at = AT_CENTER;
		lboard->colIcons[col].ai.offset.x = 0.5 * deltaX + (-0.5) * deltaX * 8 + col * deltaX;
		lboard->colIcons[col].ai.offset.y = 170 + (-0.5) * deltaY * 6;
		for (int row = 0; row < playerCount; row++) {
			lboard->texts[col][row] = new_text("0", 255, 255, 255, 0.5);
			lboard->texts[col][row]->sprite->ai.at = AT_CENTER;
			lboard->texts[col][row]->sprite->ai.offset.x = 50 + 5 * (row == 0) + 0.5 * deltaX + (-0.5) * deltaX * 8 + col * deltaX;
			lboard->texts[col][row]->sprite->ai.offset.y = 270 + 20 * (row == 0) + (-0.5) * deltaY * 5 + row * deltaY;
		}
	}

	for (int row = 0; row < playerCount; row++) {
		lboard->texts[8][row] = new_text("0", 255, 255, 255, 0.5);
		lboard->texts[8][row]->sprite->ai.at = AT_CENTER;
		lboard->texts[8][row]->sprite->ai.offset.x = 70 + 20 * (row == 0) + 0.5 * deltaX + (-0.5) * deltaX * 8 + (row + 1) * deltaX * 8/6;
		lboard->texts[8][row]->sprite->ai.offset.y = 10 * (row == 0) + (-0.5) * deltaY * 5;
	}
	return lboard;
}

int cmpfunc_rice(const void* a, const void* b)
{
	return (*(Player**)b)->panRice - (*(Player**)a)->panRice;
}

int cmpfunc_mount(const void* a, const void* b)
{
	return (*(Player**)b)->panMount - (*(Player**)a)->panMount;
}

int cmpfunc_sea(const void* a, const void* b)
{
	return (*(Player**)b)->panSea - (*(Player**)a)->panSea;
}

int cmpfunc_temple(const void* a, const void* b)
{
	return (*(Player**)b)->templeCoins - (*(Player**)a)->templeCoins;
}

int cmpfunc_encounter(const void* a, const void* b)
{
	return (*(Player**)b)->encounterCount - (*(Player**)a)->encounterCount;
}

int cmpfunc_shop(const void* a, const void* b)
{
	return (*(Player**)b)->itemCount - (*(Player**)a)->itemCount;
}

int cmpfunc_hot_spring(const void* a, const void* b)
{
	return (*(Player**)b)->hotSpringCount - (*(Player**)a)->hotSpringCount;
}

int cmpfunc_inn(const void* a, const void* b)
{
	return (*(Player**)b)->innCoins - (*(Player**)a)->innCoins;
}

int cmpfunc_bundle_tk(const void* a, const void* b)
{
	return (*(Player**)b)->bundleToken - (*(Player**)a)->bundleToken;
}

void update_lboard(Lboard* lboard, Player* players, int playerCount)
{
	// sort every list
	qsort(lboard->riceList, playerCount, sizeof(Player*), (compfn)cmpfunc_rice);
	qsort(lboard->mountList, playerCount, sizeof(Player*), (compfn)cmpfunc_mount);
	qsort(lboard->seaList, playerCount, sizeof(Player*), (compfn)cmpfunc_sea);
	qsort(lboard->templeList, playerCount, sizeof(Player*), (compfn)cmpfunc_temple);
	qsort(lboard->encounterList, playerCount, sizeof(Player*), (compfn)cmpfunc_encounter);
	qsort(lboard->shopList, playerCount, sizeof(Player*), (compfn)cmpfunc_shop);
	qsort(lboard->hotSpringList, playerCount, sizeof(Player*), (compfn)cmpfunc_hot_spring);
	qsort(lboard->innList, playerCount, sizeof(Player*), (compfn)cmpfunc_inn);
	qsort(lboard->bundleTkList, playerCount, sizeof(Player*), cmpfunc_bundle_tk);

	for (int i = 0; i < playerCount; i++) {
		lboard->playerIcons[0][i].crop = lboard->riceList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[0][i]->content, "%d", lboard->riceList[i]->panRice);
		lboard->playerIcons[1][i].crop = lboard->mountList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[1][i]->content, "%d", lboard->mountList[i]->panMount);

		lboard->playerIcons[2][i].crop = lboard->seaList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[2][i]->content, "%d", lboard->seaList[i]->panSea);

		lboard->playerIcons[3][i].crop = lboard->templeList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[3][i]->content, "%d", lboard->templeList[i]->templeCoins);

		lboard->playerIcons[4][i].crop = lboard->encounterList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[4][i]->content, "%d", lboard->encounterList[i]->encounterCount);

		lboard->playerIcons[5][i].crop = lboard->shopList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[5][i]->content, "%d", lboard->shopList[i]->itemCount);
		printf("[shop] %s : %d\n", lboard->shopList[i]->nickname, lboard->shopList[i]->itemCount);

		lboard->playerIcons[6][i].crop = lboard->hotSpringList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[6][i]->content, "%d", lboard->hotSpringList[i]->hotSpringCount);

		lboard->playerIcons[7][i].crop = lboard->innList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[7][i]->content, "%d", lboard->innList[i]->innCoins);

		lboard->playerIcons[8][i].crop = lboard->bundleTkList[i]->traveler.sprite.crop;
		sprintf(lboard->texts[8][i]->content, "%d", lboard->bundleTkList[i]->bundleToken);

		for (int col = 0; col < 9; col++) {
			update_text(lboard->texts[col][i]);
		}
	}
}

void draw_lboard(Lboard* lboard)
{
	draw_sprite(&lboard->bg);
	for (int col = 0; col < 8; col++) {
		draw_sprite(&lboard->colIcons[col]);
		for (int row = 0; row < 5; row++) {
			if (lboard->texts[col][row]->content[0] != '0')
			{
				draw_sprite(lboard->texts[col][row]->sprite);
				draw_sprite(&lboard->playerIcons[col][row]);
			}
		}
	}
	for (int row = 0; row < 5; row++) {
		draw_sprite(lboard->texts[8][row]->sprite);
		draw_sprite(&lboard->playerIcons[8][row]);
	}
}

void destroy_lboard(Lboard* lboard)
{
	free(lboard);
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

// Menu* new_yoshiyasu_menu(int encounterId1, int encounterId2)
// {
// 		Menu* menu = base_menu(2, 2, 0, 2)
//
// 		menu->texts[0] = new_text("Rencontre 1", 0, 0, 0, 0.5);
// 		menu->texts[0]->sprite->ai.at = AT_CENTER;
// 		menu->texts[0]->sprite->ai.offset = (Offset){-150, 50};
// 		menu->texts[1] = new_text("Rencontre 2", 0, 0, 0, 0.5);
// 		menu->texts[1]->sprite->ai.at = AT_CENTER;
// 		menu->texts[1]->sprite->ai.offset = (Offset){150, 50};
//
// 		menu->buttons[0] = new_button("Rencontre 1",0.5, ACTION_NONE, MENU_NONE);
// 		menu->buttons[0]->sprite->ai.offset = (Offset){-200, 0};
// 		menu->buttons[0]->sprite->ai.at = AT_CENTER;
// 		menu->buttons[1] = new_button("Rencontre 2",0.5, ACTION_NONE, MENU_NONE);
// 		menu->buttons[1]->sprite->ai.offset = (Offset){200, 0};
// 		menu->buttons[1]->sprite->ai.at = AT_CENTER;
//
// }
//
// Menu* new_Hiroshige_menu()
// {
// 		Menu* menu = base_menu(3, 3, 0, 3)
//
// 		menu->texts[0] = new_text("Panorama Montagne", 0, 0, 0, 0.5);
// 		menu->texts[0]->sprite->ai.at = AT_CENTER;
// 		menu->texts[0]->sprite->ai.offset = (Offset){-200,50};
// 		menu->texts[1] = new_text("Panorama Rizière", 0, 0, 0, 0.5);
// 		menu->texts[1]->sprite->ai.at = AT_CENTER;
// 		menu->texts[1]->sprite->ai.offset = (Offset){0,50};
// 		menu->texts[2] = new_text("Panorama Mer", 0, 0, 0, 0.5);
// 		menu->texts[2]->sprite->ai.at = AT_CENTER;
// 		menu->texts[2]->sprite->ai.offset = (Offset){200,50};
//
// 		menu->buttons[0] = new_button("Choix Panorama Montagne",0.5, ACTION_NONE, MENU_NONE);
// 		menu->buttons[0]->sprite->ai.offset = (Offset){-200, 0};
// 		menu->buttons[0]->sprite->ai.at = AT_CENTER;
// 		menu->buttons[1] = new_button("Choix Panorama Rizière",0.5, ACTION_NONE, MENU_NONE);
// 		menu->buttons[1]->sprite->ai.offset = (Offset){0, 0};
// 		menu->buttons[1]->sprite->ai.at = AT_CENTER;
// 		menu->buttons[2] = new_button("Choix Panorama Mer",0.5, ACTION_NONE, MENU_NONE);
// 		menu->buttons[2]->sprite->ai.offset = (Offset){200, 0};
// 		menu->buttons[2]->sprite->ai.at = AT_CENTER;
//
// }
//
// Menu* new_Satsuki_menu(int foodId))
// {
// 		Menu* menu = base_menu(1, 1, 0, 2)
//
// 		menu->texts[0] = new_text("Repas Gratuit", 0, 0, 0, 1);
// 		menu->texts[0]->sprite->ai.at = AT_CENTER;
// 		menu->texts[0]->sprite->ai.offset = (Offset){0,100};
//
// 		menu->buttons[0] = new_button("Accepter",0.5, ACTION_NONE, MENU_NONE);
// 		menu->buttons[0]->sprite->ai.offset = (Offset){0, -50};
// 		menu->buttons[0]->sprite->ai.at = AT_CENTER;
// 		menu->buttons[1] = new_button("Refuser",0.5, ACTION_END_TURN, MENU_NONE);
// 		menu->buttons[0]->bg.ai.at = AT_BOTTOM_RIGHT;
// 		menu->buttons[0]->bg.ai.offset = (Offset){-10, -10};
//
// }
