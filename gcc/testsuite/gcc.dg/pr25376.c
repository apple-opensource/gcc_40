/* APPLE LOCAL file mainline 2006-02-13 radar 4373419 */
/* PR25376.  Verify that a named section is honored.  */
/* { dg-require-named-sections "" } */

void simple (void) __attribute__((section("my_named_section")));
void simple (void)
{
}

/* { dg-final { scan-assembler "my_named_section" } } */
