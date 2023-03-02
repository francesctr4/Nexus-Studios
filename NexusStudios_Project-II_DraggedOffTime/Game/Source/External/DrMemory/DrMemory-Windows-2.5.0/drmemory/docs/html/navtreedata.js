/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Dr. Memory", "index.html", [
    [ "Home", "index.html", [
      [ "Downloading Dr. Memory", "index.html#autotoc_md0", null ],
      [ "Dr. Memory Performance", "index.html#autotoc_md1", null ],
      [ "Documentation", "index.html#autotoc_md2", null ],
      [ "System Call Tracer for Windows", "index.html#autotoc_md3", null ],
      [ "Fuzz Testing Infrastructure", "index.html#autotoc_md4", null ],
      [ "Discussion List", "index.html#autotoc_md5", null ],
      [ "Issue Tracker", "index.html#autotoc_md6", null ],
      [ "Contributing to Dr. Memory", "index.html#autotoc_md7", null ]
    ] ],
    [ "Download", "page_download.html", [
      [ "Latest Build", "page_download.html#sec_latest_build", null ],
      [ "Official Releases", "page_download.html#autotoc_md8", null ],
      [ "Tutorials and talks", "page_download.html#autotoc_md9", null ]
    ] ],
    [ "Installing Dr. Memory", "page_install.html", "page_install" ],
    [ "Preparing Your Application", "page_prep.html", [
      [ "For All Platforms", "page_prep.html#sec_prep_general", [
        [ "Debug Information", "page_prep.html#sec_prep_debuginfo", null ],
        [ "Callstack Quality", "page_prep.html#sec_prep_callstacks", null ]
      ] ],
      [ "Linux", "page_prep.html#sec_prep_linux", null ],
      [ "Mac", "page_prep.html#sec_prep_mac", null ],
      [ "Windows Visual Studio", "page_prep.html#sec_prep_windows", [
        [ "C Library Interactions", "page_prep.html#sec_prep_win_libc", null ],
        [ "Disable Runtime Checks", "page_prep.html#sec_prep_win_rtc", null ],
        [ "Parameter Summary", "page_prep.html#sec_prep_win_sum", null ]
      ] ],
      [ "Windows MinGW", "page_prep.html#sec_prep_mingw", null ],
      [ "Windows Cygwin: Not Supported", "page_prep.html#sec_prep_cygwin", null ],
      [ "Android", "page_prep.html#sec_prep_android", null ]
    ] ],
    [ "Running Dr. Memory", "page_running.html", [
      [ "Dr. Memory as a Visual Studio Tool", "page_running.html#sec_vstudio", null ],
      [ "Invoking Dr. Memory from the Command Line", "page_running.html#sec_invocation", null ],
      [ "Examining the Results", "page_running.html#sec_results", [
        [ "Application Versus System Library Errors", "page_running.html#sec_potential_errors", null ],
        [ "Eliminating Uninitialized Read Checks By Library", "page_running.html#sec_no_uninit_checks", null ]
      ] ],
      [ "Controlling Child Processes", "page_running.html#sec_children", null ],
      [ "Applications That Do Not Exit", "page_running.html#sec_daemon", null ],
      [ "Tuning for Performance", "page_running.html#sec_perf", null ]
    ] ],
    [ "Error Types Reported by Dr. Memory", "page_types.html", "page_types" ],
    [ "Error Reports", "page_reports.html", "page_reports" ],
    [ "Light Mode", "page_light.html", null ],
    [ "Chinese Quickstart Instructions", "page_chinese.html", null ],
    [ "Fuzz Testing Mode", "page_fuzzer.html", [
      [ "Fuzzer Target", "page_fuzzer.html#sec_fuzzer_target", null ],
      [ "C++ Targets", "page_fuzzer.html#sec_cpp_targets", null ],
      [ "Calling Conventions", "page_fuzzer.html#sec_calling_conventions", null ],
      [ "Mutator", "page_fuzzer.html#sec_mutator", null ],
      [ "Dumping and Loading Fuzz Input Data", "page_fuzzer.html#sec_dump_load", null ],
      [ "Corpus-Based Fuzzing", "page_fuzzer.html#sec_corpus", null ]
    ] ],
    [ "Code Coverage", "page_coverage.html", [
      [ "Enabling Coverage Information", "page_coverage.html#sec_enable", null ],
      [ "Post Processing", "page_coverage.html#sec_postproc", null ]
    ] ],
    [ "Additional Tools", "page_tools.html", "page_tools" ],
    [ "Obtaining Help and Reporting Bugs", "page_help.html", [
      [ "Discussion Email List", "page_help.html#autotoc_md10", null ],
      [ "Issue Tracker", "page_help.html#autotoc_md11", null ],
      [ "Debugging Dr. Memory", "page_help.html#sec_debugging", [
        [ "General Tips", "page_help.html#autotoc_md12", null ],
        [ "Narrowing Down the Source of the Problem", "page_help.html#sec_narrow", null ],
        [ "Gathering Additional Data", "page_help.html#autotoc_md13", null ],
        [ "Windows", "page_help.html#autotoc_md14", null ],
        [ "Private Symbols", "page_help.html#autotoc_md15", null ],
        [ "DMP files", "page_help.html#autotoc_md16", null ],
        [ "Application Callstack", "page_help.html#autotoc_md17", null ]
      ] ]
    ] ],
    [ "Dr. Memory Runtime Option Reference", "page_options.html", null ],
    [ "Release Notes for Version 2.5.0", "page_release_notes.html", [
      [ "Distribution Contents", "page_release_notes.html#sec_package", null ],
      [ "Changes Since Prior Releases", "page_release_notes.html#sec_changes", null ],
      [ "Limitations", "page_release_notes.html#sec_limits", [
        [ "Interoperability", "page_release_notes.html#sec_interop", null ]
      ] ]
    ] ],
    [ "Dr. Memory Framework", "page_drmf.html", "page_drmf" ],
    [ "License for Dr. Memory", "page_license.html", null ],
    [ "Developer Documentation", "page_developers.html", "page_developers" ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "DRMF Modules", "modules.html", "modules" ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", null ],
        [ "Variables", "functions_vars.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "Globals", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ],
    [ "Dr. Memory Home Page", "^http://www.drmemory.org", null ]
  ] ]
];

var NAVTREEINDEX =
[
"annotated.html",
"page_build.html#autotoc_md37",
"umbra_8h.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';