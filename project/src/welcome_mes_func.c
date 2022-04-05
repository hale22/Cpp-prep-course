#include <stddef.h>
#include <stdio.h>

#include "welcome_mes_func.h"

#define ERR_INC_WEL_MES_FLAG    (-1)

#define INIT_MESSAGE        0
#define ACT_ENT_CLIENT      1
#define ACT_ENT_TRANS       2

#define WEL_MES_ENT_CLIENT "1 Number account: ", \
        "2 Client name: ", \
        "3 Surname: ", \
        "4 Addres client: ", \
        "5 Client Telnum: ", \
        "6 Client indebtedness: ", \
        "7 Client credit limit: ", \
        "8 Client cash payments:"
#define WEL_MES_INIT "please enter action", \
        "1 enter data client:", \
        "2 enter data transaction:", \
        "3 update base"
#define  WEL_MES_ENT_TRANS "1 Number account: ", \
        "2 Client cash payments: "

const char *fs_init_mes = "%s\n%s\n%s\n%s\n";
const char *fs_ent_client_mes = "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n";
const char *fs_ent_trans_mes = "%s\n%s\n";

int print_welcome_mes(int mode) {
    switch (mode) {
    case INIT_MESSAGE: {
        printf(fs_init_mes, WEL_MES_INIT);
        break;
    }
    case ACT_ENT_CLIENT: {
        printf(fs_ent_client_mes, WEL_MES_ENT_CLIENT);
        break;
    }
    case ACT_ENT_TRANS: {
        printf(fs_ent_trans_mes, WEL_MES_ENT_TRANS);
        break;
    }
    default:
        return ERR_INC_WEL_MES_FLAG;
    }
    return 0;
}
