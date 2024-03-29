# Process this file with autoconf to create configure.

AC_PREREQ([2.65])

# ====================
# Version informations
# ====================
m4_define([libwpd_version_major],[0])
m4_define([libwpd_version_minor],[10])
m4_define([libwpd_version_micro],[4])
m4_define([libwpd_version],[libwpd_version_major.libwpd_version_minor.libwpd_version_micro])

# =============
# Automake init
# =============
AC_INIT([libwpd],[libwpd_version])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([1.11 foreign dist-xz dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_LANG([C++])

# ===========================
# Find required base packages
# ===========================
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT([win32-dll disable-static pic-only])
AC_CANONICAL_HOST

# =================================
# Libtool/Version Makefile settings
# =================================
AC_SUBST(WPD_MAJOR_VERSION, [libwpd_version_major])
AC_SUBST(WPD_MINOR_VERSION, [libwpd_version_minor])
AC_SUBST(WPD_MICRO_VERSION, [libwpd_version_micro])
AC_SUBST(WPD_VERSION, [libwpd_version])
# AC_SUBST(LT_RELEASE, [libwpd_version_major.libwpd_version_minor])
LT_CURRENT=`expr 100 '*' libwpd_version_major + libwpd_version_minor`
# For 1.0.0 comment the first line and uncomment the second
LT_AGE=0
# LT_AGE=libwpd_version_minor
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION, [libwpd_version_micro])
AC_SUBST(LT_AGE)

AX_CXX_COMPILE_STDCXX_11
AX_GCC_FUNC_ATTRIBUTE([format])

# ==========================
# Platform check for windows
# ==========================
AC_MSG_CHECKING([for native Win32])
AS_CASE([$host],
	[*-*-mingw*], [
		native_win32=yes
		LIBWPD_WIN32_RESOURCE=libwpd-win32res.lo
		WPD2HTML_WIN32_RESOURCE=wpd2html-win32res.lo
		WPD2TEXT_WIN32_RESOURCE=wpd2text-win32res.lo
		WPD2RAW_WIN32_RESOURCE=wpd2raw-win32res.lo
	], [
		native_win32=no
		LIBWPD_WIN32_RESOURCE=
		WPD2HTML_WIN32_RESOURCE=
		WPD2TEXT_WIN32_RESOURCE=
		WPD2RAW_WIN32_RESOURCE=
	]
)
AC_MSG_RESULT([$native_win32])
AM_CONDITIONAL(OS_WIN32, [test "x$native_win32" = "xyes"])
AC_SUBST(LIBWPD_WIN32_RESOURCE)
AC_SUBST(WPD2HTML_WIN32_RESOURCE)
AC_SUBST(WPD2TEXT_WIN32_RESOURCE)
AC_SUBST(WPD2RAW_WIN32_RESOURCE)

AC_MSG_CHECKING([for Win32 platform in general])
AS_CASE([$host],
	[*-*-mingw*|*-*-cygwin*], [platform_win32=yes],
	[platform_win32=no]
)
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL([PLATFORM_WIN32], [test "x$platform_win32" = "xyes"])

AS_IF([test "x$platform_win32" = "xyes"],
    [],
    [
        AC_MSG_CHECKING([for -fvisibility=hidden compiler flag])
        saved_CXXFLAGS="$CXXFLAGS"
        CXXFLAGS="$CXXFLAGS -fvisibility=hidden"
        AC_TRY_COMPILE([], [], [have_visibility=yes], [have_visibility=no])
        AC_MSG_RESULT([$have_visibility])
        CXXFLAGS="$saved_CXXFLAGS"
        AX_GCC_FUNC_ATTRIBUTE([visibility])
    ]
)
AM_CONDITIONAL([HAVE_VISIBILITY], [
    test x"$have_visibility" = xyes && test x"$ax_cv_have_func_attribute_visibility" = xyes])

# =========================
# Platform check for darwin
# =========================
AC_MSG_CHECKING([for Darwin (Mac OS X) platform])
AS_CASE([$host],
	[*-*-darwin*], [platform_darwin=yes],
	[platform_darwin=no]
)
AC_MSG_RESULT([$platform_darwin])
AM_CONDITIONAL(PLATFORM_DARWIN, [test "x$platform_darwin" = "xyes"])

# ================
# Check for cflags
# ================
AC_ARG_ENABLE([werror],
	[AS_HELP_STRING([--enable-werror], [Treat all warnings as errors, usefull for development])],
	[enable_werror="$enableval"],
	[enable_werror=no]
)
AS_IF([test x"$enable_werror" != "xno"], [
	CFLAGS="$CFLAGS -Werror"
	CXXFLAGS="$CXXFLAGS -Werror"
])
AC_ARG_ENABLE([weffc],
	[AS_HELP_STRING([--disable-weffc], [ Disable -Weffc++ warnings, usefull when using an old version of gcc or of boost])],
	[enable_weffc="$enableval"],
	[enable_weffc=yes]
)
AC_ARG_ENABLE([wparanoic],
	[AS_HELP_STRING([--enable-wparanoic], [Enable a lot of warnings...])],
	[enable_wparanoic="$enableval"],
	[enable_wparanoic=no]
)
# Courtesy of Glib: Ensure MSVC-compatible struct packing convention
# is used when compiling for Win32 with gcc.
AS_IF([test "x$native_win32" = "xyes"], [
	AC_CHECK_TOOL(WINDRES, windres)
	AS_IF([test x"$GCC" = xyes], [
		AC_MSG_CHECKING([how to get MSVC-compatible struct packing])
		AS_IF([test -z "$ac_cv_prog_CC"], [
			our_gcc="$CC"
		], [
			our_gcc="$ac_cv_prog_CC"
		])
		AS_IF([$our_gcc -v --help 2>/dev/null | grep ms-bitfields >/dev/null], [
			msnative_struct="-mms-bitfields"
			CFLAGS="$CFLAGS $msnative_struct"
			CXXFLAGS="$CXXFLAGS $msnative_struct"
			AC_MSG_RESULT([${msnative_struct}])
		], [
			AC_MSG_RESULT([no way])
			AC_MSG_WARN([produced libraries might be incompatible with MSVC-compiled code])
		])
	])
	CFLAGS="$CFLAGS -Wall -Wextra -pedantic"
	CXXFLAGS="$CXXFLAGS -Wall -Wextra -Wshadow -pedantic"
], [
	AS_IF([test x"$GCC" = xyes], [
		# Be tough with warnings and produce less careless code
		CFLAGS="$CFLAGS -Wall -Wextra -pedantic"
		CXXFLAGS="$CXXFLAGS -Wall -Wextra -pedantic -Wshadow -Wunused-variable"
		AS_IF([test x"$enable_weffc" != "xno"], [
			CXXFLAGS="$CXXFLAGS -Weffc++"
		])
		AS_IF([test x"$enable_wparanoic" != "xno"], [
			CXXFLAGS="$CXXFLAGS -Wcast-align -Wcast-qual -Wchar-subscripts"
			CXXFLAGS="$CXXFLAGS -Wcomment -Wconversion -Wdisabled-optimization"
			CXXFLAGS="$CXXFLAGS -Wfloat-equal -Wformat -Wformat=2"
			CXXFLAGS="$CXXFLAGS -Wformat-nonliteral -Wformat-security"
			CXXFLAGS="$CXXFLAGS -Wformat-y2k -Wimport -Winit-self -Winvalid-pch"
			CXXFLAGS="$CXXFLAGS -Wmissing-braces -Wmissing-field-initializers"
			CXXFLAGS="$CXXFLAGS -Wmissing-format-attribute -Wmissing-include-dirs"
			CXXFLAGS="$CXXFLAGS -Wmissing-noreturn -Wpacked -Wparentheses"
			CXXFLAGS="$CXXFLAGS -Wpointer-arith -Wredundant-decls -Wreturn-type"
			CXXFLAGS="$CXXFLAGS -Wsequence-point -Wsign-compare -Wstrict-aliasing"
			CXXFLAGS="$CXXFLAGS -Wstrict-aliasing=2 -Wswitch -Wswitch-default"
			CXXFLAGS="$CXXFLAGS -Wswitch-enum -Wtrigraphs -Wunknown-pragmas -Wunused"
			CXXFLAGS="$CXXFLAGS -Wunused-function -Wunused-label -Wunused-parameter"
			CXXFLAGS="$CXXFLAGS -Wunused-value -Wvariadic-macros"
			CXXFLAGS="$CXXFLAGS -Wvolatile-register-var -Wwrite-strings"
		])
	])
])

# ============
# Debug switch
# ============
AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug], [Turn on debugging])],
	[enable_debug="$enableval"],
	[enable_debug=no]
)
AS_IF([test "x$enable_debug" = "xyes"], [
	DEBUG_CXXFLAGS="-DDEBUG -g"
], [
	DEBUG_CXXFLAGS="-DNDEBUG"
])
AC_SUBST(DEBUG_CXXFLAGS)

# =============
# Documentation
# =============
AC_ARG_WITH(docs,
	[AS_HELP_STRING([--without-docs], [Do not build documentation])],
	[with_docs="$withval"],
	[AS_IF([test "x$native_win32" = "xyes"], [with_docs=no], [with_docs=yes])]
)
AS_IF([test "x$with_docs" != "xno"], [
	AC_PATH_PROG(DOXYGEN, [doxygen])
	AS_IF([test -z "$DOXYGEN"], [
		AC_MSG_WARN([*** Could not find doxygen in your PATH.])
		AC_MSG_WARN([*** The documentation will not be built.])
		build_docs=no
	], [build_docs=yes])
], [build_docs=no])
AM_CONDITIONAL([WITH_LIBWPD_DOCS], [test "x$build_docs" != "xno"])


# ===============
# Find librevenge
# ===============
PKG_CHECK_MODULES([REVENGE],[librevenge-0.0 >= 0.0.1])
AC_SUBST([REVENGE_CFLAGS])
AC_SUBST([REVENGE_LIBS])

# ==================
# Find boost headers
# ==================
saved_CPPFLAGS="${CPPFLAGS}"
CPPFLAGS="${BOOST_CFLAGS} ${CPPFLAGS}"
AC_CHECK_HEADERS([dnl
        boost/spirit/include/qi.hpp \
    ],
    [],
    [AC_MSG_ERROR([Required boost headers not found.])],
    []
)
CPPFLAGS="${saved_CPPFLAGS}"
AC_SUBST([BOOST_CFLAGS])

# =====
# Tools
# =====
AC_ARG_ENABLE([tools],
	[AS_HELP_STRING([--disable-tools], [Build conversion tools])],
	[enable_tools="$enableval"],
	[enable_tools=yes]
)
AM_CONDITIONAL(BUILD_TOOLS, [test "x$enable_tools" = "xyes"])

# =======
# Fuzzers
# =======
AC_ARG_ENABLE([fuzzers],
	[AS_HELP_STRING([--enable-fuzzers], [Build fuzzer(s)])],
	[enable_fuzzers="$enableval"],
	[enable_fuzzers=no]
)
AM_CONDITIONAL(BUILD_FUZZERS, [test "x$enable_fuzzers" = "xyes"])

AS_IF([test "x$enable_tools" = "xyes" -o "x$enable_fuzzers" = "xyes"], [
	PKG_CHECK_MODULES([REVENGE_GENERATORS],[librevenge-generators-0.0])
	PKG_CHECK_MODULES([REVENGE_STREAM],[librevenge-stream-0.0])
])
AC_SUBST([REVENGE_GENERATORS_CFLAGS])
AC_SUBST([REVENGE_GENERATORS_LIBS])
AC_SUBST([REVENGE_STREAM_CFLAGS])
AC_SUBST([REVENGE_STREAM_LIBS])

# =====================
# Prepare all .in files
# =====================
AC_CONFIG_FILES([
Makefile
src/Makefile
src/conv/Makefile
src/conv/html/Makefile
src/conv/html/wpd2html.rc
src/conv/raw/Makefile
src/conv/raw/wpd2raw.rc
src/conv/text/Makefile
src/conv/text/wpd2text.rc
src/fuzz/Makefile
src/lib/Makefile
src/lib/libwpd.rc
inc/Makefile
inc/libwpd/Makefile
docs/Makefile
docs/doxygen/Makefile
build/Makefile
build/win32/Makefile
libwpd-$WPD_MAJOR_VERSION.$WPD_MINOR_VERSION.pc:libwpd.pc.in
])
AC_OUTPUT

# ==============================================
# Display final informations about configuration
# ==============================================
AC_MSG_NOTICE([
==============================================================================
Build configuration:
	debug:           ${enable_debug}
	docs:            ${build_docs}
	fuzzers:         ${enable_fuzzers}
	tools:           ${enable_tools}
	werror:          ${enable_werror}
==============================================================================
])
