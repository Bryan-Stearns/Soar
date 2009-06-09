@echo off

call "%VS80COMNTOOLS%\vsvars32.bat"

call %ANT_HOME%\bin\ant clean

devenv /rebuild "Distribution SCU" SML.sln
if not errorlevel 0 goto fail

devenv /build Release Tools\TestCSharpSML\TestCSharpSML.sln
if not errorlevel 0 goto fail
exit 0

:fail
exit 1