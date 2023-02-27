ICEPACK = icepack
ICEPROG = iceprog
NEXTPNR = nextpnr-ice40 --randomize-seed --up5k --package sg48
YOSYS = yosys
BIN2UF2 = bin2uf2

RTL = top.v

all: pico_ice_bitstream.bit

clean:
	rm -f *.log *.json *.asc *.bit *.dfu *.uf2 *.dot *.pdf *.vcd *.elf
	rm -rf verilator

flash: pico_ice_bitstream.bit
	${ICEPROG} -d i:0x0403:0x6014:0 ice40.bit

pico_ice_bitstream.json: ${RTL}

.SUFFIXES: .sv .elf .vcd .json .asc .bit .dfu .uf2

.v.json:
	${YOSYS} -p "read_verilog -sv $< ${RTL}; synth_ice40 -top $* -json $@" >$*.yosys.log

.json.asc:
	${NEXTPNR} -q -l $*.nextpnr.log --pcf ice40.pcf --json $< --asc $@

.asc.bit:
	${ICEPACK} $< $@

.bit.uf2:
	$(BIN2UF2) -o $@ 0x00000000 $<

.bit.dfu:
	cp $< $@
	dfu-suffix -v 1209 -p 70b1 -a $@
