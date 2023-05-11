
<hr>
@subsection design_overview_doc_sec3_15 applications repository - Top level Product Application Definition
<hr>
@par
This repository is used to create the final executable applications and packages that once
down loaded to the appropriate hardware create the product application and control the hardware.
Each sub-directory of the applications repository has a sub-directory whose name reflects a
customer and a product application.

@par
A directory name ETNA-ALU-RRH would indicate the end customer as Alcatel-Lucent (ALU), the product type
would be a remote radio head (RRH) and that the hardware platform for the implementation is ETNA.
The build system pulls together the appropriate collections of hardware and services implementation
in order to create the application package.

@par
<b>Detailed Design</b>
@par
All applications are created and run through the implementation of the virtual appication intervface as defined here:
<A HREF="./applications-common/index.html" target="_blank"><b><i>applications/common</i>  - Common Application Interface Design Document</b></A>

@par
To accelerate base application implementation, there is a common applications library (used by all applications) can be found here:
<A HREF="./applications-common-Application/index.html" target="_blank"><b><i>applications/common/Application</i>  - Common Application Implementation Design Document</b></A>

@par
Product specific application for the <b>@{APPLICATION} product design implementation</b> can be found here:
<A HREF="./applications-@{CUSTOMER}-@{APPLICATION}/index.html" target="_blank"><b><i>applications/@{CUSTOMER}-@{APPLICATION}</i>  - @{APPLICATION} Design Document</b></A>

