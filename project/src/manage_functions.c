#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "manage_functions.h"
#include "welcome_mes_func.h"
#include "write_read_stream.h"

#define ERR_TRY_TO_MAKE_INC_REC (-1)

#define ACT_ENT_CLIENT  1
#define ACT_ENT_TRANS   2

#define COR_CLIENT_ARG_C    8
#define COR_TRANS_ARG_C     2

int write_client_data(FILE *input_stream, FILE *output_stream, accounting_data_t client_data) {
    print_welcome_mes(ACT_ENT_CLIENT);
    while (read_stream(input_stream, &client_data, ACT_ENT_CLIENT) == COR_CLIENT_ARG_C) {
        if (write_stream(output_stream, client_data, ACT_ENT_CLIENT) != COR_CLIENT_ARG_C) {
            return ERR_TRY_TO_MAKE_INC_REC;
        }
    }
    return 0;
}

int commit_transaction(FILE *input_stream, FILE *output_stream, accounting_data_t transfer_data) {
    print_welcome_mes(ACT_ENT_TRANS);
    while (read_stream(input_stream, &transfer_data, ACT_ENT_TRANS) == COR_TRANS_ARG_C) {
        if (write_stream(output_stream, transfer_data, ACT_ENT_TRANS) != COR_TRANS_ARG_C) {
            return ERR_TRY_TO_MAKE_INC_REC;
        }
    }
    return 0;
}

int update_credit_limit(FILE *client_stream, FILE *transaction_stream, FILE *upd_client_stream,
    accounting_data_t client_data, accounting_data_t transfer_data) {
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
