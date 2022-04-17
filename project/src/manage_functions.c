#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "manage_functions.h"
#include "structs.h"
#include "welcome_mes_func.h"
#include "write_read_stream.h"

enum errors_code {ERR_TRY_TO_MAKE_INC_REC = -1, ERR_NULL_STREAM = 1};

enum mode_flags {ACT_ENT_CLIENT = 1, ACT_ENT_TRANS};

enum correct_args_count {COR_TRANS_ARG_C = 2, COR_CLIENT_ARG_C = 8};

int write_client_data(FILE *input_stream, FILE *output_stream) {
    if (input_stream == NULL || output_stream == NULL)
        return ERR_NULL_STREAM;
    print_welcome_mes(ACT_ENT_CLIENT);
    accounting_data_t client_data = {0};
    while (read_stream(input_stream, &client_data, ACT_ENT_CLIENT) == COR_CLIENT_ARG_C) {
        if (write_stream(output_stream, client_data, ACT_ENT_CLIENT) != COR_CLIENT_ARG_C) {
            return ERR_TRY_TO_MAKE_INC_REC;
        }
    }
    return 0;
}

int commit_transaction(FILE *input_stream, FILE *output_stream) {
    print_welcome_mes(ACT_ENT_TRANS);
    if (input_stream == NULL || output_stream == NULL)
        return ERR_NULL_STREAM;
    accounting_data_t transfer_data = {0};
    while (read_stream(input_stream, &transfer_data, ACT_ENT_TRANS) == COR_TRANS_ARG_C) {
        if (write_stream(output_stream, transfer_data, ACT_ENT_TRANS) != COR_TRANS_ARG_C) {
            return ERR_TRY_TO_MAKE_INC_REC;
        }
    }
    return 0;
}

int update_credit_limit(FILE *client_stream, FILE *transaction_stream, FILE *upd_client_stream) {
    if ((client_stream == NULL) || (transaction_stream == NULL) || (upd_client_stream == NULL))
        return ERR_NULL_STREAM;
    accounting_data_t client_data = {0};
    accounting_data_t transfer_data = {0};
    while (read_stream(client_stream, &client_data, ACT_ENT_CLIENT) == COR_CLIENT_ARG_C) {
        while (read_stream(transaction_stream, &transfer_data, ACT_ENT_TRANS) == COR_TRANS_ARG_C) {
            if (client_data.account_id == transfer_data.account_id && transfer_data.cash_payments != 0) {
                client_data.credit_limit += transfer_data.cash_payments;
                if (write_stream(upd_client_stream, client_data, ACT_ENT_CLIENT) != COR_CLIENT_ARG_C) {
                    return ERR_TRY_TO_MAKE_INC_REC;
                }
            }
        }
        rewind(transaction_stream);
    }
    return 0;
}
