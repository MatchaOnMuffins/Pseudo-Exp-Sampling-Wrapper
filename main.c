#include "Pseudo_Exp_Sampling.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc != 6) {
    printf("Usage: %s Start End Step_Size Sparseness Num_Exp\n", argv[0]);
    return 1;
  }
  double Start = strtod(argv[1], NULL);
  double End = strtod(argv[2], NULL);
  double Step_Size = strtod(argv[3], NULL);
  double Sparseness = strtod(argv[4], NULL);
  double Num_Exp = strtod(argv[5], NULL);
  int total_size_ = (int)((End - Start) / Step_Size * Sparseness + 1) - 1;

  double New_Data_Array[total_size_];

  Pseudo_Exp_Sampling_wrapper(Start, End, Step_Size, Sparseness, Num_Exp,
                              New_Data_Array, total_size_);

  for (int i = 0; i < total_size_; i++) {
    printf("%f \n", New_Data_Array[i]);
  }
  return 0;
}