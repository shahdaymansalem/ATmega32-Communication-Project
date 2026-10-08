#ifndef LIBRARY_BIT_MATH_H_
#define LIBRARY_BIT_MATH_H_

#define SET(reg,bit)         (reg |= (1<<bit))
#define CLEAR(reg,bit)       (reg &= ~(1<<bit))
#define TOGGLE(reg,bit)      (reg ^= (1<<bit))
#define GET(REG,BIT)         (REG & (1<<BIT))

#endif