# Learning FPGA Design

A large number of resources exists for learning FPGA design.

Some of them have been collected and aggregated on this page.

An online class was held by tinyVision.ai, and is available freely:

- [Hands-on-FPGA-class](https://github.com/tinyvision-ai-inc/Hands-on-FPGA-class/)

## Video format

- [Digi-Key Intro to FPGA](https://www.youtube.com/watch?v=lLg1AgA2Xoo)
  Starts with defining FPGA and covers HDLs, programming flow etc.
  New to FPGAs? Start here!

- [SystemVerilog in 5 minutes](https://www.bilibili.com/video/BV1Rr4y1z7Dv?p=1)
  Serie of concise and focused descriptions of the SystemVerilog language.

- [VLSI Chaps](https://youtube.com/channel/UCzvXC7WbnaWs5FZ5djO8cag)
  Discussion and explanation of ASICs, VLISI, but also SystemVerilog.

- [Digital to FPGA 101](https://youtu.be/FcFbFTbngrw)
  design a circuit in digital convert into verilog and run it on an ice40 FPGA (like Upduino_v3.1).

## Examples

- [icebreaker-verilog-examples](https://github.com/icebreaker-fpga/icebreaker-verilog-examples)
  A collection of examples using Makefiles for iCE40 boards.
  Can be used for the `pico-ice` with minor adaptations.

- [Xark's upduino-example](https://github.com/XarkLabs/upduino-example/tree/master)
  An example for how to use a Makefile for building a Verilog.
  Can be used for the `pico-ice` with minor adaptations.

- [tnt's ice40-playground](https://github.com/smunaut/ice40-playground/)
  S. Munaut's examples for the iCE40.

- [Librecores](https://www.librecores.org/)
  Index of open source cores (Verilog, VHDL...) projects. Good Verilog examples.

- [Upduino v2 icestorm examples](https://github.com/osresearch/up5k)
  large collection of very useful code, and a good overview. Upduino v2 only.

## General tutorials

- [Hobbyist's guide to FPGAs](https://hackaday.io/project/27550-the-hobbyists-guide-to-fpgas)
  FPGA tutorials, theory of design articles, hands-on labs targeted towards hobbyists.

- [VHDL Wiz](https://vhdlwhiz.com/)
  Community offering tutoring focused on VHDL.

- [Hardware as Code](https://www.hackster.io/sthibault/hardware-as-code-part-i-an-introduction-48bacb)
  A 5-part tutorial series using the UPduino as an example.

- [fpga 101 fpgas for beginners](https://www.nandland.com/articles/fpga-101-fpgas-for-beginners.html)
  Tutorial explaining concepts and practice with videos and articles.

- [Alchitry](https://alchitry.com/)
  Tutorial focused on the Artix 7 Alchitry boards.

- [Fomu Workshop](https://workshop.fomu.im/en/latest/)
  Workshop by FOMU the ICE40 FPGA that fits on an USB port.

- [Open FPGA Verilog Tutorial](https://github.com/Obijuan/open-fpga-verilog-tutorial/wiki)
  Excellent tutorial series for beginners and the more experienced.

- [Atadiat](https://atadiat.com/en/)
  Introduction about FPGA in both English and Arabic languages.

- [Verilog Tutorial for beginners](http://www.referencedesigner.com/tutorials/verilog/verilog_01.php)
  Verilog Tutorial Series.

- [CircuitVerse](https://learn.circuitverse.org/)
  Teaching verilog through an interactive book with challenges along the way.

- [ASIC-World Tutorial on Verilog](https://www.asic-world.com/verilog/veritut.html)
  Introduction to Verilog oriented toward ASICs and chip design.

- [FPGA-4-fun](https://www.fpga4fun.com/)
  Tutorials covering many practical problems with FPGAs.
  Lots of info and very well put together

- [Lattice IceCube2 Tutorial](https://hsel.co.uk/2018/05/21/lattice-ice40-ultra-plus-fpga-gnarly-grey-upduino-tutorial-1-the-basics/)
  A tutorial on Lattice's IceCube2 software/ide.
  IceCube2 is no longer recommended, replaced by Radiant

- [VLSI Chaps](https://youtube.com/channel/UCzvXC7WbnaWs5FZ5djO8cag)
  Discussion and explanation of ASICs, VLISI, but also SystemVerilog.

- [Digital to FPGA 101](https://youtu.be/FcFbFTbngrw)
  design a circuit in digital convert into verilog and run it on an ice40 FPGA (like Upduino_v3.1).

- [Verilog Tutorial](http://www.asic-world.com/verilog/veritut.html)
  Tutorial series on verilog with example code.
  all examples are synthesizable in icarus verilog simulator

- [CFU Playground](https://cfu-playground.readthedocs.io/en/latest/)
  The "Crash Course on Everything" is a good introduction

- [VHDL in an hour](https://www.jopdesign.com/teaching/VHDL.pdf)
  Fast paced but practical guide to VHDL.
  longest hour ever

- [First look at Prog. Logic](https://www.allaboutcircuits.com/technical-articles/a-microcontroller-enthusiast-first-look-at-programmable-logic/)
  Getting started w/FPGAs article series 1.

- [Sparkfun So you want to learn FPGAs](https://www.sparkfun.com/news/1203)
  Sparkfun article introducing to FPGAs.

- [ZIPCPU](http://zipcpu.com/)
  Articles by Gisselquist explaining design,verification, and more.

- [FPGA Workshop](https://github.com/ranzbak/fpga-workshop)
  Basic FPGA development for absolute beginners featuring the Upduino V2.

- [Upduino FPGA Tutorial](https://blog.idorobots.org/entries/upduino-fpga-tutorial.html)
  UPduino FPGA tutorial using APIO.

- [Installing the Icestorm Toolchain](https://www.youtube.com/watch?v=Bfhnu9XUzLs)
  Guide on getting comfortable with a Makefile-based development process for Icestorm/Yosys and Verilog.

- [Explanation of essential Verilog concepts](https://vanhunteradams.com/DE1/Lorenz/Verilog.html)
  Several pitfalls and myths debunked about the Verilog language, as part of an introduction.

## Specific topic

- [clock domain crossing](http://fpgacpu.ca/fpga/handshake.html)
  Sending data across modules of two different clock domain: clock domain crossing.

- [lowRISC Verilog Coding Style](https://github.com/lowRISC/style-guides/blob/master/VerilogCodingStyle.md)
  Set of rules for formatting and organizing Verilog code.
  Not difficult per-se, but problem encountered after initial discovery of Verilog is over

- [Interfacing FPGAs to an ADC’s Digital Data Output](https://www.analog.com/en/technical-articles/interfacing-fpgas-to-an-adcs-digital-data-output.html)
  Article from Analog Design exploring the topic of ADC/DAC <-> FPGA interface.

- [RISC-V on an ICE40 FPGA](https://pingu98.wordpress.com/2019/04/08/)
  A very detailed blog on implementing a RISC-V in the FPGA.

- [RISC-V on an iCE40 FPGA](https://github.com/BrunoLevy/learn-fpga)
  by the author of the relatively high-performance yet tiny RISC-V core FemtoRV.

## Wiki

- [VHDL Wiz Terminology](https://vhdlwhiz.com/terminology/)
  Glossary of many concepts.

- [VHDL Wiz Terminology](https://vhdlwhiz.com/terminology/)
  Glossary of many concepts.

- [Hamsterworks wiki](https://web.archive.org/web/20190115080828/http://hamsterworks.co.nz/mediawiki/index.php/Main_Page)
  Introduction to FPGAs focused on VHDL.
  The site is offline, but an archive of the content is still available.

- [VerilogGuide](https://verilogguide.readthedocs.io/)
  Wiki/Book for learning Verilog from the ground up.
  Uses Quartus and ModelSim-Altera Starter instead of the open source toolchain

- [Chipress](https://chipress.online/)
  Collection of explanations targetted at aspiring ASICs engineers.
  Many of the topics are related

- [ChipVerify](https://www.chipverify.com/)
  Wiki covering much of Verilog and SystemVerilog syntax.

- [FPGA key](https://www.fpgakey.com/)
  Community focused on providing resources to learn FPGAs.

## Simulators

- [EDA playground](https://www.edaplayground.com/home)
  Online IDE and simulator, quickest way to get started without a dev board.

- [Verilator](https://www.veripool.org/verilator/)
  Simulator for Verilog code.
  Convert the simulation to a C++ code library that exposes signals as C variables.

- [Icarus Verilog](http://iverilog.icarus.com/)
  Simulator for Verilog code.

- [Digital](https://github.com/hneemann/Digital/releases)
  digital logic circuit simulator based on logisim.
  Alternative: https://github.com/logisim-evolution/logisim-evolution

- [HDL Bits](https://hdlbits.01xz.net/wiki/Main_Page)
  Interactive (in browser) verilog syntax lessons.
  initially assumes no prior knowledge of HDLs but quickly ramps up difficulty

## Toolchains

- [oss-tabby-cad](https://github.com/YosysHQ/oss-cad-suite-build)
  A complete toolchain based on top of Yosys.

- [Yosys](https://yosyshq.net/yosys/)
  The central tool connecting the languages front-end and back-ends.

- [GHDL](https://ghdl.github.io/ghdl/)
  Simulator for VHDL code.

- [MixedSim](https://www.isotel.eu/mixedsim/)
  Tool building on top of ngspice for simulating circuits.

- [verilog to routing](https://verilogtorouting.org/)
  Open-Source toolchain alternative to YoSys.

- [open FPGA](https://github.com/azonenberg/openfpga)
  Older toolchain for CPLD.

- [FASM](https://fasm.readthedocs.io/en/latest/)
  Low-level format aiming to be a de-facto industry standard for FPGA toolchains.

## Courses

- [Hands-on FPGA class](https://github.com/tinyvision-ai-inc/Hands-on-FPGA-class/)
  A 8-week class was given by tinyVision.ai for getting started with FPGAs.

- [Intel FPGA Academy](https://fpgacademy.org/courses.html)
  Digital logic/FPGA courses by Intel.
  requires .edu email (contact intel for access without .edu email but response may vary)

- [fpga4fun FPGAs 1 - What are they?](https://www.fpga4fun.com/FPGAinfo1.html)
  Intro to FPGA lesson 1.
  Link is forr lesson 1 of intro to FPGA but the entire site is dedicated to learning FPGAs

- [WTFpga Workshop](https://github.com/icebreaker-fpga/wtfpga)
  Guided discovery of FPGA through the IceBreaker board.

- [IceBreaker Workshop](https://github.com/icebreaker-fpga/icebreaker-workshop)
  Course focused on getting started through the IceBreaker board.

- [Intro to Digital Logic Circuits](http://www.ece.tufts.edu/es/4/)
  University course by Steven Bell that assumes little/no prior knowledge of FPGAs.
  Features the Upduino v3 and "Digital Design and Computer Architecture arm edition"

- [Digital System Design (DSD) Spring 2009](http://www.ee.ic.ac.uk/pcheung/teaching/ee3_DSD/)
  Course introducing FPGAs to students.

- [MIT 6.205 Course](https://fpga.mit.edu/6205/F22)
  Requires log-in to access the whole content, but good introductory text.

## Other lists

- [F4PGA Link list](https://github.com/f4pga/ideas/issues/52)
  Another project aiming to collect links.

- [FPGA Design Elements](http://fpgacpu.ca/fpga/index.html)
  coding style and notes about various building blocks/design principles.
  Fantastic list of resources/code examples etc

- [HDL Simulators](https://en.wikipedia.org/wiki/List_of_HDL_simulators)
  Wikipedia list of simulators for HDLs.

- [sv-tests results](https://chipsalliance.github.io/sv-tests-results/)
  Table summarizing support for all SystemVerilog (and Verilog) features support in various tool..
  Useful to check compatibility of a toolchain

## Books

- [PLD World E-books](http://ebook.pldworld.com/_eBook/FPGA%EF%BC%8FHDL/-Eng-/)
  ebooks about all things HDL/FPGA/PLD etc.

- [Digital systems design using VHDL](https://www.pdfdrive.com/digital-systems-design-using-vhdl-d166870425.html)
  VHDL/digital design textbook by Charles H. Roth Jr & Lizy K. John.

- [FPGAs now what?](https://xess.com/static/media/appnotes/FpgasNowWhatBook.pdf)
  FPGA e-book that employs a hands on/learn by doing approach.

- [SystemVerilog RTL Modeling, Simulation, Verification](https://systemverilog.dev/)
  Online book on SystemVerilog using Cadence tools or EDA Playground.
  Work in progress

- [Digital Logic Pocket Data Book](https://www.ti.com/lit/ug/scyd013b/scyd013b.pdf)
  pinout/reference for TI Logic ICs (74xx series etc).
  Not exactly FPGA related, but useful for configuring the FPGA like common logic ICs

## Organizations

- [Build an FPGA from 7400 series ICs](http://blog.notdot.net/2012/10/Build-your-own-FPGA)
  DIY FPGA competition submission and source.
  https://github.com/arachnid/dfpga

- [Libre-SOC](https://libre-soc.org/)
  Open source high performance CPU/GPU/VPU on a chip.
  Focused on high performance open-sourced OpenPOWER architecture

- [F4PGA](https://f4pga.org/)
  Umbrella project based on Yosys for synthesis of code toward an HDL..
  Good place to first learn about toolchains, but some dead links

## Research papers

- [Sunburst design whitepapers](http://www.sunburst-design.com/papers/)
  reference papers on coding standard etc..
  Range of difficulties

## Games

- [NandGame](https://nandgame.com/)
  Browser based puzzle game about logic gates.
  serves as litmus test to determine familiarity with digital logic. Good for visual learners
