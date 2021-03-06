/* APPLE LOCAL file radar 4631814 */
/* This test should not produce any error or warning when property name is
   assigned to without use of 'self' qualifier. */
/* APPLE LOCAL radar 4899595 */
/* { dg-options "-mmacosx-version-min=10.5" } */
/* { dg-do compile { target powerpc*-*-darwin* i?86*-*-darwin* } } */

#include <Cocoa/Cocoa.h>

@interface NamedObject : NSObject
{
	NSString * name;
}
@property(copy) NSString *name;
@end

@implementation NamedObject
@synthesize name;
- (id)init {
	if (self = [super init]) {
		self.name = @"no name";	// no warning or error.
	}
	
	return self;
}

- (void)dealloc {
	self.name = nil;	// no warning or error.
	[super dealloc];
}
@end

int main(int argc, char **argv) {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NamedObject *object = [[NamedObject alloc] init];
	NSLog(@"object.name == %@", object.name);
	object.name = @"foo";
	NSLog(@"object.name == %@", object.name);
	[object release];
	
	[pool release];
	
	return 0;
}
