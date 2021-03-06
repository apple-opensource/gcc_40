/* APPLE LOCAL file ARM darwin target */

#define SUBTARGET_CPU_DEFAULT arm920

#undef SUBTARGET_EXTRA_ASM_SPEC
#define SUBTARGET_EXTRA_ASM_SPEC ""

#define rs6000_alignment_flags target_flags
#define MASK_ALIGN_MAC68K       (1 << 30)
#define TARGET_ALIGN_MAC68K     (target_flags & MASK_ALIGN_MAC68K)
#define MASK_ALIGN_NATURAL	(1 << 29)
#define TARGET_ALIGN_NATURAL	(target_flags & MASK_ALIGN_NATURAL)
#define MASK_MACHO_DYNAMIC_NO_PIC (1 << 28)
#define TARGET_DYNAMIC_NO_PIC	(target_flags & MASK_MACHO_DYNAMIC_NO_PIC)

#define DEFAULT_TARGET_ARCH "arm"

#undef TARGET_VERSION
#define TARGET_VERSION fprintf (stderr, " (arm Darwin)");

#define TARGET_OS_CPP_BUILTINS()                \
  do                                            \
    {                                           \
      builtin_define ("__arm__") ;              \
      builtin_define ("__arm");                 \
      builtin_define ("__LITTLE_ENDIAN__");     \
      darwin_cpp_builtins (pfile);		\
    }                                           \
  while (0)

/* We want -fPIC by default, unless we're using -static to compile for
   the kernel or some such.  */

#undef CC1_SPEC
#define CC1_SPEC "%<faltivec %<mcpu=G4 %<mcpu=G5 \
%{!mmacosx-version-min=*: %{!miphoneos-version-min=*: %(darwin_cc1_minversion)}} \
%{static: %{Zdynamic: %e conflicting code gen style switches are used}} \
%{static: %{mdynamic-no-pic: %e conflicting code gen style switches are used}} \
%{!static:%{!mdynamic-no-pic:-fPIC}} \
%{!fbuiltin-strcat:-fno-builtin-strcat} \
%{!fbuiltin-strcpy:-fno-builtin-strcpy} \
%<fbuiltin-strcat \
%<fbuiltin-strcpy"

#undef LIB_SPEC
#define LIB_SPEC "%{!static:-lSystem}"

/* Use the following macro for any Darwin/x86-specific command-line option
   translation.  */
#define SUBTARGET_OPTION_TRANSLATE_TABLE \
  { "", "" }

#define REGISTER_PREFIX 	""

/* The assembler's names for the registers.  */
#ifndef REGISTER_NAMES
#define REGISTER_NAMES				   \
{				                   \
  "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",  \
  "r8", "r9", "r10","r11","ip", "sp", "lr", "pc",  \
  "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",  \
  "cc", "sfp", "afp",		   		   \
  "mv0",   "mv1",   "mv2",   "mv3",		   \
  "mv4",   "mv5",   "mv6",   "mv7",		   \
  "mv8",   "mv9",   "mv10",  "mv11",		   \
  "mv12",  "mv13",  "mv14",  "mv15",		   \
  "wcgr0", "wcgr1", "wcgr2", "wcgr3",		   \
  "wr0",   "wr1",   "wr2",   "wr3",		   \
  "wr4",   "wr5",   "wr6",   "wr7",		   \
  "wr8",   "wr9",   "wr10",  "wr11",		   \
  "wr12",  "wr13",  "wr14",  "wr15",		   \
  "s0",  "s1",  "s2",  "s3",  "s4",  "s5",  "s6",  "s7",  \
  "s8",  "s9",  "s10", "s11", "s12", "s13", "s14", "s15", \
  "s16", "s17", "s18", "s19", "s20", "s21", "s22", "s23", \
  "s24", "s25", "s26", "s27", "s28", "s29", "s30", "s31", \
  "vfpcc"					   \
}
#endif

#ifndef ADDITIONAL_REGISTER_NAMES
#define ADDITIONAL_REGISTER_NAMES		\
{						\
  {"a1", 0},					\
  {"a2", 1},					\
  {"a3", 2},					\
  {"a4", 3},					\
  {"v1", 4},					\
  {"v2", 5},					\
  {"v3", 6},					\
  {"v4", 7},					\
  {"v5", 8},					\
  {"v6", 9},					\
  {"rfp", 9}, /* Gcc used to call it this */	\
  {"sb", 9},					\
  {"v7", 10},					\
  {"sl", 10},	/* sl */			\
  {"r12", 12},	/* ip */			\
  {"r13", 13},	/* sp */			\
  {"r14", 14},	/* lr */			\
  {"r15", 15},	/* pc */			\
  {"mvf0", 27},					\
  {"mvf1", 28},					\
  {"mvf2", 29},					\
  {"mvf3", 30},					\
  {"mvf4", 31},					\
  {"mvf5", 32},					\
  {"mvf6", 33},					\
  {"mvf7", 34},					\
  {"mvf8", 35},					\
  {"mvf9", 36},					\
  {"mvf10", 37},				\
  {"mvf11", 38},				\
  {"mvf12", 39},				\
  {"mvf13", 40},				\
  {"mvf14", 41},				\
  {"mvf15", 42},				\
  {"mvd0", 27},					\
  {"mvd1", 28},					\
  {"mvd2", 29},					\
  {"mvd3", 30},					\
  {"mvd4", 31},					\
  {"mvd5", 32},					\
  {"mvd6", 33},					\
  {"mvd7", 34},					\
  {"mvd8", 35},					\
  {"mvd9", 36},					\
  {"mvd10", 37},				\
  {"mvd11", 38},				\
  {"mvd12", 39},				\
  {"mvd13", 40},				\
  {"mvd14", 41},				\
  {"mvd15", 42},				\
  {"mvfx0", 27},				\
  {"mvfx1", 28},				\
  {"mvfx2", 29},				\
  {"mvfx3", 30},				\
  {"mvfx4", 31},				\
  {"mvfx5", 32},				\
  {"mvfx6", 33},				\
  {"mvfx7", 34},				\
  {"mvfx8", 35},				\
  {"mvfx9", 36},				\
  {"mvfx10", 37},				\
  {"mvfx11", 38},				\
  {"mvfx12", 39},				\
  {"mvfx13", 40},				\
  {"mvfx14", 41},				\
  {"mvfx15", 42},				\
  {"mvdx0", 27},				\
  {"mvdx1", 28},				\
  {"mvdx2", 29},				\
  {"mvdx3", 30},				\
  {"mvdx4", 31},				\
  {"mvdx5", 32},				\
  {"mvdx6", 33},				\
  {"mvdx7", 34},				\
  {"mvdx8", 35},				\
  {"mvdx9", 36},				\
  {"mvdx10", 37},				\
  {"mvdx11", 38},				\
  {"mvdx12", 39},				\
  {"mvdx13", 40},				\
  {"mvdx14", 41},				\
  {"mvdx15", 42},				\
  {"d0", 63},					\
  {"d1", 65},					\
  {"d2", 67},					\
  {"d3", 69},					\
  {"d4", 71},					\
  {"d5", 73},					\
  {"d6", 75},					\
  {"d7", 77},					\
  {"d8", 79},					\
  {"d9", 81},					\
  {"d10", 83},					\
  {"d11", 85},					\
  {"d12", 87},					\
  {"d13", 89},					\
  {"d14", 91},					\
  {"d15", 93},					\
}
#endif

#define DBX_DEBUGGING_INFO 1

#ifndef ASM_COMMENT_START
#define ASM_COMMENT_START 	"@"
#endif

#undef  ASM_DECLARE_FUNCTION_SIZE
#define ASM_DECLARE_FUNCTION_SIZE(FILE, FNAME, DECL)		\
  do								\
    {								\
      ARM_DECLARE_FUNCTION_SIZE (FILE, FNAME, DECL);		\
    }								\
  while (0)

#define DARWIN_SUBARCH_SPEC "			\
 %{march=armv6k:armv6;				\
   march=armv5tej:armv5;			\
   march=xscale:xscale;				\
   march=armv4t:armv4t;				\
   mcpu=arm10tdmi:armv5;			\
   mcpu=arm1020t:armv5;				\
   mcpu=arm9e:armv5;				\
   mcpu=arm946e-s:armv5;			\
   mcpu=arm966e-s:armv5;			\
   mcpu=arm968e-s:armv5;			\
   mcpu=arm10e:armv5;				\
   mcpu=arm1020e:armv5;				\
   mcpu=arm1022e:armv5;				\
   mcpu=arm926ej-s:armv5;			\
   mcpu=arm1026ej-s:armv5;			\
   mcpu=xscale:xscale;				\
   mcpu=arm1136j-s:armv6;			\
   mcpu=arm1136jf-s:armv6;			\
   mcpu=arm1176jz-s:armv6;			\
   mcpu=arm1176jzf-s:armv6;			\
   :arm -force_cpusubtype_ALL}"

#define DARWIN_MINVERSION_SPEC "2.0"

/* Default cc1 option for specifying minimum version number.  */
#define DARWIN_CC1_MINVERSION_SPEC "-miphoneos-version-min=%(darwin_minversion)"

/* Default ld option for specifying minimum version number.  */
#define DARWIN_LD_MINVERSION_SPEC "-iphoneos_version_min %(darwin_minversion)"

/* Use iPhone OS version numbers by default.  */
#define DARWIN_DEFAULT_VERSION_TYPE DARWIN_VERSION_IPHONEOS

#define DARWIN_IPHONEOS_LIBGCC_SPEC "-lgcc_s.1 -lgcc"

#undef SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS			\
  DARWIN_EXTRA_SPECS				\
  { "darwin_arch", DARWIN_SUBARCH_SPEC },	\
  { "darwin_subarch", DARWIN_SUBARCH_SPEC },

/* This can go away once we can feature test the assembler correctly.  */
#define ASM_DEBUG_SPEC ""

#undef	SUBTARGET_SWITCHES
#define SUBTARGET_SWITCHES						\
  {"dynamic-no-pic",	MASK_MACHO_DYNAMIC_NO_PIC,			\
      N_("Generate code suitable for executables (NOT shared libs)")},	\
  {"no-dynamic-no-pic",	-MASK_MACHO_DYNAMIC_NO_PIC, ""},

#define SUBTARGET_OVERRIDE_OPTIONS					\
do {									\
  if (1)								\
  {									\
    if (!darwin_macosx_version_min && !darwin_iphoneos_version_min)	\
      darwin_iphoneos_version_min = "2.0";				\
    if (MACHO_DYNAMIC_NO_PIC_P)						\
      {									\
        if (flag_pic)							\
            warning ("-mdynamic-no-pic overrides -fpic or -fPIC");	\
        flag_pic = 0;							\
      }									\
    else if (flag_pic == 1)						\
      {									\
        /* Darwin doesn't support -fpic.  */				\
        warning ("-fpic is not supported; -fPIC assumed");		\
        flag_pic = 2;							\
      }									\
  }									\
} while(0)

/* We reserve r9 on darwin for thread local data.  */
#undef SUBTARGET_CONDITIONAL_REGISTER_USAGE
#define SUBTARGET_CONDITIONAL_REGISTER_USAGE			\
  if (1)							\
    {								\
      fixed_regs[9]     = 1;					\
      call_used_regs[9] = 1;					\
    }								\
  if (TARGET_THUMB)						\
    {								\
      fixed_regs[THUMB_HARD_FRAME_POINTER_REGNUM] = 1;		\
      call_used_regs[THUMB_HARD_FRAME_POINTER_REGNUM] = 1;	\
      global_regs[THUMB_HARD_FRAME_POINTER_REGNUM] = 1;		\
    }

#undef TARGET_MACHO
#define TARGET_MACHO 1

#undef DEFAULT_STRUCTURE_SIZE_BOUNDARY
#define DEFAULT_STRUCTURE_SIZE_BOUNDARY 8

#undef DOT_WORD
#define DOT_WORD ".long"

/* Output an element of a dispatch table.  */
#define ASM_OUTPUT_ADDR_VEC_ELT(STREAM, VALUE)  \
  asm_fprintf (STREAM, "\t" DOT_WORD "\t%LL%d\n", VALUE)

#define ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED)			\
  do {									\
    unsigned HOST_WIDE_INT _new_size = SIZE;				\
    fputs (".comm ", (FILE));						\
    assemble_name ((FILE), (NAME));					\
    if (_new_size == 0) _new_size = 1;					\
    fprintf ((FILE), ","HOST_WIDE_INT_PRINT_UNSIGNED"\n", _new_size);	\
  } while (0)

#undef SUBTARGET_ASM_DECLARE_FUNCTION_NAME
#define SUBTARGET_ASM_DECLARE_FUNCTION_NAME ARM_DECLARE_FUNCTION_NAME

/* We default to VFP */
#define FPUTYPE_DEFAULT FPUTYPE_VFP

#undef TARGET_DEFAULT_FLOAT_ABI
#define TARGET_DEFAULT_FLOAT_ABI (arm_arch6 ? ARM_FLOAT_ABI_SOFTFP : ARM_FLOAT_ABI_SOFT)

/* Define this to change the optimizations performed by default.  */
#define OPTIMIZATION_OPTIONS(LEVEL, SIZE) \
  optimization_options ((LEVEL), (SIZE))

#undef REGISTER_TARGET_PRAGMAS
#define REGISTER_TARGET_PRAGMAS DARWIN_REGISTER_TARGET_PRAGMAS

#undef DEFAULT_SIGNED_CHAR
#define DEFAULT_SIGNED_CHAR (1)

#undef GLOBAL_ASM_OP
#define GLOBAL_ASM_OP "\t.globl "

#define TARGET_64BIT 0

#define C_COMMON_OVERRIDE_OPTIONS do {          \
  SUBTARGET_C_COMMON_OVERRIDE_OPTIONS;          \
  } while (0)

/* The xxxvfp comparisons return 0 or 1. */
#define FLOAT_LIB_COMPARE_RETURNS_BOOL(MODE, OPERATOR)	\
  ((TARGET_MACHO && TARGET_THUMB && !TARGET_SOFT_FLOAT	\
    && (flag_pic || MACHO_DYNAMIC_NO_PIC_P)		\
    && (MODE == SFmode || MODE == DFmode)) ? 1 : 0)

/* Adjust inlining parameters.  */
#undef SUBTARGET_OPTIMIZATION_OPTIONS
#define SUBTARGET_OPTIMIZATION_OPTIONS			\
  if (optimize_size)					\
    {							\
      set_param_value ("max-inline-insns-single", 9);	\
      set_param_value ("max-inline-insns-auto", 4);	\
      set_param_value ("inline-call-cost", 2);		\
    }

#undef ARM_DECLARE_FUNCTION_SIZE
#define ARM_DECLARE_FUNCTION_SIZE(STREAM, NAME, DECL)	\
  if (!TARGET_LONG_CALLS || ! DECL_SECTION_NAME (DECL))	\
    arm_encode_call_attribute (DECL, SYMBOL_SHORT_CALL)

/* Remove limit for -Os */
#undef MAX_CONDITIONAL_EXECUTE
#define MAX_CONDITIONAL_EXECUTE	(optimize_size ? INT_MAX : (BRANCH_COST + 1))

/* APPLE LOCAL KEXT */
#define TARGET_SUPPORTS_KEXTABI1 1

#define OBJC_TARGET_FLAG_OBJC_ABI		\
  do { 						\
    if (flag_objc_abi == -1)			\
      flag_objc_abi = 2;			\
    if (flag_objc_legacy_dispatch == -1)	\
      flag_objc_legacy_dispatch = 1;		\
  } while (0)

