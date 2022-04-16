#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "manage_functions.h"
#include "structs.h"
#include "welcome_mes_func.h"
#include "write_read_stream.h"

enum errors_code {ERR_EOL = -1, ERR_NULL_STREAM = 1, ERR_INC_MODE};

enum mode_flags {INIT_MESSAGE = 0, ACT_ENT_CLIENT, ACT_ENT_TRANS, ACT_ENT_UPD_CLIENT};

#define F_NAME_ENT_CLIENT   "clients.dat"
#define F_NAME_ENT_TRANS    "transaction.dat"
#define F_NAME_UPD_CLIENT   "updated_clients.dat"

int main(void) {
    FILE *client_strm = NULL;
    FILE *transaction_strm = NULL;
    FILE *upd_strm = NULL;
    print_welcome_mes(INIT_MESSAGE);
    int choice = 0;
    while (scanf("%d", &choice) != ERR_EOL) {
        switch (choice) {
            case ACT_ENT_CLIENT: {
                client_strm = fopen(F_NAME_ENT_CLIENT, "r+");
                if (client_strm != NULL) {
                    write_client_data(stdin, client_strm);
                    fclose(client_strm);
                } else {
                    return ERR_NULL_STREAM;
                }
                break;
            }
            case ACT_ENT_TRANS: {
                transaction_strm = fopen(F_NAME_ENT_TRANS, "r+");
                if (transaction_strm != NULL) {
                    commit_transaction(stdin, transaction_strm);
                    fclose(transaction_strm);
                } else {
                    return ERR_NULL_STREAM;
                }
                break;
            }
            case ACT_ENT_UPD_CLIENT: {
                client_strm = fopen(F_NAME_ENT_CLIENT, "r");
                transaction_strm = fopen(F_NAME_ENT_TRANS, "r");
                upd_strm = fopen(F_NAME_UPD_CLIENT, "w");
                if (client_strm != NULL && transaction_strm != NULL && upd_strm != NULL) {
                    update_credit_limit(client_strm, transaction_strm, upd_strm);
                    fclose(client_strm);
                    fclose(transaction_strm);
                    fclose(upd_strm);
                } else {
                    return ERR_NULL_STREAM;
                }
                break;
            }
            default: {
                return ERR_INC_MODE;
            }
        }
    }
    return 0;
}
