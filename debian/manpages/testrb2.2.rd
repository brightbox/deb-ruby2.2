=begin

= NAME

testrb2.2 - Automatic runnter for Test::Unit of Ruby

= SYNOPSIS

testrb2.2 [options] [-- untouched arguments] test ...

= DESCRIPTION

testrb2.2 loads and runs unit-tests.  If test is directory name, testrb2.2
testrb2.2 traverses the directory.

= OPTIONS

: -r, --runner=RUNNER

  Use the given RUNNER.  (t[k], c[onsole], g[tk], f[ox])

: -a, --add=TORUN

  Add TORUN to the list of things to run;  can be a file or a directory.

: -p, --pattern=PATTERN

   Match files to collect against PATTERN.  (default pattern is
   /\Atest_.*\.rb\Z/.)

: -n, --name=NAME

  Runs tests matching NAME.  (patterns may be used.)

: -t, --testcase=TESTCASE

  Runs tests in TestCases matching TESTCASE.  (patterns may be used.)

: -v, --verbose=[LEVEL]

  Set the output level (default is verbose).  (p[rogress], n[ormal],
  v[erbose], s[ilent])

: --

  Stop processing options so that the remaining options will be passed to
  the test.

: -h, --help

  Display help.

= AUTHOR

This manpage was contributed by akira yamada <akira@debian.org>

=end
