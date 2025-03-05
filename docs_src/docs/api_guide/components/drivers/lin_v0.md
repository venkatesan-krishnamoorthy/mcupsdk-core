# LIN {#DRIVERS_LIN_PAGE}

[TOC]

The LIN module is compliant to the LIN2.1 standard in the LIN Specification
Package. This standard is based on the UART serial protocol. The protocol
involves a single commander and one or more responder nodes with a message
identification for multicast transmission between any network nodes.

SDK has support for both High Level Driver(HLD) and Low Level driver(LLD).
LLD is designed to be independent of other modules and the cross module
dependencies are to be taken care of in application. HLD is a heavily abstracted
driver which uses the LLD driver underneath. It uses the DPL layer in SDK to
fill the LLD dependencies. It has the advantage of ease of use and less
lines of code in application. Applications which find the SDK DPL layer
incompatible should use the LLD driver and customize based on requirement.
Others can go ahead with HLD.

- \subpage DRIVERS_LIN_V0_HLD_PAGE
- \subpage DRIVERS_LIN_V0_LLD_PAGE