
<hr>
@subsection design_overview_doc_sec3_4 hardware repository - Common and Radio Hardware Specific Implementations
<hr>
@par
The modules in the hardware repository must be the only application
code base that accesses the radio hardware. The software may access hardware either
directly or through <b>ros</b> radio operating system BSP functions.
The code must implement the virtual abstract interfaces defined by the virtual hardware
hardware interface or vhi.

@subsubsection design_overview_doc_sec3_4_1 vhi sub-directory - Virtual Hardware Interface
@par
The vhi sub-directory or <b>virtual hardware interface</b> is a collection of inter-related C++
abstract classes, containing only pure virtual methods that collectively define an interface to
a generic hardware implementation. The aim of the virtual hardware interface is to
create a common implementation that may be altered or extended by a specific product
implementation. Higher level services and application software that use the interface
are effectively unaware of the details of the underlying hardware implementation as it
is protected from those details through its generic interface.

@par
<b>Constraints</b>
@par
All code in the vhi <b>should not</b> contain any implementation. All classes should be abstract
with all methods defined as pure virtual and must not contain any data.

@par
<b>Detailed Design</b>
@par
More details of the <b>virtual radio hardware</b> interface design can be found here:
<A HREF="./hardware-vhi/index.html" target="_blank"><b><i>vhi</i> - Virtual Hardware Interface Design Document</b></A>
<BR>

@subsubsection design_overview_doc_sec3_4_2 common sub-directory - Common Hardware Implementation
@par

@par
It is the intention of the common sub-directory to implement all common hardware functionality.
Any common class implementation can easily be extended by a product specific hardware
implementation. The common implementation can be found in the <b><i>common</i></b> directory.

@par
All product specific implementations of the virtual hardware interface can be found in
corresponding named product directories, i.e. <b><i>ETNA, ECB, E6G</i></b> etc.


@par
<b>Constraints</b>
@par
The radio hardware implementation must have no dependency on the Services or Applications
layers above it. Only vhi, ros and common/inc can be referenced by the hardware design.

@par
<b>Detailed Design</b>
@par
More details of the <b>common hardware implementation</b> can be found here:
<A HREF="./hardware-common/index.html" target="_blank"><b><i>hardware/common</i> - Common Hardware Implementation Design Document</b></A>


@subsubsection design_overview_doc_sec3_4_44 hardware specific sub-directories - Hardware/Product Specific Implementation
@par
The hard repository contains a collection of hardware and hardware-product specific implementations.
Those that are simply hardware specific have a simple mnemonic, e.g. ETNA. Those that are hardware and product
specific use a combination of the hardware mnemonic and the product mnemonic separated by an underscore e.g. ETNA_FTU.

@par
<b>Constraints</b>
@par
The radio specific hardware implementation must have no dependency on the Services or Applications
layers above it. Only vhi, ros, hardware/common and common/inc can be referenced by the hardware design.

@par
<b>Detailed Design</b>
@par
The following links are provided to the currently implemented hardware/product(s) designs supported by the
Software Platform.

@par
More details of the <b>@{BOARD} hardware implementation</b> can be found here:
<A HREF="./hardware-@{BOARD}/index.html" target="_blank"><b><i>hardware/@{BOARD}</i> - @{BOARD} board specific Hardware Implementation Design Document</b></A>

