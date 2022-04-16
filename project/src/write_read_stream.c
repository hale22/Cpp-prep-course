#include <stdio.h>

#include "structs.h"
#include "write_read_stream.h"

enum errors_code {ERR_INC_ENT_ARG_ONE = 101, ERR_INC_ENT_ARG_TWO,
ERR_INC_ENT_ARG_THR, ERR_INC_ENT_ARG_FOUR, ERR_INC_ENT_ARG_FIVE,
ERR_INC_ENT_ARG_SIX, ERR_INC_ENT_ARG_SEV, ERR_INC_ENT_ARG_EIT,
ERR_NULL_STREAM = 201, ERR_INC_MODE};

enum correct_args_count {COR_ARGC_ID_ALT_TRANS = 3, COR_ARGC_CASH_TRANS = 7,
COR_ARGC_NAME = 11, COR_ARGC_SNAME = 11, COR_ARGC_ID, COR_ARGC_INDEB = 12,
COR_ARGC_LIM  = 12, COR_ARGC_CASH, COR_ARGC_ADR = 16, COR_ARGC_PHONE = 20};

enum mode_flags {ACT_ENT_CLIENT = 1, ACT_ENT_TRANS};

int read_stream(FILE *stream, accounting_data_t *accounting_data, int mode) {
    if (stream != NULL) {
        int counter = 0;
        switch (mode) {
        case ACT_ENT_CLIENT: {
            if (fscanf(stream, "%12d", &(accounting_data->account_id)) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_ONE;
            }
            if (fscanf(stream, "%11s", accounting_data->name) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_TWO;
            }
            if (fscanf(stream, "%11s", accounting_data->surname) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_THR;
            }
            if (fscanf(stream, "%16s", accounting_data->address) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_FOUR;
            }
            if (fscanf(stream, "%20s", accounting_data->phone_number) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_FIVE;
            }
            if (fscanf(stream, "%12lf", &(accounting_data->indebtedness)) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_SIX;
            }
            if (fscanf(stream, "%12lf", &(accounting_data->credit_limit)) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_SEV;
            }
            if (fscanf(stream, "%12lf", &(accounting_data->cash_payments)) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_EIT;
            }
            return counter;
        }
        case ACT_ENT_TRANS: {
            if (fscanf(stream, "%12d", &(accounting_data->account_id)) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_ONE;
            }
            if (fscanf(stream, "%12lf", &(accounting_data->cash_payments)) == 1) {
                ++counter;
            } else {
                return ERR_INC_ENT_ARG_EIT;
            }
            return counter;
        }
        default:
            return ERR_INC_MODE;
        }
    } else {
        return ERR_NULL_STREAM;
    }
}

int write_stream(FILE *stream, accounting_data_t accounting_data, int mode) {
    if (stream != NULL) {
        int counter = 0;
        switch (mode) {
            case ACT_ENT_CLIENT: {
                if (fprintf(stream, "%-12d", accounting_data.account_id) == COR_ARGC_ID) ++counter;
                if (fprintf(stream, "%-11s", accounting_data.name) == COR_ARGC_NAME) ++counter;
                if (fprintf(stream, "%-11s", accounting_data.surname) == COR_ARGC_SNAME) ++counter;
                if (fprintf(stream, "%-16s", accounting_data.address) == COR_ARGC_ADR) ++counter;
                if (fprintf(stream, "%20s", accounting_data.phone_number) == COR_ARGC_PHONE) ++counter;
                if (fprintf(stream, "%12.2f", accounting_data.indebtedness) == COR_ARGC_INDEB) ++counter;
                if (fprintf(stream, "%12.2f", accounting_data.credit_limit) == COR_ARGC_LIM) ++counter;
                if (fprintf(stream, "%12.2f\n", accounting_data.cash_payments) == COR_ARGC_CASH) ++counter;
                return counter;
            }
            case ACT_ENT_TRANS: {
                if (fprintf(stream, "%-3d", accounting_data.account_id) == COR_ARGC_ID_ALT_TRANS) ++counter;
                if (fprintf(stream, "%-6.2f\n", accounting_data.cash_payments) == COR_ARGC_CASH_TRANS)
                    ++counter;
                return counter;
            }
            default:
                return ERR_INC_MODE;
            }

    } else {
        return ERR_NULL_STREAM;
    }
}
