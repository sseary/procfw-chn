#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspsysclib.h>
#include <string.h>
#include "printf_chs.h"
#include "font_chs.c"

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272
#define PSP_LINE_SIZE 512

static int X = 0, Y = 0;
static int MX=80, MY=22;
static u32 bg_col = 0, fg_col = 0xFFFFFFFF;
static void* g_vram_base = (u32 *) 0x04000000;
static int g_vram_offset = 0;
static int init = 0;

static void clear_screen(u32 color)
{
	int x;
	u32 *vram = g_vram_base;
	vram +=	(g_vram_offset>>2);

	for(x = 0; x < (PSP_LINE_SIZE * PSP_SCREEN_HEIGHT); x++)
	{
		*vram++ = color; 
	}
}

void Printf_CHS_ScreenInit(void)
{
	X = Y = 0;
	g_vram_base = (void*) (0x40000000 | (u32) 0x04000000);
	g_vram_offset = 0;
	sceDisplaySetMode(0, PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT);
	sceDisplaySetFrameBuf((void *) g_vram_base, PSP_LINE_SIZE, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
	clear_screen(bg_col);
	init = 1;
}

void Printf_CHS_ScreenSetXY(int x, int y)
{
	if( x<MX && x>=0 ) X=x;
	if( y<MY && y>=0 ) Y=y;
}

void Printf_CHS_ScreenSetTextColor(u32 colour)
{
	fg_col = colour;
}

void Printf_CHS_ScreenSetOffset(int offset)
{
	g_vram_offset = offset;
}

static void PutPixel(int x, int y, u32 color)
{
	u32 *vram_ptr;

	vram_ptr = g_vram_base;
	vram_ptr += (g_vram_offset >> 2) + x;
	vram_ptr += (y * PSP_LINE_SIZE);

	*vram_ptr = color;
}

void Printf_CHS_ScreenPutChar( int x, int y, u32 color, u8 ch1, u8 ch2)
{
	int i,j,font_offset;
	u8 *font;

	if(!init)
	{
		return;
	}

	if((int)ch1 < 128)
	{
		font = &msx[ (int)ch1 * 12 ];
		for (i=0; i < 12; i++, font++)
		{
			for (j=0; j < 6; j++)
			{
				if ((*font & (128 >> j)))
					PutPixel(x+j, y+i, color);
				else
					PutPixel(x+j, y+i, bg_col);
			}
		}
	}
	else
	{
		if( ((int)ch1 >= 0xA1) && ((int)ch1 <= 0xFE) && ((int)ch2 >= 0xA1) && ((int)ch2 <= 0xFE) )
			font_offset = 1536 + 24 + ((94*((int)ch1-0xA1)+((int)ch2-0xA1))*24);
		else
			font_offset = 1536;

		if(font_offset+24 > sizeof(msx))
			font_offset = 1536;

		font = &msx[ font_offset ];
		for (i=0; i < 12; i++, font+=2)
		{
			for (j=0; j < 12; j++)
			{
				if (j < 8)
				{
					if ((*font & (128 >> j)))
						PutPixel(x+j, y+i, color);
					else
						PutPixel(x+j, y+i, bg_col);
				}
				else
				{
					if ((*(font+1) & (128 >> (j-8))))
						PutPixel(x+j, y+i, color);
					else
						PutPixel(x+j, y+i, bg_col);
				}
			}
		}
	}
}

void  _Printf_CHS_ScreenClearLine( int Y)
{
	int i;

	for (i=0; i < MX; i++)
	{
		Printf_CHS_ScreenPutChar( i*6 , Y * 12, bg_col, ' ', 0);
	}
	return;
}

void Printf_CHS_ScreenClear(void)
{
	int y;

	if(!init)
	{
		return;
	}

	for(y=0;y<MY;y++)
	{
		_Printf_CHS_ScreenClearLine(y);
	}

	Printf_CHS_ScreenSetXY(0,0);
	clear_screen(bg_col);
}

int Printf_CHS_ScreenPrintData(const char *buff, int size)
{
	int i,j;
	unsigned char c[2];

	if(!init)
	{
		return 0;
	}

	i = 0;
	while (i < size)
	{
		c[0] = buff[i];
		if (c[0] < 128)
		{
			c[1] = 0;
			i++;

			switch (c[0])
			{
				case '\r':
					X = 0;
					break;
				case '\n':
					X = 0;
					Y ++;
					if (Y >= MY)
						Y = 0;
					_Printf_CHS_ScreenClearLine(Y);
					break;
				case '\t':
					for (j = 0; j < 5 && X < MX; j++)
					{
						Printf_CHS_ScreenPutChar( X*6 , Y * 12, fg_col, ' ', 0);
						X++;
					}
					break;
				default:
					if (X+1 > MX)
					{
						X = 0;
						Y++;
						if (Y >= MY)
							Y = 0;
						_Printf_CHS_ScreenClearLine(Y);
					}
					Printf_CHS_ScreenPutChar( X*6 , Y * 12, fg_col, c[0], c[1]);
					X++;
			}
		}
		else
		{
			c[1] = buff[i+1];
			i+=2;

			if (X+2 > MX)
			{
				X = 0;
				Y++;
				if (Y >= MY)
					Y = 0;
				_Printf_CHS_ScreenClearLine(Y);
			}
			Printf_CHS_ScreenPutChar( X*6 , Y * 12, fg_col, c[0], c[1]);
			X+=2;
		}
	}

	return i;
}

static int _itostr(char *buf, int in_data, int base, int upper, int sign)
{
	int res, len, i;
	unsigned int data;
	char *str;

	if(base==10 && sign && in_data<0){
		data = -in_data;
	}else{
		data = in_data;
	}

	str = buf;
	do{
		res = data%base;
		data = data/base;
		if(res<10){
			res += '0';
		}else{
			if(upper){
				res += 'A'-10;
			}else{
				res += 'a'-10;
			}
		}
		*str++ = res;
	}while(data);
	len = str-buf;

	/* reverse digital order */
	for(i=0; i<len/2; i++){
		res = buf[i];
		buf[i] = buf[len-1-i]; 
		buf[len-1-i] = res; 
	}

	return len;
}

#define _OUT_C(c) \
	if(str<end){ \
		*str++ = (c); \
	} else { \
		goto exit; \
	}

static char _digital_buf[32];
int _vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
	char ch, *s, *str, *end, *sstr;
	int zero_pad, left_adj, add_sign, field_width, sign;
	int i, base, upper, len;


	if(!buf || !fmt ||!size){
		return 0;
	}

	str = buf;
	end = buf+size;

	while(*fmt){
		if(*fmt!='%'){
			_OUT_C(*fmt++);
			continue;
		}

		/* skip '%' */
		sstr = (char *)fmt;
		fmt++;

		/* %% */
		if(*fmt=='%'){
			_OUT_C(*fmt++);
			continue;
		}

		/* get flag */
		zero_pad = ' ';
		left_adj = 0;
		add_sign = 0;
		while((ch=*fmt)){

			if(*fmt=='0'){
				zero_pad = '0';
			}else if(*fmt=='-'){
				left_adj = 1;
			}else if(*fmt=='#'){
			}else if(*fmt==' '){
				if(add_sign!='+')
					add_sign = ' ';
			}else if(*fmt=='+'){
				add_sign = '+';
			}else{
				break;
			}
			fmt++;
		}

		/* get field width: m.n */
		field_width = 0;
		/* get m */
		while(*fmt && *fmt>'0' && *fmt<='9'){
			field_width = field_width*10+(*fmt-'0');
			fmt++;
		}
		if(*fmt && *fmt=='.'){
			fmt++;
			/* skip n */
			while(*fmt && *fmt>'0' && *fmt<='9'){
				fmt++;
			}
		}

		/* get format char */
		upper = 0;
		base = 0;
		sign = 0;
		len = 0;
		s = _digital_buf;
		while((ch=*fmt)){
			fmt++;
			switch(ch){
			/* hexadecimal */
			case 'p':
			case 'X':
				upper = 1;
			case 'x':
				base = 16;
				break;

			/* decimal */
			case 'd':
			case 'i':
				sign = 1;
			case 'u':
				base = 10;
				break;

			/* octal */
			case 'o':
				base = 8;
				break;

			/* character */
			case 'c':
				_digital_buf[0] = (unsigned char) va_arg(args, int);
				len = 1;
				break;

			/* string */
			case 's':
				s = va_arg(args, char *);
				if(!s) s = "<NUL>";
				len = strlen(s);
				break;

			/* float format, skip it */
			case 'e': case 'E': case 'f': case 'F': case 'g': case 'G': case 'a': case 'A':
				va_arg(args, double);
				s = NULL;
				break;

			/* length modifier */
			case 'l': case 'L': case 'h': case 'j': case 'z': case 't':
				/* skip it */
				continue;

			/* bad format */
			default:
				s = sstr;
				len = fmt-sstr;
				break;
			}
			break;
		}

		if(base){
			i = va_arg(args, int);
			if(base==10 && sign){
				if(i<0){
					add_sign = '-';
				}
			}else{
				add_sign = 0;
			}

			len = _itostr(_digital_buf, i, base, upper, sign);
		}else{
			zero_pad = ' ';
			add_sign = 0;
		}

		if(s){
			if(len>=field_width){
				field_width = len;
				if(add_sign)
					field_width++;
			}
			for(i=0; i<field_width; i++){
				if(left_adj){
					if(i<len){
						_OUT_C(*s++);
					}else{
						_OUT_C(' ');
					}
				}else{
					if(add_sign && (zero_pad=='0' || i==(field_width-len-1))){
						_OUT_C(add_sign);
						add_sign = 0;
						continue;
					}
					if(i<(field_width-len)){
						_OUT_C(zero_pad);
					}else{
						_OUT_C(*s++);
					}
				}
			}
		}
	}

	_OUT_C(0);

exit:
	return str-buf;
}

void Printf_CHS_ScreenPrintf(const char *format, ...)
{
	va_list	opt;
	char buff[1760];
	int bufsz;

	va_start(opt, format);
	bufsz = _vsnprintf( buff, (size_t) sizeof(buff), format, opt) - 1;
	va_end(opt);
	(void) Printf_CHS_ScreenPrintData(buff, bufsz);
}

