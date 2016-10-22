/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BIT_H
#define __BIT_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define    ZERO    0x0000

#ifdef __BIT_IMPLICIT
  #define  BIT0    0x0001
  #define  BIT1    0x0002
  #define  BIT2    0x0004
  #define  BIT3    0x0008
  #define  BIT4    0x0010
  #define  BIT5    0x0020
  #define  BIT6    0x0040
  #define  BIT7    0x0080
  #define  BIT8    0x0100
  #define  BIT9    0x0200
  #define  BIT10   0x0400
  #define  BIT11   0x0800
  #define  BIT12   0x1000
  #define  BIT13   0x2000
  #define  BIT14   0x4000
  #define  BIT15   0x8000
#else
  #define  BIT0    (1 << 0)
  #define  BIT1    (1 << 1)
  #define  BIT2    (1 << 2)
  #define  BIT3    (1 << 3)
  #define  BIT4    (1 << 4)
  #define  BIT5    (1 << 5)
  #define  BIT6    (1 << 6)
  #define  BIT7    (1 << 7)
  #define  BIT8    (1 << 8)
  #define  BIT9    (1 << 9)
  #define  BIT10   (1 << 10)
  #define  BIT11   (1 << 11)
  #define  BIT12   (1 << 12)
  #define  BIT13   (1 << 13)
  #define  BIT14   (1 << 14)
  #define  BIT15   (1 << 15)
#endif

/* Exported functions ------------------------------------------------------- */


#endif /* __BIT_H */
