#include <check.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_test) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  int ret = s21_create_matrix(rows, columns, &M);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&M);
  rows = rand() % 100 + 1;
  columns = rand() % 100 + 1;
  ret = s21_create_matrix(rows, columns, &M);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(rows, M.rows);
  ck_assert_int_eq(columns, M.columns);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(s21_remove_matrix_test) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

START_TEST(s21_eq_matrix_test) {
  int rows = 3;
  int columns = 3;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      M.matrix[i][j] = i;
      N.matrix[i][j] = i + 1;
    }
  }
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(FAILURE, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      M.matrix[i][j] = i;
      N.matrix[i][j] = i;
    }
  }
  ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(SUCCESS, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 3;
      B.matrix[i][j] = t / 5;
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }
  int ret = s21_sum_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 3;
      B.matrix[i][j] = t / 5;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  int ret = s21_sub_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_number_test) {
  double number = (rand() % 100 + 1) / 3;
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 2;
      C.matrix[i][j] = number * A.matrix[i][j];
    }
  }
  int ret = s21_mult_number(&A, number, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  int rowsA = 2;
  int columnsA = 1;
  int columnsB = 2;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(columnsA, columnsB, &B);
  s21_create_matrix(rowsA, columnsB, &C);
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < columnsA; j++) {
      A.matrix[i][j] = i + 2;
    }
  }
  for (int i = 0; i < columnsA; i++) {
    for (int j = 0; j < columnsB; j++) {
      B.matrix[i][j] = j + 1;
    }
  }
  C.matrix[0][0] = 2;
  C.matrix[0][1] = 4;
  C.matrix[1][0] = 3;
  C.matrix[1][1] = 6;
  int ret = s21_mult_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_transpose_test) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 7;
      C.matrix[j][i] = t / 7;
    }
  }
  int ret = s21_transpose(&A, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_test) {
  int rows = 3;
  int columns = 3;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  A.matrix[0][0] = 6;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 4;
  C.matrix[0][0] = 0;
  C.matrix[0][1] = 0.4;
  C.matrix[0][2] = -0.2;
  C.matrix[1][0] = 2;
  C.matrix[1][1] = -4.2;
  C.matrix[1][2] = 1.6;
  C.matrix[2][0] = -1;
  C.matrix[2][1] = 1.8;
  C.matrix[2][2] = -0.4;
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(0, ret);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_determinant_test) {
  int rows = 1;
  int columns = 1;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 5;
  double det = 5;
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(res, det);
  s21_remove_matrix(&A);

  rows = 2;
  columns = 2;
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  det = -2;
  ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(res, det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
  int rows = 1;
  int columns = 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 5;
  int ret = s21_inverse_matrix(&A, &R);
  double inv = 0.2;
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(inv, R.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

int main() {
  int result;
  Suite *suite = suite_create("s21_matrix");
  TCase *tcase = tcase_create("s21_matrix");
  SRunner *srunner = srunner_create(suite);

  suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, s21_create_matrix_test);
  tcase_add_test(tcase, s21_remove_matrix_test);
  tcase_add_test(tcase, s21_eq_matrix_test);
  tcase_add_test(tcase, s21_sum_matrix_test);
  tcase_add_test(tcase, s21_sub_matrix_test);
  tcase_add_test(tcase, s21_mult_number_test);
  tcase_add_test(tcase, s21_mult_matrix_test);
  tcase_add_test(tcase, s21_transpose_test);
  tcase_add_test(tcase, s21_calc_complements_test);
  tcase_add_test(tcase, s21_determinant_test);
  tcase_add_test(tcase, s21_inverse_matrix_test);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  if (result == 0) {
    return 0;
  } else {
    return 1;
  }
}