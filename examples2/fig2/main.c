#include <msp430.h>

//uint16_t assert(int32_t a);
//uint16_t ADC10MEM0 = 0;

#define MAXARGC 20
//uint16_t argc; uint16_t argv[MAXARGC];

uint16_t main()
{
  uint16_t argc; char argv[MAXARGC];
  int x = 0;
  uint16_t  i,n =0, b[4] = {0,0,0,0};
  klee_make_symbolic(&argc, sizeof(argc), "argc");
  klee_make_symbolic(argv, MAXARGC, "argv");

  for(i=0; i< argc; i++)
  {
    if(argv[i] == 'b') {
      if(n>=4)
        assert(0);
      b[n++] = 1;
    } else
      x++;
  }
  uint16_t z = 0;
  while (1) {
    z++;
  }
  return 0;
}
