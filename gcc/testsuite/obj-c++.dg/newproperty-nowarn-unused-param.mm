/* APPLE LOCAL file radar 5232840 */
/* Test that no warning is issued on 'unused' "_value" parameter even though it is used. */
/* { dg-options "-Wunused-parameter -mmacosx-version-min=10.5" { target powerpc*-*-darwin* i?86*-*-darwin* } } */
/* { dg-options "-Wunused-parameter" { target arm*-*-darwin* } } */
/* { dg-do compile { target *-*-darwin* } } */
@interface MyClass 
{
        int foo;
}
@property(readwrite) int foo;
@end


@implementation MyClass
@synthesize foo;
@end
