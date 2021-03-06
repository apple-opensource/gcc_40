/* APPLE LOCAL file radar 4621020 */
/* Test a variety of error reporting on mis-use of 'weak' attribute */
/* { dg-do compile { target powerpc*-*-darwin* i?86*-*-darwin* } } */
/* APPLE LOCAL radar 4899595 */
/* { dg-options "-fno-objc-new-property -mmacosx-version-min=10.5 -fobjc-gc" } */
/* { dg-require-effective-target objc_gc } */

@interface INTF
{
  id IVAR;
}
@property (weak, ivar=IVAR, bycopy) id pweak;
@end	/* { dg-error "existing ivar \'IVAR\' for a \'weak\' property must be __weak" } */
/* { dg-error "\'weak\' and \'bycopy\' or \'byref\' attributes both cannot" "" { target *-*-* } 13 } */

@implementation INTF
@property (weak, ivar=IVAR, bycopy) id pweak;
@end

