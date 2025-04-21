# EPWM Hr Updown {#EXAMPLES_DRIVERS_EPWM_HR_UPDOWN}

[TOC]

# Introduction

EPWM HR UpDown

This example modifies the MEP control registers to show edge displacement for high-resolution period with ePWM in Up-Down count mode due to the HRPWM control extension of the respective ePWM module.

\imageStyle{am263_epwm_hr_updown.PNG,width:60%}
 \image html am263_epwm_hr_updown.PNG "Block Diagram for EPWM HR UpDown example"

# External Connections

- Pin can be connected to high resolution oscilloscope (1 GHz) to observe the edge displacement.

## AM263X-CC or AM263PX-CC or AM261X-SOM
When using with TMDSHSECDOCK (HSEC180 controlCARD Baseboard Docking Station)
- Capture waveform on HSEC Pin 49, 51 for epwm0
- Capture waveform on HSEC Pin 53, 55 for epwm1
- Capture waveform on HSEC Pin 50, 52 for epwm2
- Capture waveform on HSEC Pin 54, 56 for epwm3
- Capture waveform on HSEC Pin 57, 59 for epwm4

## AM263X-LP or AM263PX-LP
When using AM263X-LP or AM263PX-LP
- Capture waveform on J2.11 / J6.59 for epwm0
- Capture waveform on J4.37 / J4.38 for epwm1
- Capture waveform on J4.39 / J4.40 for epwm2
- Capture waveform on J8.77 / J8.78 for epwm3
- Capture waveform on J8.75 / J8.76 for epwm9

## AM261X-LP
When using AM261X-LP
- Capture waveform on J7.69 / J7.63 for epwm1
- Capture waveform on J4.40 / J4.39 for epwm2
- Capture waveform on J4.38 / J4.37 for epwm3
- Capture waveform on J4.36 / J4.35 for epwm4
- Capture waveform on J8.78 / J8.77 for epwm6

# Supported Combinations {#EXAMPLES_DRIVERS_EPWM_HR_UPDOWN_COMBOS}

\cond SOC_AM263X || SOC_AM263PX || SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/epwm/epwm_hr_updown

\endcond



# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Establish connections as mentioned in External Connections section
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_EPWM_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
EPWM High Resolution Up Down Test Started ...
Please wait for 60 secs
EPWM High Resolution Up Down Test Passed!!
All tests have passed!!
\endcode

\imageStyle{am263_epwm_hr_updown_output.PNG,width:80%}
 \image html am263_epwm_hr_updown_output.PNG "EPWM HR UpDown waveform"
