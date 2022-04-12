#include <mc9s12dp256.h>        /* derivative information */


//The following defines half of the period required for the notes
//#defines assume that there will be prescaler = 8

#define rest 20
#define Eb3 9641
#define E3  9100
#define F3  8589
#define Gb3 8107
#define G3  7652
#define Ab3 7223
#define A3  6817
#define Bb3 6434
#define B3  6073
#define C4  5733
#define Db4 5411
#define D4  5107
#define Eb4 4820
#define E4  4550
#define F4  4294
#define Gb4 4053
#define G4  3826
#define Ab4 3611
#define A4  3408
#define Bb4 3611
#define B4  3036
#define C5  2866
#define Db5 2705
#define D5  2553
#define Eb5 2410
#define E5  2275
#define F5  2147
#define Gb5 2026
#define G5  1913
#define Ab5 1805
#define A5  1704


unsigned int note{
    rest,
    Eb3,
    E3,
    F3,
    Gb3,
    G3,
    Ab3,
    A3,
    Bb3,
    B3,
    C4,
    Db4,
    D4,
    Eb4,
    E4,
    F4,
    Gb4,
    G4,
    Ab4,
    A4,
    Bb4,
    B4,
    C5,
    Db5,
    D5,
    Eb5,
    E5,
    F5,
    Gb5,
    G5,
    Ab5,
    };

unsigned int duration
{
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
}