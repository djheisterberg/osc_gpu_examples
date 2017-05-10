/*
 * Random64.h
 * Based on code written in 2014 by Sebastiano Vigna (vigna@acm.org)
 */
#ifndef RANDOM64_H
#define RANDOM64_H

#include <stdint.h>

class Random64 {

private:
   uint64_t s[16];
   int p;

public:
   Random64(uint64_t seed);

   uint64_t next();
   double nextDouble();

   void jump();
};

#endif /* RANDOM64_H */
