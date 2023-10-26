#include "PPintrin.h"

// implementation of absSerial(), but it is vectorized using PP intrinsics
void absVector(float *values, float *output, int N)
{
  __pp_vec_float x;
  __pp_vec_float result;
  __pp_vec_float zero = _pp_vset_float(0.f);
  __pp_mask maskAll, maskIsNegative, maskIsNotNegative;

  //  Note: Take a careful look at this loop indexing.  This example
  //  code is not guaranteed to work when (N % VECTOR_WIDTH) != 0.
  //  Why is that the case?
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {

    // All ones
    maskAll = _pp_init_ones(min(VECTOR_WIDTH, N - i));

    // All zeros
    maskIsNegative = _pp_init_ones(0);

    // Load vector of values from contiguous memory addresses
    _pp_vload_float(x, values + i, maskAll); // x = values[i];

    // Set mask according to predicate
    _pp_vlt_float(maskIsNegative, x, zero, maskAll); // if (x < 0) {

    // Execute instruction using mask ("if" clause)
    _pp_vsub_float(result, zero, x, maskIsNegative); //   output[i] = -x;

    // Inverse maskIsNegative to generate "else" mask
    maskIsNotNegative = _pp_mask_not(maskIsNegative); // } else {
    maskIsNotNegative = _pp_mask_and(maskIsNotNegative, maskAll);

    // Execute instruction ("else" clause)
    _pp_vload_float(result, values + i, maskIsNotNegative); //   output[i] = x; }

    // Write results back to memory
    _pp_vstore_float(output + i, result, maskAll);
  }
}

void clampedExpVector(float *values, int *exponents, float *output, int N)
{
  //
  // PP STUDENTS TODO: Implement your vectorized version of
  // clampedExpSerial() here.
  //
  // Your solution should work for any value of
  // N and VECTOR_WIDTH, not just when VECTOR_WIDTH divides N
  //
  // Declare variables
  __pp_vec_float x, result;
  __pp_vec_int y, count;
  __pp_vec_int zeroInt = _pp_vset_int(0);
  __pp_vec_int onesInt = _pp_vset_int(1);
  __pp_vec_float onesFloat = _pp_vset_float(1.f);
  __pp_vec_float tensFloat = _pp_vset_float(9.999999f);
  __pp_mask maskAll, maskIsPosstive, maskIsZero, maskIsNotZero, maskIsTens;
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {
    // All ones mask (work for any value of N and VECTOR_WIDTH)
    maskAll = _pp_init_ones(min(VECTOR_WIDTH, N - i));
    // Initialize maskIsZero to all zeros
    maskIsZero = _pp_init_ones(0);
    // Initialize maskIsPosstive to all zeros
    maskIsPosstive = _pp_init_ones(0);
    // Initialize maskIsTens to all zeros
    maskIsTens = _pp_init_ones(0);
    // x = values[i];
    _pp_vload_float(x, values + i, maskAll);
    // y = exponents[i];
    _pp_vload_int(y, exponents + i, maskAll);
    // if (y == 0) {
    _pp_veq_int(maskIsZero, y, zeroInt, maskAll);
    //   output[i] = 1.f;
    _pp_vmove_float(result, onesFloat, maskIsZero);
    // } else { 
    maskIsNotZero = _pp_mask_not(maskIsZero);
    // (work for any value of N and VECTOR_WIDTH)
    maskIsNotZero = _pp_mask_and(maskIsNotZero, maskAll);
    //   result = x;
    _pp_vmove_float(result, x, maskIsNotZero);
    //   count = y - 1;
    _pp_vsub_int(count, y, onesInt, maskIsNotZero);
    //   while (
    while (true)
    {
    //        count > 0
      _pp_vgt_int(maskIsPosstive, count, zeroInt, maskIsNotZero);
    //        ) {
      if (_pp_cntbits(maskIsPosstive) == 0) break;
    //      result *= x;
      _pp_vmult_float(result, result, x, maskIsPosstive);
    //      count--;
      _pp_vsub_int(count, count, onesInt, maskIsPosstive);
    //   }
    }
    //   if (result > 9.999999f) {
    _pp_vgt_float(maskIsTens, result, tensFloat, maskIsNotZero);
    //      result = 9.999999f;
    _pp_vmove_float(result, tensFloat, maskIsTens);
    //   }
    // }
    // output[i] = result;
    _pp_vstore_float(output + i, result, maskAll);
  }
}

// returns the sum of all elements in values
// You can assume N is a multiple of VECTOR_WIDTH
// You can assume VECTOR_WIDTH is a power of 2
float arraySumVector(float *values, int N)
{

  //
  // PP STUDENTS TODO: Implement your vectorized version of arraySumSerial here
  //

  // Declare variables
  __pp_vec_float sum = _pp_vset_float(0.f);
  __pp_vec_float tmp;
  __pp_mask maskAll = _pp_init_ones();
  // Sum of all VECTORs
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {
    // tmp = values[i]
    _pp_vload_float(tmp, values + i, maskAll);
    // sum += tmp
    _pp_vadd_float(sum, sum, tmp, maskAll);
  }
  // Sum of VECTOR_WIDTH elements in sum
  for (int i = 1; i < VECTOR_WIDTH; i *= 2)
  {
    // [0 1 2 3] -> [0+1 0+1 2+3 2+3]
    _pp_hadd_float(sum, sum);
    // [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
    _pp_interleave_float(sum, sum);
  }
  // ret = sum
  float ret[VECTOR_WIDTH];
  _pp_vstore_float(ret, sum, maskAll);
  // return ret[0]
  return ret[0];
}