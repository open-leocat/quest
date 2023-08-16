/* TODO: Optimize Display, bitmap writing routines */

#include "quest/state.h"
#include "quest/display.h"
#include "quest/input.h"
#include "quest/renderer.h"
#include "quest/player.h"

#include <stdint.h>
#include <stdbool.h>



const struct quest_sprite number_sprites[10] = {
	{
		4, 4,
		(const uint8_t[16]) {
			0, 1, 1, 0,
			0, 1, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 1, 0
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 0
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 1, 1, 0,
			0, 0, 0, 1,
			0, 0, 1, 1,
			0, 1, 1, 0
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 0, 0, 1,
			0, 0, 0, 1,
			0, 1, 1, 1,
			0, 1, 0, 1
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 1, 0, 0,
			0, 1, 1, 0
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 0, 1, 1,
			0, 1, 0, 1,
			0, 1, 1, 0,
			0, 1, 0, 0
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 0, 0, 1,
			0, 0, 0, 1,
			0, 1, 0, 1,
			0, 1, 1, 1
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 1, 1, 1,
			0, 1, 1, 1,
			0, 1, 0, 1,
			0, 1, 1, 1
		}
	},
	{
		4, 4,
		(const uint8_t[16]) {
			0, 0, 0, 1,
			0, 0, 1, 1,
			0, 1, 0, 1,
			0, 1, 1, 0,
		}
	}
};

const struct quest_sprite tile_sprite = {
		4, 4,
		(const uint8_t[16]) {
			1, 0, 0, 1,
			1, 1, 0, 0,
			1, 0, 1, 0,
			1, 1, 1, 1
		}
	};



struct quest_display* display;
struct quest_renderer renderer;
struct quest_state_manager manager;
struct quest_player player;



void game_state_initialize() {
	quest_renderer_initialize(&renderer);
	quest_renderer_set_display(&renderer, display);
	quest_renderer_set_camera_range_minimum(&renderer, 0, 0);

	quest_player_initialize(&player);
}

uint32_t delta = 0;

void game_state_update(uint32_t delta_time) {
	delta = delta_time;

	quest_player_update(&player, delta_time);
}

void game_state_render() {
	quest_display_clear(display);

	quest_player_render(&player, &renderer);

	for(uint32_t i = 0; i < 10; i++) {
		quest_renderer_draw_sprite(&renderer, i * 4, 0, &tile_sprite);
	}

	quest_display_set_bitmap(display, 0, 32 - 4, 4, 4, number_sprites[delta % 10].data);

	quest_display_show(display);
}

void game_state_terminate() {
	quest_renderer_terminate(&renderer);
	quest_display_terminate(display);
}

const struct quest_state game_state = {
	.initialize = game_state_initialize,
	.update = game_state_update,
	.render = game_state_render,
	.terminate = game_state_terminate
};

int main() {
	quest_input_initialize();

	display = quest_display_create();
	quest_display_initialize(display);

	quest_state_manager_initialize(&manager);
	quest_state_manager_set_current_state(&manager, &game_state);
	quest_state_manager_set_ups(&manager, 60);
	quest_state_manager_start(&manager);

	while(quest_state_manager_is_running(&manager)) {
		quest_state_manager_update(&manager);
	}

	quest_state_manager_terminate(&manager);
}
