#ifndef QUEST_DISPLAY_H
#define QUEST_DISPLAY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



struct quest_display;



extern const size_t quest_display_width;
extern const size_t quest_display_height;



struct quest_display* quest_display_create();
void quest_display_initialize(struct quest_display* display);
void quest_display_show(struct quest_display* display);
void quest_display_set_pixel(struct quest_display* display, uint16_t x, uint16_t y, uint8_t color);
void quest_display_set_bitmap(struct quest_display* display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* bitmap);
void quest_display_clear(struct quest_display* display);
void quest_display_terminate(struct quest_display* display);



#endif
