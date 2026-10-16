#ifndef MOBILE_TOUCH_ART_H
#define MOBILE_TOUCH_ART_H

#include "mac_sdl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Authentic Command & Conquer: Red Alert (Westwood 1996) Tactical Palette
 */
typedef struct {
	Uint8 r, g, b, a;
} RAColor;

static const RAColor RA_CHASSIS_BG        = { 22,  26,  32, 230 };
static const RAColor RA_CHASSIS_BG_GRAIN  = { 28,  33,  40, 230 };
static const RAColor RA_CHASSIS_BORDER_DARK = { 12,  15,  18, 255 };
static const RAColor RA_CHASSIS_HIGHLIGHT = { 108, 116, 126, 220 };
static const RAColor RA_CHASSIS_SHADOW    = { 18,  21,  25, 255 };

static const RAColor RA_STEEL_OUTLINE     = { 14,  17,  20, 255 };
static const RAColor RA_STEEL_LIGHT_OUTER = { 220, 226, 232, 255 };
static const RAColor RA_STEEL_LIGHT_INNER = { 170, 178, 186, 255 };
static const RAColor RA_STEEL_SHADOW_OUTER= { 22,  25,  28, 255 };
static const RAColor RA_STEEL_SHADOW_INNER= { 48,  54,  60, 255 };
static const RAColor RA_STEEL_FACE_A      = { 115, 122, 130, 255 };
static const RAColor RA_STEEL_FACE_B      = { 126, 134, 142, 255 };
static const RAColor RA_STEEL_FACE_C      = { 102, 109, 117, 255 };
static const RAColor RA_STEEL_PRESSED_FACE= { 72,  77,  84, 255 };

static const RAColor RA_GOLD_SHEEN        = { 255, 240, 160, 255 };
static const RAColor RA_GOLD_HIGHLIGHT    = { 240, 196,  64, 255 };
static const RAColor RA_GOLD_BODY         = { 190, 142,  36, 255 };
static const RAColor RA_GOLD_SHADOW       = { 110,  78,  18, 255 };
static const RAColor RA_GOLD_OUTLINE      = { 42,   28,   6, 255 };

static const RAColor RA_ALERT_RED         = { 225,  32,  24, 255 };
static const RAColor RA_ALERT_RED_GLOW    = { 255,  80,  70, 255 };
static const RAColor RA_ALERT_RED_PEAK    = { 255, 200, 195, 255 };

static const RAColor RA_LED_GREEN_RIM     = { 12,   28,  16, 255 };
static const RAColor RA_LED_GREEN_ON      = { 36,  224,  58, 255 };
static const RAColor RA_LED_GREEN_CORE    = { 180, 255, 190, 255 };
static const RAColor RA_LED_GREEN_OFF     = { 26,   42,  30, 240 };

static const RAColor RA_TACTICAL_AMBER    = { 255, 198,  20, 255 };
static const RAColor RA_TACTICAL_CYAN     = { 90,  210, 255, 255 };
static const RAColor RA_TACTICAL_WHITE    = { 242, 246, 250, 255 };
static const RAColor RA_TACTICAL_SHADOW   = { 16,   19,  22, 255 };

static inline void MobileArt_SetColor(SDL_Renderer *renderer, RAColor c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

/* Helper to render a thick line */
static inline void MobileArt_DrawThickLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int thickness)
{
	if (thickness <= 1) {
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		return;
	}
	int half = thickness / 2;
	for (int dy = -half; dy <= half; ++dy) {
		for (int dx = -half; dx <= half; ++dx) {
			if (dx * dx + dy * dy <= half * half + 1) {
				SDL_RenderDrawLine(renderer, x1 + dx, y1 + dy, x2 + dx, y2 + dy);
			}
		}
	}
}

/* Draws a realistic 3D metallic rivet / screw head like on the radar console */
static inline void MobileArt_DrawRivet(SDL_Renderer *renderer, int cx, int cy, int radius)
{
	if (radius < 2) radius = 2;
	/* Outer dark shadow ring */
	MobileArt_SetColor(renderer, RA_STEEL_OUTLINE);
	SDL_Rect r_base = { cx - radius, cy - radius, radius * 2 + 1, radius * 2 + 1 };
	SDL_RenderFillRect(renderer, &r_base);

	/* Steel body */
	MobileArt_SetColor(renderer, RA_STEEL_FACE_A);
	SDL_Rect r_body = { cx - radius + 1, cy - radius + 1, (radius - 1) * 2 + 1, (radius - 1) * 2 + 1 };
	SDL_RenderFillRect(renderer, &r_body);

	/* Specular top-left light */
	MobileArt_SetColor(renderer, RA_STEEL_LIGHT_OUTER);
	SDL_RenderDrawLine(renderer, cx - radius + 1, cy - radius + 1, cx + radius - 1, cy - radius + 1);
	SDL_RenderDrawLine(renderer, cx - radius + 1, cy - radius + 1, cx - radius + 1, cy + radius - 1);

	/* Bottom-right shadow */
	MobileArt_SetColor(renderer, RA_STEEL_SHADOW_OUTER);
	SDL_RenderDrawLine(renderer, cx - radius + 1, cy + radius - 1, cx + radius - 1, cy + radius - 1);
	SDL_RenderDrawLine(renderer, cx + radius - 1, cy - radius + 1, cx + radius - 1, cy + radius - 1);

	/* Center screw slot */
	MobileArt_SetColor(renderer, RA_STEEL_OUTLINE);
	int slot_len = radius - 1;
	if (slot_len < 1) slot_len = 1;
	SDL_RenderDrawLine(renderer, cx - slot_len, cy, cx + slot_len, cy);
}

/* Draws the native Command & Conquer steel chassis / dock frame */
static inline void MobileArt_DrawDockChassis(SDL_Renderer *renderer, SDL_Rect dock, int scale)
{
	int bevel = (scale >= 3) ? 2 : 1;
	int rivet_rad = (scale >= 3) ? 3 : 2;
	int rivet_inset = rivet_rad + bevel + 1;

	/* Outer black boundary */
	MobileArt_SetColor(renderer, RA_CHASSIS_BORDER_DARK);
	SDL_RenderDrawRect(renderer, &dock);

	/* Interior base fill */
	SDL_Rect inside = { dock.x + 1, dock.y + 1, dock.w - 2, dock.h - 2 };
	MobileArt_SetColor(renderer, RA_CHASSIS_BG);
	SDL_RenderFillRect(renderer, &inside);

	/* Horizontal brushed scanlines across dock background */
	MobileArt_SetColor(renderer, RA_CHASSIS_BG_GRAIN);
	for (int y = inside.y; y < inside.y + inside.h; y += 3) {
		SDL_RenderDrawLine(renderer, inside.x, y, inside.x + inside.w - 1, y);
	}

	/* Steel frame bevels */
	MobileArt_SetColor(renderer, RA_CHASSIS_HIGHLIGHT);
	for (int b = 0; b < bevel; ++b) {
		/* Top and right inner highlights */
		SDL_RenderDrawLine(renderer, inside.x + b, inside.y + b, inside.x + inside.w - 1 - b, inside.y + b);
		SDL_RenderDrawLine(renderer, inside.x + inside.w - 1 - b, inside.y + b, inside.x + inside.w - 1 - b, inside.y + inside.h - 1 - b);
	}
	MobileArt_SetColor(renderer, RA_CHASSIS_SHADOW);
	for (int b = 0; b < bevel; ++b) {
		/* Bottom and left inner shadows */
		SDL_RenderDrawLine(renderer, inside.x + b, inside.y + inside.h - 1 - b, inside.x + inside.w - 1 - b, inside.y + inside.h - 1 - b);
		SDL_RenderDrawLine(renderer, inside.x + b, inside.y + b, inside.x + b, inside.y + inside.h - 1 - b);
	}

	/* Corner metallic rivets */
	MobileArt_DrawRivet(renderer, dock.x + rivet_inset, dock.y + rivet_inset, rivet_rad);
	MobileArt_DrawRivet(renderer, dock.x + dock.w - rivet_inset, dock.y + rivet_inset, rivet_rad);
	MobileArt_DrawRivet(renderer, dock.x + rivet_inset, dock.y + dock.h - rivet_inset, rivet_rad);
	MobileArt_DrawRivet(renderer, dock.x + dock.w - rivet_inset, dock.y + dock.h - rivet_inset, rivet_rad);
}

/* Draws panel divider groove between tactical sections */
static inline void MobileArt_DrawDividerGroove(SDL_Renderer *renderer, int x1, int x2, int y)
{
	MobileArt_SetColor(renderer, RA_CHASSIS_SHADOW);
	SDL_RenderDrawLine(renderer, x1, y, x2, y);
	MobileArt_SetColor(renderer, RA_CHASSIS_HIGHLIGHT);
	SDL_RenderDrawLine(renderer, x1, y + 1, x2, y + 1);
}

/* Draws the classic Westwood brushed metal button plate with 3D bevels */
static inline void MobileArt_DrawButtonPlate(SDL_Renderer *renderer, SDL_Rect rect, int pressed, int active, int scale)
{
	int bevel = (scale >= 3) ? 2 : 1;

	/* Outer dark border */
	MobileArt_SetColor(renderer, RA_STEEL_OUTLINE);
	SDL_RenderDrawRect(renderer, &rect);

	SDL_Rect body = { rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2 };

	if (pressed) {
		/* Sunken pressed state */
		MobileArt_SetColor(renderer, RA_STEEL_PRESSED_FACE);
		SDL_RenderFillRect(renderer, &body);

		/* Pressed inverted bevel: top and left are dark shadows */
		MobileArt_SetColor(renderer, RA_STEEL_SHADOW_OUTER);
		for (int b = 0; b < bevel; ++b) {
			SDL_RenderDrawLine(renderer, body.x + b, body.y + b, body.x + body.w - 1 - b, body.y + b);
			SDL_RenderDrawLine(renderer, body.x + b, body.y + b, body.x + b, body.y + body.h - 1 - b);
		}
		MobileArt_SetColor(renderer, RA_STEEL_SHADOW_INNER);
		if (bevel > 1) {
			SDL_RenderDrawLine(renderer, body.x + 1, body.y + 1, body.x + body.w - 2, body.y + 1);
			SDL_RenderDrawLine(renderer, body.x + 1, body.y + 1, body.x + 1, body.y + body.h - 2);
		}

		/* Bottom and right subtle highlight */
		MobileArt_SetColor(renderer, RA_STEEL_FACE_A);
		for (int b = 0; b < bevel; ++b) {
			SDL_RenderDrawLine(renderer, body.x + b, body.y + body.h - 1 - b, body.x + body.w - 1 - b, body.y + body.h - 1 - b);
			SDL_RenderDrawLine(renderer, body.x + body.w - 1 - b, body.y + b, body.x + body.w - 1 - b, body.y + body.h - 1 - b);
		}
	} else {
		/* Normal unpressed state: brushed metal horizontal grain */
		for (int y = body.y; y < body.y + body.h; ++y) {
			int grain = y % 3;
			if (grain == 0) {
				MobileArt_SetColor(renderer, RA_STEEL_FACE_A);
			} else if (grain == 1) {
				MobileArt_SetColor(renderer, RA_STEEL_FACE_B);
			} else {
				MobileArt_SetColor(renderer, RA_STEEL_FACE_C);
			}
			SDL_RenderDrawLine(renderer, body.x, y, body.x + body.w - 1, y);
		}

		/* Top and Left: bright 3D specular light bevel */
		MobileArt_SetColor(renderer, RA_STEEL_LIGHT_OUTER);
		SDL_RenderDrawLine(renderer, body.x, body.y, body.x + body.w - 1, body.y);
		SDL_RenderDrawLine(renderer, body.x, body.y, body.x, body.y + body.h - 1);
		if (bevel > 1) {
			MobileArt_SetColor(renderer, RA_STEEL_LIGHT_INNER);
			SDL_RenderDrawLine(renderer, body.x + 1, body.y + 1, body.x + body.w - 2, body.y + 1);
			SDL_RenderDrawLine(renderer, body.x + 1, body.y + 1, body.x + 1, body.y + body.h - 2);
		}

		/* Bottom and Right: deep 3D shadow bevel */
		MobileArt_SetColor(renderer, RA_STEEL_SHADOW_OUTER);
		SDL_RenderDrawLine(renderer, body.x, body.y + body.h - 1, body.x + body.w - 1, body.y + body.h - 1);
		SDL_RenderDrawLine(renderer, body.x + body.w - 1, body.y, body.x + body.w - 1, body.y + body.h - 1);
		if (bevel > 1) {
			MobileArt_SetColor(renderer, RA_STEEL_SHADOW_INNER);
			SDL_RenderDrawLine(renderer, body.x + 1, body.y + body.h - 2, body.x + body.w - 2, body.y + body.h - 2);
			SDL_RenderDrawLine(renderer, body.x + body.w - 2, body.y + 1, body.x + body.w - 2, body.y + body.h - 2);
		}
	}

	/* Active / armed state: tactical amber border outline */
	if (active) {
		MobileArt_SetColor(renderer, RA_TACTICAL_AMBER);
		SDL_Rect active_rect = { body.x + bevel, body.y + bevel, body.w - bevel * 2, body.h - bevel * 2 };
		SDL_RenderDrawRect(renderer, &active_rect);
		if (scale >= 3) {
			SDL_Rect inner_glow = { active_rect.x + 1, active_rect.y + 1, active_rect.w - 2, active_rect.h - 2 };
			MobileArt_SetColor(renderer, RA_GOLD_SHEEN);
			SDL_RenderDrawRect(renderer, &inner_glow);
		}
	}
}

/*
 * Draws the authentic 3D bronze/gold Westwood chevron arrow (from STRIPUP / STRIPDN)
 * point_right: 0 = points left (collapse), 1 = points right (expand)
 */
static inline void MobileArt_DrawWestwoodArrow(SDL_Renderer *renderer, SDL_Rect rect, int point_right, int pressed, int scale)
{
	int cx = rect.x + rect.w / 2;
	int cy = rect.y + rect.h / 2;
	if (pressed) {
		cx += 1;
		cy += 1;
	}

	int aw = (rect.w * 9) / 20;
	int ah = (rect.h * 11) / 20;
	if (aw < 6) aw = 6;
	if (ah < 8) ah = 8;
	int half_w = aw / 2;
	int half_h = ah / 2;

	int line_thick = (scale >= 3) ? 2 : 1;

	if (point_right) {
		/* Points RIGHT (▶) to expand */
		int tip_x = cx + half_w;
		int base_x = cx - half_w;
		int notch_x = cx - half_w / 3;

		/* 1. Body Fill - Rich Westwood Gold */
		MobileArt_SetColor(renderer, RA_GOLD_BODY);
		for (int y = -half_h; y <= half_h; ++y) {
			int span = (int)(((long long)(half_h - (y < 0 ? -y : y)) * aw) / half_h);
			int cur_tip = base_x + span;
			int cur_back = base_x + (notch_x - base_x) * (half_h - (y < 0 ? -y : y)) / half_h;
			if (cur_tip >= cur_back) {
				SDL_RenderDrawLine(renderer, cur_back, cy + y, cur_tip, cy + y);
			}
		}

		/* 2. Upper Light Facet - Peak Sheen */
		MobileArt_SetColor(renderer, RA_GOLD_SHEEN);
		MobileArt_DrawThickLine(renderer, base_x, cy - half_h, tip_x, cy, line_thick);

		/* 3. Lower Shadow Facet - Bronze Shadow */
		MobileArt_SetColor(renderer, RA_GOLD_SHADOW);
		MobileArt_DrawThickLine(renderer, tip_x, cy, base_x, cy + half_h, line_thick);

		/* 4. Inner Notch Bevel */
		MobileArt_SetColor(renderer, RA_GOLD_HIGHLIGHT);
		MobileArt_DrawThickLine(renderer, base_x, cy - half_h, notch_x, cy, line_thick);
		MobileArt_SetColor(renderer, RA_GOLD_SHADOW);
		MobileArt_DrawThickLine(renderer, notch_x, cy, base_x, cy + half_h, line_thick);

		/* 5. Center Ridge Line */
		MobileArt_SetColor(renderer, RA_GOLD_SHEEN);
		SDL_RenderDrawLine(renderer, notch_x, cy, tip_x, cy);

		/* 6. Outer Contour */
		MobileArt_SetColor(renderer, RA_GOLD_OUTLINE);
		SDL_RenderDrawLine(renderer, base_x - 1, cy - half_h - 1, tip_x + 1, cy);
		SDL_RenderDrawLine(renderer, tip_x + 1, cy, base_x - 1, cy + half_h + 1);
		SDL_RenderDrawLine(renderer, base_x - 1, cy - half_h - 1, notch_x - 1, cy);
		SDL_RenderDrawLine(renderer, notch_x - 1, cy, base_x - 1, cy + half_h + 1);
	} else {
		/* Points LEFT (◀) to collapse */
		int tip_x = cx - half_w;
		int base_x = cx + half_w;
		int notch_x = cx + half_w / 3;

		/* 1. Body Fill - Rich Westwood Gold */
		MobileArt_SetColor(renderer, RA_GOLD_BODY);
		for (int y = -half_h; y <= half_h; ++y) {
			int span = (int)(((long long)(half_h - (y < 0 ? -y : y)) * aw) / half_h);
			int cur_tip = base_x - span;
			int cur_back = base_x - (base_x - notch_x) * (half_h - (y < 0 ? -y : y)) / half_h;
			if (cur_back >= cur_tip) {
				SDL_RenderDrawLine(renderer, cur_tip, cy + y, cur_back, cy + y);
			}
		}

		/* 2. Upper Light Facet - Peak Sheen */
		MobileArt_SetColor(renderer, RA_GOLD_SHEEN);
		MobileArt_DrawThickLine(renderer, tip_x, cy, base_x, cy - half_h, line_thick);

		/* 3. Lower Shadow Facet - Bronze Shadow */
		MobileArt_SetColor(renderer, RA_GOLD_SHADOW);
		MobileArt_DrawThickLine(renderer, tip_x, cy, base_x, cy + half_h, line_thick);

		/* 4. Inner Notch Bevel */
		MobileArt_SetColor(renderer, RA_GOLD_HIGHLIGHT);
		MobileArt_DrawThickLine(renderer, base_x, cy - half_h, notch_x, cy, line_thick);
		MobileArt_SetColor(renderer, RA_GOLD_SHADOW);
		MobileArt_DrawThickLine(renderer, notch_x, cy, base_x, cy + half_h, line_thick);

		/* 5. Center Ridge Line */
		MobileArt_SetColor(renderer, RA_GOLD_SHEEN);
		SDL_RenderDrawLine(renderer, tip_x, cy, notch_x, cy);

		/* 6. Outer Contour */
		MobileArt_SetColor(renderer, RA_GOLD_OUTLINE);
		SDL_RenderDrawLine(renderer, tip_x - 1, cy, base_x + 1, cy - half_h - 1);
		SDL_RenderDrawLine(renderer, tip_x - 1, cy, base_x + 1, cy + half_h + 1);
		SDL_RenderDrawLine(renderer, base_x + 1, cy - half_h - 1, notch_x + 1, cy);
		SDL_RenderDrawLine(renderer, notch_x + 1, cy, base_x + 1, cy + half_h + 1);
	}
}

/* Draws a retro 5x7 Westwood style pixel glyph with 3D drop-shadow relief */
static inline void MobileArt_DrawPixelGlyph(SDL_Renderer *renderer, int ox, int oy, const unsigned char matrix[7], RAColor face_color, int pixel_size)
{
	int shadow_offset = (pixel_size >= 2) ? 2 : 1;

	/* Pass 1: 3D Drop Shadow in dark charcoal */
	MobileArt_SetColor(renderer, RA_TACTICAL_SHADOW);
	for (int r = 0; r < 7; ++r) {
		unsigned char row = matrix[r];
		for (int c = 0; c < 5; ++c) {
			if (row & (1 << (4 - c))) {
				SDL_Rect sp = { ox + c * pixel_size + shadow_offset, oy + r * pixel_size + shadow_offset, pixel_size, pixel_size };
				SDL_RenderFillRect(renderer, &sp);
			}
		}
	}

	/* Pass 2: Embossed Face */
	MobileArt_SetColor(renderer, face_color);
	for (int r = 0; r < 7; ++r) {
		unsigned char row = matrix[r];
		for (int c = 0; c < 5; ++c) {
			if (row & (1 << (4 - c))) {
				SDL_Rect fp = { ox + c * pixel_size, oy + r * pixel_size, pixel_size, pixel_size };
				SDL_RenderFillRect(renderer, &fp);
			}
		}
	}
}

/*
 * Draws a Squad Digit (1, 2, 3, 4) with tactical status LED indicator
 */
static inline void MobileArt_DrawSquadDigit(SDL_Renderer *renderer, SDL_Rect rect, int digit, int assigned, int active, int pressed, int scale)
{
	static const unsigned char GLYPH_1[7] = { 0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E };
	static const unsigned char GLYPH_2[7] = { 0x0E, 0x11, 0x01, 0x06, 0x08, 0x10, 0x1F };
	static const unsigned char GLYPH_3[7] = { 0x1E, 0x01, 0x01, 0x06, 0x01, 0x01, 0x1E };
	static const unsigned char GLYPH_4[7] = { 0x11, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x01 };

	const unsigned char *matrix = GLYPH_1;
	if (digit == 2) matrix = GLYPH_2;
	else if (digit == 3) matrix = GLYPH_3;
	else if (digit == 4) matrix = GLYPH_4;

	int pixel_size = (scale >= 3) ? 3 : (scale == 2 ? 2 : 1);
	int gw = 5 * pixel_size;
	int gh = 7 * pixel_size;
	int ox = rect.x + (rect.w - gw) / 2;
	int oy = rect.y + (rect.h - gh) / 2;
	if (pressed) {
		ox += 1;
		oy += 1;
	}

	RAColor color = active ? RA_TACTICAL_AMBER : RA_TACTICAL_WHITE;
	MobileArt_DrawPixelGlyph(renderer, ox, oy, matrix, color, pixel_size);

	/* Status LED in top-right corner */
	int led_sz = (scale >= 3) ? 6 : 4;
	int led_x = rect.x + rect.w - led_sz - 4;
	int led_y = rect.y + 4;
	if (pressed) {
		led_x += 1;
		led_y += 1;
	}

	/* LED socket */
	MobileArt_SetColor(renderer, RA_STEEL_OUTLINE);
	SDL_Rect led_socket = { led_x - 1, led_y - 1, led_sz + 2, led_sz + 2 };
	SDL_RenderDrawRect(renderer, &led_socket);

	if (assigned) {
		/* Bright Green LED on */
		MobileArt_SetColor(renderer, RA_LED_GREEN_ON);
		SDL_Rect led_core = { led_x, led_y, led_sz, led_sz };
		SDL_RenderFillRect(renderer, &led_core);

		/* Specular hot-spot */
		MobileArt_SetColor(renderer, RA_LED_GREEN_CORE);
		SDL_Rect led_pip = { led_x + 1, led_y + 1, led_sz / 2, led_sz / 2 };
		SDL_RenderFillRect(renderer, &led_pip);
	} else {
		/* Inactive dark LED */
		MobileArt_SetColor(renderer, RA_LED_GREEN_OFF);
		SDL_Rect led_dark = { led_x, led_y, led_sz, led_sz };
		SDL_RenderFillRect(renderer, &led_dark);
	}
}

/*
 * Draws the Force Attack target reticle (CTRL)
 */
static inline void MobileArt_DrawForceAttackReticle(SDL_Renderer *renderer, SDL_Rect rect, int active, int pressed, int scale)
{
	int cx = rect.x + rect.w / 2;
	int cy = rect.y + rect.h / 2;
	if (pressed) {
		cx += 1;
		cy += 1;
	}

	int r = (rect.h * 7) / 24;
	if (r < 5) r = 5;
	int line_thick = (scale >= 3) ? 2 : 1;

	RAColor ring_color = active ? RA_ALERT_RED_GLOW : RA_STEEL_LIGHT_INNER;
	RAColor cross_color = active ? RA_ALERT_RED : RA_STEEL_FACE_A;
	RAColor core_color = active ? RA_ALERT_RED_PEAK : RA_ALERT_RED;

	/* Outer reticle ring */
	MobileArt_SetColor(renderer, ring_color);
	MobileArt_DrawThickLine(renderer, cx - r, cy - r / 2, cx - r / 2, cy - r, line_thick);
	MobileArt_DrawThickLine(renderer, cx + r / 2, cy - r, cx + r, cy - r / 2, line_thick);
	MobileArt_DrawThickLine(renderer, cx + r, cy + r / 2, cx + r / 2, cy + r, line_thick);
	MobileArt_DrawThickLine(renderer, cx - r / 2, cy + r, cx - r, cy + r / 2, line_thick);

	/* Crosshair ticks */
	MobileArt_SetColor(renderer, cross_color);
	int tick_len = r / 2;
	if (tick_len < 2) tick_len = 2;
	MobileArt_DrawThickLine(renderer, cx, cy - r - tick_len, cx, cy - r + 1, line_thick);
	MobileArt_DrawThickLine(renderer, cx, cy + r - 1, cx, cy + r + tick_len, line_thick);
	MobileArt_DrawThickLine(renderer, cx - r - tick_len, cy, cx - r + 1, cy, line_thick);
	MobileArt_DrawThickLine(renderer, cx + r - 1, cy, cx + r + tick_len, cy, line_thick);

	/* Center target dot */
	MobileArt_SetColor(renderer, core_color);
	int dot_sz = (scale >= 3) ? 3 : 2;
	SDL_Rect dot = { cx - dot_sz / 2, cy - dot_sz / 2, dot_sz, dot_sz };
	SDL_RenderFillRect(renderer, &dot);
}

/*
 * Draws Tactical Action Letters ('S' Stop, 'X' Scatter)
 */
static inline void MobileArt_DrawTacticalLetter(SDL_Renderer *renderer, SDL_Rect rect, char ch, int active, int pressed, int scale)
{
	static const unsigned char GLYPH_S[7] = { 0x0F, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x1E };
	static const unsigned char GLYPH_X[7] = { 0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11 };

	const unsigned char *matrix = (ch == 'S' || ch == 's') ? GLYPH_S : GLYPH_X;

	int pixel_size = (scale >= 3) ? 3 : (scale == 2 ? 2 : 1);
	int gw = 5 * pixel_size;
	int gh = 7 * pixel_size;
	int ox = rect.x + (rect.w - gw) / 2;
	int oy = rect.y + (rect.h - gh) / 2;
	if (pressed) {
		ox += 1;
		oy += 1;
	}

	RAColor color;
	if (ch == 'S' || ch == 's') {
		color = active ? RA_TACTICAL_AMBER : RA_TACTICAL_AMBER;
	} else {
		color = active ? RA_TACTICAL_CYAN : RA_TACTICAL_CYAN;
	}

	MobileArt_DrawPixelGlyph(renderer, ox, oy, matrix, color, pixel_size);
}

#ifdef __cplusplus
}
#endif

#endif /* MOBILE_TOUCH_ART_H */
