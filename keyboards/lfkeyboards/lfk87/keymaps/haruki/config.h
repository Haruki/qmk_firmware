#ifndef CONFIG_USER_H
#define CONFIG_USER_H
#define PERMISSIVE_HOLD

#include "../../config.h"

// place overrides here
#define LSPO_KEY KC_8
#define RSPC_KEY KC_9
#define DISABLE_SPACE_CADET_ROLLOVER

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(IMPERIAL_MARCH)
#endif

#endif
