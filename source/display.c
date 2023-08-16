#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#include "quest/display.h"

#include <string.h>
#include <stdlib.h>



struct quest_display {
	uint8_t* buffer;

	spi_inst_t* spi;
};

enum quest_display_command {
	QUEST_DISPLAY_COMMAND_NOOP = 0,
	QUEST_DISPLAY_COMMAND_DIGIT0 = 1,
	QUEST_DISPLAY_COMMAND_DECODEMODE = 9,
	QUEST_DISPLAY_COMMAND_INTENSITY = 10,
	QUEST_DISPLAY_COMMAND_SCANLIMIT = 11,
	QUEST_DISPLAY_COMMAND_SHUTDOWN = 12,
	QUEST_DISPLAY_COMMAND_DISPLAYTEST = 15
};

const size_t quest_display_internal_width = 128;
const size_t quest_display_internal_height = 8;

const size_t quest_display_width = 32;
const size_t quest_display_height = 32;

const size_t quest_display_count = 16;

const uint32_t sck_pin = 2;
const uint32_t mosi_pin = 3;
const uint32_t cs_pin = 5;



struct quest_display* quest_display_create() {
	return malloc(sizeof(struct quest_display));
}

void quest_display_write_command(struct quest_display* display, uint8_t address, uint8_t data) {
	gpio_put(cs_pin, 0);

	for (size_t m = 0; m < quest_display_count; m++) {
		spi_write_blocking(display->spi, &address, 1);
		spi_write_blocking(display->spi, &data, 1);
	}

	gpio_put(cs_pin, 1);
}

void quest_display_set_brightness(struct quest_display* display, uint8_t brightness) {
	if (brightness > 15) {
		brightness = 15;
	}
	quest_display_write_command(display, QUEST_DISPLAY_COMMAND_INTENSITY, brightness);
}

void quest_display_show(struct quest_display* display) {
	for (size_t y = 0; y < quest_display_internal_height; y++) {
		gpio_put(cs_pin, 0);

		for (size_t x = 0; x < quest_display_count; x++) {
			uint8_t address = QUEST_DISPLAY_COMMAND_DIGIT0 + y;
			spi_write_blocking(display->spi, &address, 1);
			spi_write_blocking(display->spi, display->buffer + y * quest_display_count + x, 1);
		}

		gpio_put(cs_pin, 1);
	}
}

/* TODO: Remove / Optimize */
void quest_display_set_pixel(struct quest_display* display, uint16_t x, uint16_t y, uint8_t color) {
	/* Ensure coordinates are within bounds */
	if(x >= quest_display_width || y >= quest_display_height) {
		return;
	}

	/* Simplified coordinate translation */
	uint16_t translated_x = ((x / quest_display_internal_height) * quest_display_width) + (quest_display_width - 1 - y);
	uint16_t translated_y = quest_display_internal_height - 1 - (x % quest_display_internal_height);

	/* Ensure translated coordinates are within bounds */
	if(translated_x >= quest_display_internal_width || translated_y >= quest_display_internal_height) {
		return;
	}

	/* Update buffer offset and bit mask */
	uint8_t buffer_offset = translated_y * quest_display_count + translated_x / 8;
	uint8_t bit_mask = 1 << (7 - (translated_x % 8));

	/* Update buffer */
	if (color) {
		display->buffer[buffer_offset] |= bit_mask;
	} else {
		display->buffer[buffer_offset] &= ~bit_mask;
	}
}

void quest_display_clear(struct quest_display* display) {
	memset(display->buffer, 0, quest_display_internal_width * quest_display_internal_height / 8);
}

void quest_display_initialize(struct quest_display* display) {
	display->buffer = malloc(quest_display_internal_width * quest_display_internal_height / 8);

	display->spi = spi0;
	spi_init(display->spi, 1000 * 1000); /* Reduce or increase? Not enough current in Pico */
	/* spi_init(display->spi, 1000 * 1000); */
	gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
	gpio_set_function(sck_pin, GPIO_FUNC_SPI);
	gpio_set_function(cs_pin, GPIO_FUNC_SIO);
	gpio_init(cs_pin);
	gpio_set_dir(cs_pin, GPIO_OUT);

	quest_display_write_command(display, QUEST_DISPLAY_COMMAND_SHUTDOWN, 0);
	quest_display_write_command(display, QUEST_DISPLAY_COMMAND_DISPLAYTEST, 0);
	quest_display_write_command(display, QUEST_DISPLAY_COMMAND_SCANLIMIT, 7);
	quest_display_write_command(display, QUEST_DISPLAY_COMMAND_DECODEMODE, 0);
	quest_display_write_command(display, QUEST_DISPLAY_COMMAND_SHUTDOWN, 1);

	quest_display_set_brightness(display, 2);
}

/* TODO: Remove / Optimize */
void quest_display_set_bitmap(struct quest_display* display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t* bitmap) {
	for(uint16_t bitmap_y = 0; bitmap_y < height; bitmap_y++) {
		for(uint16_t bitmap_x = 0; bitmap_x < width; bitmap_x++) {
			quest_display_set_pixel(display, x + bitmap_x, y + bitmap_y, bitmap[bitmap_x + bitmap_y * width]);
		}
	}
}

void quest_display_terminate(struct quest_display* display) {
	free(display->buffer);
	free(display);
}
