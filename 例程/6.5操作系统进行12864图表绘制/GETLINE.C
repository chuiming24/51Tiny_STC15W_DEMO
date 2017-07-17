/******************************************************************************/
/*                                                                            */
/*      GETLINE.C:  Line Edited Character Input                               */
/*                                                                            */
/******************************************************************************/

#include <usar.h>
#define CNTLQ      0x11
#define CNTLS      0x13
#define DEL        0x7F
#define BACKSPACE  0x08
#define CR         0x0D
#define LF         0x0A

/***************/
/* Line Editor */
/***************/
void getline (char idata *line, unsigned char n)  {
  unsigned char cnt = 0;
  char c;

  do  {
    if ((c = getkey ()) == CR)  c = LF;    /* read character                 */
    if (c == BACKSPACE  ||  c == DEL)  {    /* process backspace              */
      if (cnt != 0)  {            
        cnt--;                              /* decrement count                */
        line--;                             /* and line pointer               */
        SendData (0x08);                     /* echo backspace                 */
        SendData (' ');
        SendData (0x08);
      }
    }
    else if (c != CNTLQ && c != CNTLS && c != LF)  {   /* ignore Control S/Q             */
      SendData (*line = c);                  /* echo and store character       */
      line++;                               /* increment line pointer         */
      cnt++;                                /* and count                      */
    }
  }  while (cnt < n - 1  &&  c != LF);      /* check limit and line feed      */
  *line = 0;                                /* mark end of string             */
}
