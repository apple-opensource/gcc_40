/* Testcase for http://gcc.gnu.org/ml/gcc-patches/2003-02/msg01017.html */
/* { dg-do link } */
/* { dg-options "-O -fpic" } */
/* APPLE LOCAL -mdynamic-no-pic incompatible with -fpic */
/* { dg-skip-if "Not valid with -mdynamic-no-pic" { *-*-darwin* } { "-mdynamic-no-pic" } { "" } } */
/* { dg-warning "not supported" "PIC unsupported" { target cris-*-elf* cris-*-aout* mmix-*-* } 0 } */
/* { dg-bogus "\[Uu\]nresolved symbol .(_GLOBAL_OFFSET_TABLE_|\[_.A-Za-z\]\[_.0-9A-Za-z\]*@(PLT|GOT|GOTOFF))" "PIC unsupported" { xfail *-*-netware* } 0 } */

int *g;

int main (void)
{
  switch (*g)
    {
    case 0:
      {
        switch (*g)
          {
          case 0: *g = 1; break;
          case 1:
          case 2: *g = 1; break;
          case 3:
          case 4: *g = 1; break;
          }
        break;
      }
    case 1:
      {
        switch (*g)
          {
          case 0: *g = 1; break;
          case 1:
          case 2: *g = 1; break;
          case 3:
          case 4: *g = 1; break;
          }
      }
    }
  return 0;
}
