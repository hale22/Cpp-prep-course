#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "utils.h"
#include "welcome_mes_func.h"

#define ERR_EOF                 (-1)
#define ERR_EOL                 (-1)
#define ERR_NULL_STREAM         1

#define ACT_ENT_CLIENT      1
#define ACT_ENT_TRANS       2

/*int read_stream(FILE *stream, accounting_data_t accounting_data, int mode) {
    if (stream != NULL) {
        switch (mode)
        {
        case ACT_ENT_CLIENT:
            fscanf("%12d%11s%11s%16s%20s%12lf%12lf%12lf",
        &accounting_data.account_id, accounting_data.name, accounting_data.surname,
        accounting_data.address, accounting_data.phone_number,
        &accounting_data.indebtedness, &accounting_data.credit_limit, &accounting_data.cash_payments)
            break;
        
        default:
            break;
        }
    } else {
        return ERR_NULL_STREAM;
    }
    return 0;
}*/

void write_client_data(FILE *client_stream, accounting_data_t client_data) {
    print_welcome_mes(ACT_ENT_CLIENT);
    while (scanf("%12d%11s%11s%16s%20s%12lf%12lf%12lf",
        &client_data.account_id, client_data.name, client_data.surname,
        client_data.address, client_data.phone_number,
        &client_data.indebtedness, &client_data.credit_limit, &client_data.cash_payments) != ERR_EOL) {
        fprintf(client_stream, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            client_data.account_id, client_data.name, client_data.surname,
            client_data.address, client_data.phone_number,
            client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);
    }
}

void commit_transaction(FILE *transaction_stream, accounting_data_t transfer_data) {
    print_welcome_mes(ACT_ENT_TRANS);
    while (scanf("%d%lf", &transfer_data.account_id, &transfer_data.cash_payments) != ERR_EOL) {
        fprintf(transaction_stream, "%-3d%-6.2f\n", transfer_data.account_id, transfer_data.cash_payments);
    }
}

void update_credit_limit(FILE *client_stream, FILE *transaction_stream, FILE *upd_client_stream,
    accounting_data_t client_data, accounting_data_t transfer_data) {
    while (fscanf(client_stream, "%12d%11s%11s%16s%20s%12lf%12lf%12lf",
        &client_data.account_id, client_data.name, client_data.surname,
        client_data.address, client_data.phone_number,
        &client_data.indebtedness, &client_data.credit_limit, &client_data.cash_payments) != ERR_EOF) {
        while (fscanf(transaction_stream, "%12d%12lf",
            &transfer_data.account_id, &transfer_data.cash_payments) != ERR_EOF) {
            if (client_data.account_id == transfer_data.account_id && transfer_data.cash_payments != 0) {
                client_data.credit_limit += transfer_data.cash_payments;
            }
        }
        fprintf(upd_client_stream, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            client_data.account_id, client_data.name, client_data.surname,
            client_data.address, client_data.phone_number,
            client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);
        rewind(transaction_stream);
    }
}
