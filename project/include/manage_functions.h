#ifndef PROJECT_INCLUDE_MANAGE_FUNCTIONS_H_
#define PROJECT_INCLUDE_MANAGE_FUNCTIONS_H_

#include <stdio.h>

#include "structs.h"

int write_client_data(FILE *input_stream, FILE *output_stream);
int commit_transaction(FILE *input_stream, FILE *output_stream);
int update_credit_limit(FILE *client_stream, FILE *transaction_stream, FILE *upd_client_stream);

#endif  // PROJECT_INCLUDE_MANAGE_FUNCTIONS_H_
