#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = 0;

  if (rows < 1 || columns < 1) {
    status = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
  }

  for (int i = 0; status == 0 && i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }

  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    status = FAILURE;
  }

  for (int i = 0; status == SUCCESS && i < A->rows; i++) {
    for (int j = 0; status == SUCCESS && j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) status = FAILURE;
    }
  }

  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0, t = 0;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    status = 2;
  } else {
    t = s21_create_matrix(A->rows, A->columns, result);
  }

  for (int i = 0; status == 0 && t == 0 && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0, t = 0;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    status = 2;
  } else {
    t = s21_create_matrix(A->rows, A->columns, result);
  }

  for (int i = 0; status == 0 && t == 0 && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = 0, t = 0;

  if (A->matrix == NULL) {
    status = 1;
  } else {
    t = s21_create_matrix(A->rows, A->columns, result);
  }
  for (int i = 0; status == 0 && t == 0 && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = number * A->matrix[i][j];
    }
  }

  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0, t = 0;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = 1;
  } else if (A->columns != B->rows) {
    status = 2;
  } else {
    t = s21_create_matrix(A->rows, B->columns, result);
  }

  for (int i = 0; status == 0 && t == 0 && i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = 0, t = 0;

  if (A->matrix == NULL) {
    status = 1;
  } else {
    t = s21_create_matrix(A->columns, A->rows, result);
  }

  for (int i = 0; status == 0 && t == 0 && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0, t = 0;

  if (A->columns != A->rows) {
    status = 2;
  } else if (A->matrix == NULL) {
    status = 1;
  } else {
    t = s21_create_matrix(A->columns, A->rows, result);
  }

  for (int i = 0; status == 0 && t == 0 && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor = {0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      s21_minor_matrix(A, i, j, &minor);
      double det = 0;
      s21_determinant(&minor, &det);
      s21_remove_matrix(&minor);
      int sign = (i + j) % 2;
      result->matrix[i][j] = det * pow(-1, sign);
    }
  }

  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = 0;

  if (A->columns != A->rows) {
    status = 2;
  } else if (A->matrix == NULL) {
    status = 1;
  }
  if (status == 0) {
    *result = s21_determinant_matrix(A);
  }

  return status;
}

double s21_determinant_matrix(matrix_t *A) {
  double det = 0;

  if (A->columns == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else if (A->columns == 1) {
    det = A->matrix[0][0];
  } else if (A->columns > 2) {
    for (int i = 0; i < A->rows; i++) {
      matrix_t minor = {0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      s21_minor_matrix(A, 0, i, &minor);
      double det_minor = s21_determinant_matrix(&minor);
      int sign = i % 2;
      det += A->matrix[0][i] * det_minor * pow(-1, sign);
      s21_remove_matrix(&minor);
    }
  }

  return det;
}

void s21_minor_matrix(matrix_t *A, int row, int col, matrix_t *result) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      if (j < col && i < row) result->matrix[i][j] = A->matrix[i][j];
      if (j >= col && i < row) result->matrix[i][j] = A->matrix[i][j + 1];
      if (j < col && i >= row) result->matrix[i][j] = A->matrix[i + 1][j];
      if (j >= col && i >= row) result->matrix[i][j] = A->matrix[i + 1][j + 1];
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = 0;
  double det = 0;

  if (A->columns != A->rows) {
    status = 2;
  } else if (A->matrix == NULL) {
    status = 1;
  }

  if (status == 0) {
    s21_determinant(A, &det);
    if (det == 0) {
      status = 2;
    } else if (det != 0 && A->rows == 1) {
      s21_create_matrix(A->columns, A->rows, result);
      result->matrix[0][0] = 1 / det;
    } else if (det != 0 && A->rows > 1) {
      matrix_t C = {0};
      s21_calc_complements(A, &C);
      matrix_t T = {0};
      s21_transpose(&C, &T);
      s21_remove_matrix(&C);
      s21_mult_number(&T, 1 / det, result);
      s21_remove_matrix(&T);
    }
  }

  return status;
}