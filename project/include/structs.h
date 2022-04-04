#ifndef PROJECT_INCLUDE_STRUCTS_H_
#define PROJECT_INCLUDE_STRUCTS_H_

#define PHONE_ARR_SIZE  15
#define ADRES_ARR_SIZE  20
#define NAME_ARR_SIZE   20

typedef struct accounting_data {
  int account_id;
  char name[20];
  char surname[20];
  char address[30];
  char phone_number[15];
  double indebtedness;
  double credit_limit;
  double cash_payments;
} accounting_data_t;

typedef struct transaction_data {
  int account_id;
  double cash_payments;
} transaction_data_t;

#endif  // PROJECT_INCLUDE_STRUCTS_H_
