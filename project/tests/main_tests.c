#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "write_read_stream.h"

enum correct_args_count {COR_TRANS_ARG_C = 2, COR_CLIENT_ARG_C = 8};

enum mode_flags {ACT_ENT_CLIENT = 1, ACT_ENT_TRANS};

int test_write_to_file(void) {
    const char *test_file_name_client = "test_cl.dat";
    FILE *test_strm = fopen(test_file_name_client, "w+");
    accounting_data_t excepted_client_data = {258, "Ivan",
    "Ivanov", "Moskva,Kreml", "3188282",
    242.00, 12700.59, 3500.88};

    write_stream(test_strm, excepted_client_data, ACT_ENT_CLIENT);
    rewind(test_strm);

    accounting_data_t got_client_data = {0};

    read_stream(test_strm, &got_client_data, ACT_ENT_CLIENT);
    fclose(test_strm);

    int counter_of_client_data = 0;
    if (excepted_client_data.account_id == got_client_data.account_id) ++counter_of_client_data;
    if (strcmp(excepted_client_data.name, got_client_data.name) == 0) ++counter_of_client_data;
    if (strcmp(excepted_client_data.surname, got_client_data.surname) == 0) ++counter_of_client_data;
    if (strcmp(excepted_client_data.address, got_client_data.address) == 0) ++counter_of_client_data;
    if (strcmp(excepted_client_data.phone_number, got_client_data.phone_number) == 0)
        ++counter_of_client_data;
    if (excepted_client_data.indebtedness == got_client_data.indebtedness) ++counter_of_client_data;
    if (excepted_client_data.credit_limit == got_client_data.credit_limit) ++counter_of_client_data;
    if (excepted_client_data.cash_payments == got_client_data.cash_payments) ++counter_of_client_data;

    const char *test_file_name_transac = "test_tr.dat";
    FILE *test_strm_transac = fopen(test_file_name_transac, "w+");
    accounting_data_t excepted_transac_data = {0};

    excepted_transac_data.account_id = 25;
    excepted_transac_data.cash_payments = 22.57;
    write_stream(test_strm_transac, excepted_transac_data, ACT_ENT_TRANS);
    rewind(test_strm_transac);

    accounting_data_t got_transac_data = {0};
    read_stream(test_strm_transac, &got_transac_data, ACT_ENT_TRANS);
    fclose(test_strm_transac);

    int counter_of_transac_data = 0;
    if (excepted_transac_data.account_id == got_transac_data.account_id) ++counter_of_transac_data;
    if (excepted_transac_data.cash_payments == got_transac_data.cash_payments) ++counter_of_transac_data;

    if (counter_of_client_data == COR_CLIENT_ARG_C && counter_of_transac_data == COR_TRANS_ARG_C)
        return 1;
    else
        return 0;
}

int main(void) {
    if (test_write_to_file() == 1)
        printf("%s", "SUCCEED! Functions work correctly");
    else
        printf("%s", "FAIL! Functions dont work correctly");
    return 0;
}
