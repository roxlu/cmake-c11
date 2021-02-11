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

struct rxlog;

/* ------------------------------------------------------- */

int rx_log_create(struct rxlog** log);
int rx_log_destroy(struct rxlog* log);
int rx_log_init(struct rxlog* log);
int rx_log_shutdown(struct rxlog* log);
int rx_log_add(struct rxlog* log, const char* message);

/* ------------------------------------------------------- */

#endif
