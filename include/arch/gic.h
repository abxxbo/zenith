#pragma once

#include <stddef.h>
#include <stdint.h>


#define GIC_BASE 0x08000000
#define GIC_CTLR GIC_BASE
#define GIC_ISEN (GIC_BASE + 0x0100) // is enabler
#define GIC_PEND (GIC_BASE + 0x0280)
#define GIC_TARG (GIC_BASE + 0x0800)
#define GIC_PRIO (GIC_BASE + 0x0400)
#define GIC_ICFG (GIC_BASE + 0x0c00)

#define GIC_CLTR_ENABLE 1
#define GIC_ISEN_SIZE   32
#define GIC_PEND_SIZE   32
#define GIC_TARG_SIZE   4
#define GIC_TARG_BITS   8 // bits/int

#define GIC_PRIO_SIZE   4
#define GIC_PRIO_BITS   8
#define GIC_ICFG_SIZE  16
#define GIC_ICFG_BITS   2

// CPU
#define GICC_BASE      0x08010000
#define GICC_CTLR			 GICC_BASE
#define GICC_PWR			 (GICC_BASE + 0x0004)
#define GICC_BPR 			 (GICC_BASE + 0x0008)

#define GICC_CTLR_ENABLE   1
#define GICC_PMR_PRIO_LOW  0xFF
#define GICC_BPR_NO_GRUOUP 0x00
#define ICFGR_EDGE				 2


void init_gic(void);
void enable_gic(uint32_t interrupt);
void clear_int(uint32_t interrupt);

void set_core(uint32_t interrupt, uint32_t core);
void set_prio(uint32_t interrupt, uint32_t priority);
void set_config(uint32_t interrupt, uint32_t config);