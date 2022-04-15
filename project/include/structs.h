#ifndef PROJECT_INCLUDE_STRUCTS_H_
#define PROJECT_INCLUDE_STRUCTS_H_

#define PHONE_ARR_SIZE  15
#define NAME_ARR_SIZE   20
#define ADRES_ARR_SIZE  30


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

#endif  // PROJECT_INCLUDE_STRUCTS_H_
