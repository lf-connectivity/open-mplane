
<hr>
@subsection design_overview_doc_sec_tif TIF repository - Test Interface Framework
<hr>
@par
The test interface framework provides a mechanism for defining the command interface with the application objects. This
interface can then be used to auto-generate code in multiple programming languages (for example C++, Java etc) that can
then be used in applications that access the radio hardware internals for test purposes.

@par
The developer adds his own code to the auto-generated framework which actually performs the access to the radio classes.

@par
<b>Constraints</b>
@par
The test interface descriptions must be defined in properly formatted XML (see
<A HREF="./tif-bin-utils-gentool/index.html" target="_blank"><b>Generator Tool Design Document</b></A> for full details).

@par
The user code added to the test framework should generally access the products hardware and services
using the virtual interface. Only product specific test interface requirements should access any
product specific implementation but this should be avoided where possible.

@par
<b>Detailed Design</b>
@par
More details of the <b>RTI implementation</b> can be found here:
<A HREF="./tif-doc/index.html" target="_blank"><b>Radio Test Interface Design Document</b></A>

@par
Details of the TIF directory structure, test helpers and test thandlers can be found here:
<A HREF="./tif-helper/index.html" target="_blank"><b>Test Helpers</b></A>

@par
A detailed description of the <b>TIF Generator Tool</b> can be found here:
<A HREF="./tif-bin-utils-gentool/index.html" target="_blank"><b>Generator Tool Design Document</b></A>

