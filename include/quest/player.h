#ifndef QUEST_PLAYER_H
#define QUEST_PLAYER_H

#include "quest/entity.h"
#include "quest/renderer.h"

#include <stdbool.h>
#include <stdint.h>



struct quest_player {
	struct quest_entity entity;

	const struct quest_sprite* current_sprite;

	uint32_t movement_timer;

	int8_t horizontal_input;
	int8_t vertical_input;
};


void quest_player_initialize(struct quest_player* player);
void quest_player_update(struct quest_player* player, uint32_t delta_time);
void quest_player_render(struct quest_player* player, struct quest_renderer* renderer);
void quest_player_terminate(struct quest_player* player);



#endif
