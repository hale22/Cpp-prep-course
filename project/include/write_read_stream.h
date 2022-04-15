#ifndef PROJECT_INCLUDE_WRITE_READ_STREAM_H_
#define PROJECT_INCLUDE_WRITE_READ_STREAM_H_

#include <stdio.h>

#include "structs.h"

int read_stream(FILE *stream, accounting_data_t *accounting_data, int mode);
int write_stream(FILE *stream, accounting_data_t accounting_data, int mode);

#endif  // PROJECT_INCLUDE_WRITE_READ_STREAM_H_
