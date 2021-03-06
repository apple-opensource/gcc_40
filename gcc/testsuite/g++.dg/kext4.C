/* APPLE LOCAL file KEXT double destructor */
/* { dg-do compile } */
/* { dg-options "-fapple-kext" } */
/* { dg-skip-if "Not valid on 64-bit" { *-*-darwin* } { "-m64" } { "" } } */
/* test for use of apple_kext_compatibility on stack */
struct B1 {
  virtual ~B1();
} __attribute__((apple_kext_compatibility));

struct D1 : B1 {
  void operator delete(void *) { }
  D1();
};

struct D2 : B1 {
  void operator delete(void *);
  D2();
};

struct D3 : B1 {
  D3();
};

void foo() {
  D1 d1;			// ok
  D2 d2;			// { dg-warning "is an instance of a class" }
  D3 d3;			// { dg-warning "is an instance of a class" }
}
