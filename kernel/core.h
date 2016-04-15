#ifndef __CORE_H
#define __CORE_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "constants.h"

void core_fork();
void core_exit();
void core_init();

#endif
