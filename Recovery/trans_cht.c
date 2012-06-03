#include "systemctrl.h"
#include "systemctrl_se.h"
#include "utils.h"
#include "main.h"

const char * g_messages_cht[] = {
	"PRO \241\241\241\316\241\331\241\315",
	"\241\116\241\331\241\315",
	"\241\332\241\100\241\104",
	"\241\264\241\121\241\104",
	"\241\171\241\135",
	"\241\371\241\353",
	"\241\301\241\126",
	"\241\337\241\126",
	"\241\110\241\320USB",
	"\241\301\241\126USB",
	"\241\337\241\126USB",
	"\241\274\241\124\241\310\241\340",
	"\241\271\241\273\241\322\242\105",
	"\241\241\241\316\241\331\241\315\241\140\242\107",
	"ISO \241\357\241\143",
	"\241\356\241\336",
	"M33 driver",
	"Sony NP9660",
	"Inferno",
	"USB \241\310\241\314",
	"Flash 0",
	"Flash 1",
	"Flash 2",
	"Flash 3",
	"UMD Disc",
	"\241\311\241\277 USB\241\256\241\330\241\350\241\144\241\117\241\350 (PSP-1000\241\325\241\255)",
	"\241\160\241\126Slim\242\101\241\146 (PSP-1000\241\275\241\126)",
	"\241\160\241\126htmlviewer\241\145\241\164\241\341\241\174\241\141\241\151\241\340",
	"\241\374\242\100 MAC\241\136\241\154",
	"\241\301\241\270\241\256\241\345\241\347Sony Logo",
	"\241\345\241\347\241\324\241\372\241\301\241\270\241\326\241\251",
	"\241\324\241\372\241\132\241\170\241\104\241\374\242\100PIC0.PNG\241\162PIC1.PNG",
	"\241\174\242\106 USB\241\310\241\314\241\142\241\342Flash",
	"\241\160\241\126/seplugins/version.txt",
	"\241\160\241\126/seplugins/usbversion.txt",
	"\241\160\241\126\241\145\241\164\241\341\241\156\241\335\241\165\241\267\241\365",
	"\241\172\241\115\241\153\241\265\241\130\241\257\241\113\241\131 (PSP-Go\241\275\241\126)",
	"\241\266\241\261\241\310\241\340",
	"\241\317\241\131(XMB)",
	"\241\317\241\131(Game)",
	"\241\317\241\131(Pops)",
	"NoDRM \241\111\241\373",
	"\241\324\241\372\241\256\241\374\242\100 CFW\241\113\241\131",
	"\241\324\241\372\241\256\241\337\241\126\241\334\241\302",
	"\241\376\241\317\241\131\241\112\241\243(PSP-Go\241\275\241\126)",
	"Inferno & NP9660 \241\160\241\126ISO\241\266\241\312\241\362\241\141",
	"Inferno & NP9660 \241\362\241\141\241\101\241\102(MB)",
	"Inferno & NP9660 \241\362\241\141\241\355",
	"Inferno & NP9660 \241\362\241\141\241\327\241\305",
	"\241\105\241\307\241\173latin1\241\167ISO\241\113\241\131\241\133",
	"Memory Stick\241\122\241\312",
	"\241\325",
	"Pop",
	"Game",
	"Vsh",
	"Pop & Game",
	"Game & Vsh",
	"Vsh & Pop",
	"\241\163\241\306",
	"CPU \241\370\241\303",
	"CPU/BUS(XMB) ",
	"CPU/BUS(Game)",
	"\241\317\241\131\241\351\241\304",
	"System Storage",
	"Memory Stick",
	"\241\317\241\131\241\137System Storage",
	"\241\317\241\131\241\137Memory Stick",
	"\241\166\241\120\241\170\241\260\241\343",
	"WMA \241\367\241\245",
	"Flash \241\367\241\245",
	"\241\242\241\333\241\127\241\320",
	"\241\361\241\353\241\242\241\333: X",
	"\241\361\241\353\241\242\241\333: O",
	"\241\367\241\245 WMA",
	"\241\367\241\245 Flash",
	"\241\127\241\320 O/X\241\242\241\333",
	"\241\127\241\320 O/X\241\242\241\333 (\241\354\241\250\241\301 VSH\241\134\241\103\241\262\241\125\241\255)",
	"\241\153\241\265\241\130\241\257\241\113\241\131 (PSP-Go\241\275\241\126)",
	"\241\130\241\257\241\113\241\131\241\153\241\265",
	"\241\346\241\147/PSP/GAME/RECOVERY/EBOOT.PBP",
	"\242\103\241\313\241\310\241\314",
	"\241\300\241\263\241\310\241\314",
	"\241\250\241\301\241\310\241\314",
	"\241\250\241\301VSH",
	"\241\107\241\252",
	"\241\114\241\124",
	"\241\246\241\272",
	"\241\360\241\244",
	"\241\375\241\272",
	"\241\247\241\272",
	"\241\364\241\150\241\254",
	"\241\366\241\101\241\152\241\157",
	"\241\253\241\323",
	"\241\352\242\110",
	"\241\175\242\102\241\321",
	"\241\104\241\272",
	"\241\363\241\344\242\104\241\176I",
	"\241\363\241\344\242\104\241\176II",
	"\241\276\241\161\241\266\241\106\241\141\241\123\241\155",
};

u8 message_test_cht[NELEMS(g_messages_cht) == MSG_END ? 0 : -1];
