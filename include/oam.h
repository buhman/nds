#include <stdint.h>
#include <stddef.h>

#define static_assert _Static_assert

struct oam_obj {
  volatile uint16_t attr[3];
  volatile uint16_t _0;
};
static_assert((sizeof (struct oam_obj)) == 8);

struct oam_param {
  volatile uint16_t _0[3];
  volatile uint16_t pa;
  volatile uint16_t _1[3];
  volatile uint16_t pb;
  volatile uint16_t _2[3];
  volatile uint16_t pc;
  volatile uint16_t _3[3];
  volatile uint16_t pd;
};
static_assert((sizeof (struct oam_param)) == 32);

union oam {
  struct oam_obj obj[128];
  struct oam_param param[32];
};
static_assert((sizeof (union oam)) == 0x400);

struct oam_a_b {
  union oam a;
  union oam b;
};
static_assert((offsetof (struct oam_a_b, a)) == 0x000);
static_assert((offsetof (struct oam_a_b, b)) == 0x400);

extern struct oam_a_b oam __asm("oam");
