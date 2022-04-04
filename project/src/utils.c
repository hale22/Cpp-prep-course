#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "utils.h"

#define ERR_EOF     (-1)
#define ERR_EOL     (-1)

void write_client_data(FILE *client_stream, accounting_data_t client_data) {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
        "1 Number account: ",
        "2 Client name: ",
        "3 Surname: ",
        "4 Addres client: ",
        "5 Client Telnum: ",
        "6 Client indebtedness: ",
        "7 Client credit limit: ",
        "8 Client cash payments:");
    while (scanf("%12d%11s%11s%16s%20s%lf%lf%lf",
        &client_data.account_id, client_data.name, client_data.surname,
        client_data.address, client_data.phone_number,
        &client_data.indebtedness, &client_data.credit_limit, &client_data.cash_payments) != ERR_EOL) {
        fprintf(client_stream, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            client_data.account_id, client_data.name, client_data.surname,
            client_data.address, client_data.phone_number,
            client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);
    }
}

void commit_transaction(FILE *transaction_stream, transaction_data_t transfer_data) {
    printf("%s\n%s\n",
        "1 Number account: ",
        "2 Client cash payments: ");
    while (scanf("%d%lf", &transfer_data.account_id, &transfer_data.cash_payments) != ERR_EOL) {
        fprintf(transaction_stream, "%-3d%-6.2f\n", transfer_data.account_id, transfer_data.cash_payments);
    }
}

void update_credit_limit(FILE *client_stream, FILE *transaction_stream, FILE *upd_client_stream,
    accounting_data_t client_data, transaction_data_t transfer_data) {
    while (fscanf(client_stream, "%12d%11s%11s%16s%20s%lf%lf%lf",
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

void hello_world(void) {
    printf("%s", "Hello world");
}