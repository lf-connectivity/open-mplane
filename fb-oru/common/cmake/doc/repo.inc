<hr>
@subsection design_overview_doc_sec3_1  common repository - Common Data and OS Services Classes
<hr>
@par
The modules of the common repository, provides generic wrapper classes and
templates with common implementation for data objects, threads and other
operating system type facilities such as IPC and application management.

@par
<b>Constraints</b>
@par
Any code in the common repository can have no hardware specific dependency and must
only reference the <b>reusable operating system</b> facilities it wraps. It must also
not have any application specific dependency and remain truly common to all product
applications and hardware.


@par
<b>Detailed Design</b>
@par
More details of the functionality provided as part of the <b>common</b> repository can be found here:
<A HREF="./common-doc/index.html" target="_blank"><b><i>common</i> - Common Data and Services Design Document</b></A>
<BR>

