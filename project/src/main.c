#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "utils.h"

#define ERR_EOF     (-1)
#define ERR_EOL     (-1)
#define ERR_ACCES   "Not access"

#define ACT_ENT_CLIENT      1
#define ACT_ENT_TRANS       2
#define ACT_ENT_UPD_CLIENT  3

#define F_NAME_ENT_CLIENT    "clients.dat"
#define F_NAME_ENT_TRANS     "transaction.dat"
#define F_NAME_UPD_CLIENT    "updated_clients.dat"

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
                client_strm = fopen(F_NAME_ENT_CLIENT, "r+");
                if (client_strm == NULL) {
                    puts(ERR_ACCES);
                } else {
                    write_client_data(client_strm, client_data);
                    fclose(client_strm);
                }
                break;
            }
            case ACT_ENT_TRANS: {
                transaction_strm = fopen(F_NAME_ENT_TRANS, "r+");
                if (transaction_strm == NULL) {
                    puts(ERR_ACCES);
                } else {
                    commit_transaction(transaction_strm, transfer_data);
                    fclose(transaction_strm);
                }
                break;
            }
            case ACT_ENT_UPD_CLIENT: {
                client_strm = fopen(F_NAME_ENT_CLIENT, "r");
                transaction_strm = fopen(F_NAME_ENT_TRANS, "r");
                upd_strm = fopen(F_NAME_UPD_CLIENT, "w");
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
