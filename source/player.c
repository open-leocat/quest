#include "quest/player.h"

#include "quest/input.h"



const struct quest_sprite player_sprite = {
	8, 8,
	(const uint8_t[64]) {
		0, 1, 1, 1, 0, 1, 1, 0,
		1, 0, 0, 0, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 0, 1, 0,
		1, 0, 1, 0, 0, 0, 0, 1,
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 1, 1, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0,
		1, 0, 1, 1, 1, 1, 0, 0
	}
};



void quest_player_initialize(struct quest_player* player) {
	player->entity.x = 0;
	player->entity.y = 4;
	player->entity.width = 8;
	player->entity.height = 8;
	player->current_sprite = &player_sprite;
	player->movement_timer = 0;
	player->horizontal_input = 0;
	player->vertical_input = 0;
}

void quest_player_update(struct quest_player* player, uint32_t delta_time) {
	if(quest_input_is_pressed(QUEST_INPUT_UP_LEFT)) {
		player->horizontal_input = INT8_MIN;
	} else if(quest_input_is_pressed(QUEST_INPUT_UP_RIGHT)) {
		player->horizontal_input = INT8_MAX;
	} else {
		player->horizontal_input = 0;
	}

	player->movement_timer += delta_time;
	if(player->movement_timer >= 10000) {
		player->entity.x += (player->horizontal_input / INT8_MAX);

		player->movement_timer = 0;
	}
}

void quest_player_render(struct quest_player* player, struct quest_renderer* renderer) {
	quest_renderer_center(renderer, player->entity.x, player->entity.y, player->entity.width, player->entity.height);
	quest_renderer_draw_sprite(renderer, player->entity.x, player->entity.y, player->current_sprite);
}

void quest_player_terminate(struct quest_player* player) {
	(void) player;
}
