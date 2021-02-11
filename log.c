#include <threads.h>
#include <stdio.h>
#include "log.h"

/* ------------------------------------------------------- */

static void* thread_func(void* log); 

/* ------------------------------------------------------- */

int rx_log_create(struct rxlog** log) {

  struct rxlog* new_log = NULL;
  if (NULL == log) {
    return -1;
  }

  if (NULL != *log) {
    return -2;
  }

  new_log = malloc(sizeof(*new_log));
  if (NULL == new_log) {
    return -3;
  }

  if (0 != rx_log_init(new_log)) {
    free(new_log);
    new_log = NULL;
    return -4;
  }

  *log = new_log;
  
  return 0;
}

int rx_log_destroy(struct rxlog* log) {

  if (0 != rx_log_shutdown(log)) {
    return -1;
  }

  free(log);
  
  return 0;
}

int rx_log_init(struct rxlog* log) {

  if (NULL == log) {
    printf("Given `log` context is NULL.\n");
    return -1;
  }

  log->num_items = 100;
  log->items = malloc(sizeof(struct rxlog_item) * log->num_items);
  log->read_dx = 0;
  log->write_dx = 0;
  
  if (NULL == log->items) {
    printf("Failed to allocate the items buffer.\n");
    return -2;
  }

  /* Initialize the log items. */
  for (uint32_t i = 0; i < log->num_items; ++i) {
    struct rxlog_item* item = log->items + i;
    item->nbytes = 1024;
    item->message = malloc(item->nbytes);
    if (NULL == item->message) {
      printf("Failed to allocate a message buffer for an item.\n");
      return -3;
    }
  }

  /* Initialize threading. */
#if 1  
  if (thrd_success != mtx_init(&log->mut, mtx_plain)) {
    printf("Failed to initialize the mutex.\n");
    return -4;
  }

  if (0 != thrd_create(&log->thr, thread_func, log)) {
    printf("Failed to create the log worker thread.\n");
    return -5;
  }
#endif
  
  return 0;
}

int rx_log_shutdown(struct rxlog* log) {

  if (NULL == log) {
    return -1;
  }

  for (uint32_t i = 0; i < log->num_items; ++i) {

    if (NULL == log->items[i].message) {
      continue;
    }
    
    free(log->items[i].message);
    
    log->items[i].nbytes = 0;
    log->items[i].message = NULL;
  }

  free(log->items);
  log->items = NULL;
  log->num_items = 0;

  /* Cleanup the mutex. */
  //mtx_destroy(&log->mut);
  
  return 0;
}

/* ------------------------------------------------------- */

int rx_log_add(struct rxlog* log, const char* message) {

  if (NULL == log) {
    return -1;
  }

  if (NULL == message) {
    return -2;
  }

  //  mtx_lock(&log->mut);
  struct rxlog_item* item = log->items + log->write_dx;
  strcpy(item->message, message);
  log->write_dx++;
  if (log->write_dx >= log->num_items) {
    log->write_dx = 0;
  }
  //mtx_unlock(&log->mut);
    
  //log->items[log->write_dx]
  
}

/* ------------------------------------------------------- */

static void* thread_func(void* log) {

  printf("nice!\n");
  return NULL;
}

/* ------------------------------------------------------- */
