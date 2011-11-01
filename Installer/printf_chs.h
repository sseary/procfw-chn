#ifndef _PRINTF_CHS_H_
#define _PRINTF_CHS_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Debug Debug Utility Library */

/** @addtogroup Debug */
/*@{*/

/** 
  * Initialise the debug screen
  */
void Printf_CHS_ScreenInit(void);

/**
  * Do a printf to the debug screen.
  *
  * @param fmt - Format string to print
  * @param ... - Arguments
  */
void Printf_CHS_ScreenPrintf(const char *fmt, ...) __attribute__((format(printf,1,2)));

/**
  * Set the text color 
  *
  * @param color - A 32 bit RGB color
  */
void Printf_CHS_ScreenSetTextColor(u32 color);

/**
  * Set the current X and Y co-ordinate for the screen (in character units)
  */
void Printf_CHS_ScreenSetXY(int x, int y);

/**
  * Set the video ram offset used for the screen
  *
  * @param offset - Offset in bytes
  */
void Printf_CHS_ScreenSetOffset(int offset);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
