#ifndef RX_LOG_H
#define RX_LOG_H

#include <stdlib.h>
#include <stdint.h>
#include <threads.h>

/* ------------------------------------------------------- */

struct rxlog_item {
  char* message;
  uint32_t nbytes;
};

/* ------------------------------------------------------- */

struct rxlog {
  struct rxlog_item* items;
  uint32_t num_items;
  uint32_t write_dx;
  uint32_t read_dx;
  struct mtx_t mut;
  struct thrd_t thr;
};

/* ------------------------------------------------------- */

int rx_log_create(struct rxlog** log);
int rx_log_destroy(struct rxlog* log);
int rx_log_init(struct rxlog* log);
int rx_log_shutdown(struct rxlog* log);
int rx_log_add(struct rxlog* log, const char* message);

/* ------------------------------------------------------- */

#endif
