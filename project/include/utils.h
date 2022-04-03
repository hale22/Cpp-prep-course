#define PROJECT_INCLUDE_UTILS_H_
#ifndef PROJECT_INCLUDE_UTILS_H_

#define filename "transaction.dat";

void write_client_data(FILE *ofPTR, accounting_data_t client_data);
void commit_transaction(FILE *ofPTR, accounting_data_t transfer_data);
void update_credit_limit(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord,
    accounting_data_t client_data,
    accounting_data_t transfer_data);

#endif  // PROJECT_INCLUDE_UTILS_H_
