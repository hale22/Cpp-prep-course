#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define ERR_EOF     (-1)
#define ERR_EOL     (-1)
#define ERR_ACCES   "Not access"

#define PHONE_ARR_SIZE  15
#define ADRES_ARR_SIZE  20
#define NAME_ARR_SIZE   20

#define ACT_ENT_CLIENT      1
#define ACT_ENT_TRANS       2
#define ACT_ENT_UPD_CLIENT  3

#define FILE_NAME_ENT_CLIENT    "clients.dat"
#define FILE_NAME_ENT_TRANS     "transaction.dat"
#define FILE_NAME_UPD_CLIENT    "updated_clients.dat"

typedef struct accounting_data {
  int account_id;
  char name[NAME_ARR_SIZE];
  char surname[NAME_ARR_SIZE];
  char address[ADRES_ARR_SIZE];
  char phone_number[PHONE_ARR_SIZE];
  double indebtedness;
  double credit_limit;
  double cash_payments;
} accounting_data_t;

typedef struct transaction_data {
  int account_id;
  double cash_payments;
} transaction_data_t;

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
        printf("%s\n%s\n",
            "1 Number account:",
            "2 Client cash payments: ");
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

int main(void) {
    int choice = 0;
    FILE *client_strm = NULL;
    FILE *transaction_strm = NULL;
    FILE *upd_strm = NULL;
    accounting_data_t client_data = {0};
    transaction_data_t transfer_data = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != ERR_EOF) {
        switch (choice) {
            case ACT_ENT_CLIENT: {
                client_strm = fopen(FILE_NAME_ENT_CLIENT, "r+");
                if (client_strm == NULL) {
                    puts(ERR_ACCES);
                } else {
                    write_client_data(client_strm, client_data);
                    fclose(client_strm);
                }
                break;
            }
            case ACT_ENT_TRANS: {
                transaction_strm = fopen(FILE_NAME_ENT_TRANS, "r+");
                if (transaction_strm == NULL) {
                    puts(ERR_ACCES);
                } else {
                    commit_transaction(transaction_strm, transfer_data);
                    fclose(transaction_strm);
                }
                break;
            }
            case ACT_ENT_UPD_CLIENT: {
                client_strm = fopen(FILE_NAME_ENT_CLIENT, "r");
                transaction_strm = fopen(FILE_NAME_ENT_TRANS, "r");
                upd_strm = fopen(FILE_NAME_UPD_CLIENT, "w");
                if (client_strm == NULL || transaction_strm == NULL || upd_strm == NULL) {
                    puts("exit");
                } else {
                    update_credit_limit(client_strm, transaction_strm, upd_strm, client_data, transfer_data);
                    fclose(client_strm);
                    fclose(transaction_strm);
                    fclose(upd_strm);
                }
                break;
            }
            default: {
                puts("error");
                break;
            }
        }
    }
    return 0;
}
