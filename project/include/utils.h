#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

#include "structs.h"

void write_client_data(FILE *client_stream, accounting_data_t client_data);
void commit_transaction(FILE *transaction_stream, transaction_data_t transfer_data);
void update_credit_limit(FILE *client_stream, FILE *transaction_stream, FILE *upd_client_stream,
    accounting_data_t client_data, transaction_data_t transfer_data);
void print_welcome_mes(int mode);

#endif  // PROJECT_INCLUDE_UTILS_H_
