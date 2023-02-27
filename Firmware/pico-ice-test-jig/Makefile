ICEPACK = icepack
NEXTPNR = nextpnr-ice40 --randomize-seed --up5k --package sg48
YOSYS = yosys
BIN2UF2 = bin2uf2
DFU-UTIL = dfu-util -R -a 0
DFU-SUFFIX = dfu-suffix -v $(VID) -p $(PID)

PROJECT = pico_ice_bitstream
RTL = top.v

all: $(PROJECT).bit

clean:
	rm -f *.log *.json *.asc *.bit *.dfu *.uf2
	rm -rf verilator

flash: pico_ice_bitstream.dfu
	$(DFU-UTIL) -D $(PROJECT).dfu

pico_ice_bitstream.json: ${RTL}

.SUFFIXES: .sv .elf .vcd .json .asc .bit .dfu .uf2

$(PROJECT).json: $(RTL)
	${YOSYS} -p "read_verilog -sv ${RTL}; synth_ice40 -top top -json $@" >$*.yosys.log

.json.asc:
	${NEXTPNR} -q -l $*.nextpnr.log --pcf pico_ice.pcf --top top --json $< --asc $@

.asc.bit:
	${ICEPACK} $< $@

.bit.uf2:
	$(BIN2UF2) -o $@ 0x00000000 $<

.bit.dfu:
	cp $< $@
	$(DFU-SUFFIX) -a $@
