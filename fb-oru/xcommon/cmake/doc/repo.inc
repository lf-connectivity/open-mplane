
<hr>
@subsection design_overview_doc_sec3_1b  xcommon repository - Cross-platform Common Classes
<hr>
@par
The modules of the xcommon repository provides generic wrapper classes and
templates with common implementation for cross-platform objects which can be used on Linux or Windows (or other OS)
since the code is all generic C++.

@par
<b>Constraints</b>
@par
Any code in the xcommon repository can have no dependency on *any* other repository and can contain no OS-specific calls.
The google tests, however, may contain conditional compilation to set up and test aspects specific to the OS the code
is being compiled for (e.g. file paths etc)

@par
<b>Detailed Design</b>
@par
More details of the functionality provided as part of the <b>xcommon</b> repository can be found here:
<A HREF="./xcommon-doc/index.html" target="_blank"><b><i>xcommon</i> - Cross-platform Common Design Document</b></A>
<BR>


