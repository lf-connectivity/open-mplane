
<hr>
@subsection design_overview_doc_sec3_5 services repository - Product Services Implementations
<hr>
@par
The services repository contains software modules that implement the general functionality of a
product into a collection of inter-related services. These services provide
logically grouped functionality which closely matches the functionality of its underlying hardware. For
example a TxService software module would be associated with the control of one or more
radio TxPaths, as defined by <b>hardware/vhi</b>, but the services data and functionality is exposed
by implementing the interface defined in the virtual services interface or <b>vsi</b>.

@par
Services differ from the modules of the product hardware implementation in that they are contextual
resources that have both time and state relationships and do not simply represent
a flat data resource with a pure functional interface. Services are tasks that
run at repeatable intervals or in response to events received from another
service.


@subsubsection design_overview_doc_sec3_5_1 vsi sub-directory - Virtual Services Interface
@par
The vsi sub-directory or <b>virtual services interface</b> provides a collection of inter-related C++ abstract classes,
containing only pure virtual methods, that collectively define an interface to
a products software services. Some services can be considered comman and might exist in some
form on all product implementations, for example all radios are likely to have Tx and
Rx power control, power measurement, temperature handling, alarms and faults etc.
The aim of the interface is to allow for the provision of a common product services implementation
that may be changed or enhanced by a product specific implementation. Higher level
application software that use the interface are effectively unaware of the detail of
the underlying service implementation, they are protected from the details through
the generic interface.

@par
<b>Constraints</b>
@par
All code in the vsi sub-directory <b>must not</b> contain any implementation. All
classes should be abstract, their methods must be pure virtual and must
not contain any data.

@par
<b>Detailed Design</b>
@par
More details of the <b>virtual services interface</b> design can be found here:
<A HREF="./services-vsi/index.html" target="_blank"><i><b>vsi</i> - Virtual Services Interface Design Document</b></A>
<BR>


@subsubsection design_overview_doc_sec3_5_2 common sub-directory - Common Product Services
@par

@par
The common radio services seek to provide application specific handling of
complex product resources such as receive and transmit path gain control, power
report processing and fault handling. The common implementation of these services
are found in the <b><i>common</i></b> sub-directory.

@par
Product specific services, such as those used to interface to a non-standard radio feature
in a directory that reflects the hardware name,  i.e. <b><i>ETNA, LAURO</i></b> etc..

@par
<b>Constraints</b>
@par
Services MUST only access its hardware through the virtual hardware interface implementation
provided by its corresponding hardware product module and NEVER directly access hardware.

@par
<b>Detailed Design</b>
@par
More details of the <b>common radio services implementation</b> can be found here:
<A HREF="./services-common/index.html" target="_blank"><b><i>services/common</i> - Common Services Implementation Design Document</b></A>

@subsubsection design_overview_doc_sec3_5_3 Product-Specific Services
@par
Certain services implementations are specific to particular products and therefore require to be handled separately from
any common services.


<!-- {{@APPLICATION_ATG{ -->


They are detailed in the following sub-sections.

@subsubsection design_overview_doc_sec3_5_3_1 ATG sub-directory - ATG Services
@par

@par
The ATG RRH provides new and extra functionality in addition to the common radio services handling of
transmit path gain control. The implementation of these services
are found in the <b><i>ATG</i></b> sub-directory.

@par
<b>Detailed Design</b>
@par
More details of the <b>ATG Service implementation</b> can be found here:
<A HREF="./services-ATG/index.html" target="_blank"><b><i>services/ATG</i> - ATG Services Implementation Design Document</b></A>

<!-- }}@APPLICATION_ATG} -->


