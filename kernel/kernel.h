#ifndef __KERNEL_H
#define __KERNEL_H

#include <stddef.h>
#include <stdint.h>

#include   "GIC.h"
#include "PL011.h"
#include "SP804.h"

#include "interrupt.h"

#include <string.h>

#include "structures/queues.h"
#include "structures/lifo.h"
#include "structures/fifo.h"

#include "constants.h"
#include "core.h"
#include "ipc.h"
#include "disk.h"
#include "system.h"

// Include definitions relating to the 2 user programs.

#include "P0.h"
#include "P1.h"
#include "P2.h"
#include "PDef.h"
#include "libc.h"
/* The kernel source code is made simpler by three type definitions:
 *
 * - a type that captures each component of an execution context (i.e.,
 *   processor state) in a compatible order wrt. the low-level handler
     preservation and restoration prologue and epilogue,
 * - a type that captures a process identifier, which is basically an
 *   integer, and
 * - a type that captures a process PCB.
 */


#endif
