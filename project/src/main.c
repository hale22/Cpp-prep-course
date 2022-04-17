#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "manage_functions.h"
#include "structs.h"
#include "welcome_mes_func.h"
#include "write_read_stream.h"

enum errors_code {ERR_EOL = -1, ERR_INC_MODE = 0};

enum mode_flags {INIT_MESSAGE = 0, ACT_ENT_CLIENT, ACT_ENT_TRANS, ACT_ENT_UPD_CLIENT};

#define F_NAME_ENT_CLIENT   "clients.dat"
#define F_NAME_ENT_TRANS    "transaction.dat"
#define F_NAME_UPD_CLIENT   "updated_clients.dat"

int main(void) {
    print_welcome_mes(INIT_MESSAGE);
    int choice = 0;
    while (scanf("%d", &choice) != ERR_EOL) {
        switch (choice) {
            case ACT_ENT_CLIENT: {
                FILE *client_strm = fopen(F_NAME_ENT_CLIENT, "r+");
                write_client_data(stdin, client_strm);
                fclose(client_strm);
                break;
            }
            case ACT_ENT_TRANS: {
                FILE *transaction_strm = fopen(F_NAME_ENT_TRANS, "r+");
                commit_transaction(stdin, transaction_strm);
                fclose(transaction_strm);
                break;
            }
            case ACT_ENT_UPD_CLIENT: {
                FILE *client_strm = fopen(F_NAME_ENT_CLIENT, "r");
                FILE *transaction_strm = fopen(F_NAME_ENT_TRANS, "r");
                FILE *upd_strm = fopen(F_NAME_UPD_CLIENT, "w");
                update_credit_limit(client_strm, transaction_strm, upd_strm);
                fclose(client_strm);
                fclose(transaction_strm);
                fclose(upd_strm);
                break;
            }
            default: {
                return ERR_INC_MODE;
            }
        }
    }
    return 0;
}
