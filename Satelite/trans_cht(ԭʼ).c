#include "common.h"

const char *g_messages_cht[] = {
	"默認",
	"禁用",
	"啟用",
	"標準",
	"M33 driver",
	"Sony NP9660",
	"Inferno",
	"CPU 頻率(XMB) ",
	"CPU 頻率(GAME)",
	"USB 設備      ",
	"UMD ISO 模式  ",
	"掛載ISO VIDEO ",
	"恢復菜單  ->",
	"關閉設備",
	"掛起設備",
	"重啟設備",
	"重啟VSH ",
	"退出",
	"PRO VSH菜單",
	"Flash",
	"UMD Disc",
	"Memory Stick",
	"無",
};

u8 message_test_cht[NELEMS(g_messages_cht) == MSG_END ? 0 : -1];
