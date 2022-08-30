WORKDIR = work

LIBS = ../..
RTL = ../src
TB = ../tb

SIM_SRCS = $(TB)/tb_$(TOP).sv

CDC_UTILS = $(LIBS)/cdc_utils/rtl/verilog
VLOG_TB_UTILS = $(LIBS)/vlog_tb_utils

SRCH_PATH = -y $(TB) -y $(RTL) -y $(CDC_UTILS) -y $(VLOG_TB_UTILS)

VLOG_OPTS = -lint -pedanticerrors -fsmverbose w +libext+.v +libext+.sv $(SRCH_PATH) +incdir+$(TB) +incdir+$(RTL)
VSIM_OPTS = -warning vsim-3009 -t ps

.PHONY: compile sim lib clean

compile: $(WORKDIR) $(SIM_SRCS)
	vlog $(VLOG_OPTS) $(SIM_SRCS)

sim:
	vsim -c $(VSIM_OPTS) -do "run -all; quit" work.tb_$(TOP) -L iCE40UP

sim_gui:
	vsim -gui $(VSIM_OPTS) work.tb_$(TOP) -L iCE40UP

$(WORKDIR):
	vlib work

clean:
	rm -r transcript $(WORKDIR)