#include "common.h"

#include <string.h>
#include <iostream>
#include <fstream>

#include <kos.h>
#include <oggvorbis/sndoggvorbis.h>

using namespace std;

int t;

char happy[5] = {
	0, 1, 2, 2, 3
};

char _new[3] = {
	4, 5, 6
};

char year[7] = {
	3, 5, 1, 7, 12
};

char decade[7] = {
	8, 5, 9, 1, 8, 5, 12
};

char twentytwentytwo[5] = {
	10, 11, 10, 10, 12
};

unsigned char vmuImage[192] = {
	0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111110,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b11100111, 0b11111111, 0b11111111, 0b11111111, 0b11101111, 0b11100111,
	0b11100111, 0b00000000, 0b00000000, 0b10000000, 0b00111000, 0b11100111,
	0b10011001, 0b01101101, 0b10011110, 0b00111100, 0b10000010, 0b10011001,
	0b10011001, 0b01101101, 0b10111111, 0b01111110, 0b11101110, 0b10011001,
	0b11100111, 0b00000000, 0b00110011, 0b01100110, 0b11111110, 0b11100111,
	0b11100111, 0b01101101, 0b10110011, 0b01100110, 0b11111110, 0b11100111,
	0b10011001, 0b01101101, 0b10110011, 0b01100110, 0b11111110, 0b10011001,
	0b10011001, 0b01101101, 0b10110011, 0b01100110, 0b11010110, 0b10011001,
	0b11100111, 0b01101101, 0b10111111, 0b01111110, 0b11000110, 0b11100111,
	0b11100111, 0b01101101, 0b10011110, 0b00111100, 0b11010110, 0b11100111,
	0b10011001, 0b01101101, 0b10000000, 0b10000000, 0b11010110, 0b10011001,
	0b10011001, 0b01101101, 0b10111111, 0b11111110, 0b11010110, 0b10011001,
	0b11100111, 0b00000000, 0b00100110, 0b01100110, 0b00010000, 0b11100111,
	0b11100111, 0b11111111, 0b11100110, 0b01100111, 0b11111111, 0b11100111,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10011001,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b11100110, 0b01100110, 0b01100110, 0b01100110, 0b01100110, 0b01100111,
	0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111110
};

pvr_ptr_t backgroundTex;
pvr_ptr_t letterTex;

/* romdisk */
extern uint8 romdisk_boot[];
KOS_INIT_ROMDISK(romdisk_boot);

void drawBackground(){
	pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&cxt, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565, 512, 512, backgroundTex, PVR_FILTER_BILINEAR);
    pvr_poly_compile(&hdr, &cxt);
    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;
    vert.flags = PVR_CMD_VERTEX;

    vert.x = 0;
    vert.y = 0;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 0;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 0.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 0;
    vert.y = 480;
    vert.z = 1;
    vert.u = 0.0;
    vert.v = 1.0;
    pvr_prim(&vert, sizeof(vert));

    vert.x = 640;
    vert.y = 480;
    vert.z = 1;
    vert.u = 1.0;
    vert.v = 1.0;
    vert.flags = PVR_CMD_VERTEX_EOL;
    pvr_prim(&vert, sizeof(vert));
}

void drawLetter(int xPos, int yPos, int index, int size){
	pvr_poly_cxt_t cxt;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

	float u, v, u2, v2;
    int x, y, x2, y2;

	pvr_poly_cxt_txr(&cxt, PVR_LIST_TR_POLY, PVR_TXRFMT_ARGB4444, 64, 64, letterTex, PVR_FILTER_NEAREST);
	pvr_poly_compile(&hdr, &cxt);
	pvr_prim(&hdr, sizeof(hdr));

	vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vert.oargb = 0;
	vert.flags = PVR_CMD_VERTEX;

	u = (float)((index % 4) * 16) / 64;
	v = (float)((index / 4) * 16) / 64;
	u2 = (float)(((index % 4) * 16) + 16) / 64;
	v2 = (float)(((index / 4) * 16) + 16) / 64;

	x = xPos;
	y = yPos;
	x2 = xPos + size;
	y2 = yPos + size;

	vert.x = x;
	vert.y = y;
	vert.z = 6;
	vert.u = (float)u;
	vert.v = (float)v;
	pvr_prim(&vert, sizeof(vert));

	vert.x = x2;
	vert.y = y;
	vert.z = 6;
	vert.u = u2;
	vert.v = v;
	pvr_prim(&vert, sizeof(vert));

	vert.x = x;
	vert.y = y2;
	vert.z = 6;
	vert.u = u;
	vert.v = v2;
	pvr_prim(&vert, sizeof(vert));

	vert.x = x2;
	vert.y = y2;
	vert.z = 6;
	vert.u = u2;
	vert.v = v2;
	vert.flags = PVR_CMD_VERTEX_EOL;
	pvr_prim(&vert, sizeof(vert));
}

/* draw one frame */
void drawFrame() {
    pvr_wait_ready();
    pvr_scene_begin();

    pvr_list_begin(PVR_LIST_OP_POLY);
    drawBackground();
    pvr_list_finish();

    pvr_list_begin(PVR_LIST_TR_POLY);

	//HAPPY NEW YEAR!
	for(int i = 0; i < 5; i++){
		drawLetter(25 + (i * 35) + (5 * sin((i * 5) + t * 0.1f)), 132 + (5 * cos((i * 5) + t * 0.1f)), happy[i], 32);
	}
	for(int i = 0; i < 3; i++){
		drawLetter((25 + (5 * 32) + 75) + (i * 35) + (5 * sin((i * 5) + t * 0.1f)), 132 + (5 * cos((i * 5) + t * 0.1f)), _new[i], 32);
	}
	for(int i = 0; i < 5; i++){
		drawLetter(((25 + (5 * 32) + 75) + (3 * 32) + 75) + (i * 35) + (5 * sin((i * 5) + t * 0.1f)), 132 + (5 * cos((i * 5) + t * 0.1f)), year[i], 32);
	}

	//2021!
	for(int i = 0; i < 5; i++){
		drawLetter(150 + (i * 67) + (5 * sin((i * 5) + t * 0.1f)), 300 + (5 * cos((i * 5) + t * 0.1f)), twentytwentytwo[i], 64);
	}

    pvr_list_finish();

    pvr_scene_finish();
}

int main(void) {
    snd_stream_init();
    sndoggvorbis_init();
    sndoggvorbis_start("/rd/bgm/bgm.ogg", 1);

    /* init kos  */
    pvr_init_defaults();

	backgroundTex = pvr_mem_malloc(512 * 512 * 2);
    png_to_texture("/rd/imgs/background.png", backgroundTex, PNG_NO_ALPHA);

	letterTex = pvr_mem_malloc(16 * 16 * 2);
    png_to_texture("/rd/imgs/letters.png", letterTex, PNG_FULL_ALPHA);

	maple_device_t* vmuLCD;
	vmuLCD = maple_enum_type(0, MAPLE_FUNC_LCD);
	vmu_draw_lcd(vmuLCD, vmuImage);

    while(1) {
        drawFrame();

		t++;
    }

    return 0;
}
