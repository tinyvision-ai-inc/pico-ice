legend = [
    ("Digital pin",  "gpio"),
    ("Pmod pin",   "analog"),
    ("Ground", "gnd"),
    ("Power", "pwr"),
]

# Pinlabels

def double(label, type, x):
    return (label, type, {"body": {"width": 166, "x": x}})

def row_2_2(name1, type1, name2, type2):
    return [
        (name1, type1, {"body": {"width": 166, "x": 6}}),
        (name2, type2, {"body": {"width": 166, "x": 20}})
    ]

def row_1_1_1_1(name1, type1, name2, type2, name3, type3, name4, type4):
    return [
        (name1, type1),
        (name2, type2),
        (name3, type3, {"body": {"x": 20}}),
        (name4, type4)
    ]

def row_2_1_1(name1, type1, name2, type2, name3, type3):
    return [
        (name1, type1, {"body": {"width": 166, "x": 6}}),
        (name2, type2, {"body": {"x": 20}}),
        (name3, type3)
    ]

def row_1_1_2(name1, type1, name2, type2, name3, type3, name4, type4):
    return [
        (name1, type1, {"body": {"x": 6}}),
        (name2, type2, {"body": {"x": 6}}),
        (name3, type3, {"body": {"width": 166, "x": 20}})
    ]

left_header = [
    row_2_2(
        "INNER ROW","", "OUTTER ROW","",
    ),
    row_1_1_1_1(
        "RP2040","", "iCE40","", "RP2040","", "iCE40",""
    ),
    row_1_1_1_1(
        "GP27~1","gpio", "CRESET","gpio", "","gpio", "IOB22a IO2","gpio"
    ),
    row_2_1_1(
        "GND","gnd", "","gpio", "IOB24a IO3","gpio"
    ),
    row_2_2(
        "3V3","pwr", "3V3","pwr"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_1_1_1_1(
        "","analog", "IOT42b","analog", "","analog", "IOT41a","analog"
    ),
    row_1_1_1_1(
        "","analog", "IOT44b","analog", "","analog", "IOT43a","analog"
    ),
    row_1_1_1_1(
        "","analog", "IOT50b","analog", "","analog", "IOT48b","analog"
    ),
    row_1_1_1_1(
        "","analog", "IOT49a","analog", "","analog", "IOT51a","analog"
    ),
    row_1_1_1_1(
        "GP24 CLK2","gpio", "IOT46b G0","gpio", "GP14 SS","gpio", "IOT45a G1","gpio"
    ),
    row_1_1_1_1(
        "","gpio", "IOB13b","gpio", "","gpio", "IOB20a","gpio"
    ),
    row_1_1_1_1(
        "","gpio", "IOB16a","gpio", "","gpio", "IOB18a PB","gpio"
    ),
    row_2_2(
        "VCCIO2","pwr", "VCCIO2","pwr"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_1_1_1_1(
        "","analog", "IOB5b","analog", "","analog", "IOB3b G6","analog"
    ),
    row_1_1_1_1(
        "","analog", "IOB2a","analog", "","analog", "IOB0a","analog"
    ),
    row_1_1_1_1(
        "","analog", "IOB6a","analog", "","analog", "IOB4a","analog"
    ),
    row_1_1_1_1(
        "","analog", "IOB8a","analog", "","analog", "IOB9b","analog"
    ),
    row_1_1_1_1(
        "RESET","gpio", "","gpio", "SWDIO","gpio", "","gpio"
    ),
    row_2_1_1(
        "GND","gnd", "SWCLK","gpio", "","gpio"
    ),
    row_1_1_1_1(
        "BOOT","gpio", "","gpio", "GP25 CLK3","gpio", "","gpio"
    ),
]

right_header = [
    row_2_2(
        "INNER ROW","", "OUTTER ROW",""
    ),
    row_1_1_1_1(
        "RP2040","", "iCE40","", "RP2040","", "iCE40",""
    ),
    row_1_1_1_1(
        "GP9","gpio", "IOB35B SS","gpio", "GP8 SO","gpio", "IOB32A","gpio"
    ),
    row_1_1_1_1(
        "GP11","gpio", "IOB33b SI","gpio", "GP10","gpio", "IOB34a SCK","gpio"
    ),
    row_1_1_1_1(
        "GP0","analog", "IOT38b","analog", "GP4","analog", "IOT39a","analog"
    ),
    row_1_1_1_1(
        "GP1","analog", "IOT36b","analog", "GP5","analog", "IOT37a","analog"
    ),
    row_1_1_1_1(
        "GP2","analog", "IOB23b","analog", "GP6","analog", "IOB25b","analog"
    ),
    row_1_1_1_1(
        "GP3","analog", "IOB29b","analog", "GP7","analog", "IOB31b","analog"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_2_2(
        "3V3","pwr", "3V3","pwr"
    ),
    row_1_1_1_1(
        "GP26~0","gpio", "CDONE","gpio", "GP5 LED B","gpio", "RGB1","gpio"
    ),
    row_1_1_1_1(
        "GP28~2","gpio", "","gpio", "GP3 LED R","gpio", "RGB2","gpio"
    ),
    row_1_1_1_1(
        "GP29~3","gpio", "","gpio", "GP2 LED G","gpio", "RGB0","gpio"
    ),
    row_1_1_1_1(
        "GP17","analog", "","analog", "GP1","analog", "","analog"
    ),
    row_1_1_1_1(
        "GP19","analog", "","analog", "GP3 CLK0","analog", "","analog"
    ),
    row_1_1_1_1(
        "GP16","analog", "","analog", "GP0","analog", "","analog"
    ),
    row_1_1_1_1(
        "GP18","analog", "","analog", "GP22","analog", "","analog"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_2_2(
        "3V3","pwr", "3V3","pwr"
    ),
    row_2_2(
        "3V3","pwr", "VCC","pwr"
    ),
    row_2_1_1(
        "3V3_SBY","gpio", "PWR_EN","gpio", "","gpio"
    ),
    row_2_2(
        "VBUS","pwr", "GND","gnd"
    ),
]


title = "<tspan class='h1'>pico-ice</tspan>"

description = """A small, low cost board featuring:
- a Raspberry Pi Pico processor (RP2040)
- a Lattice Semiconductor iCE40UP5K FPGA
<tspan class='italic strong'>pico-ice.tinyvision.ai</tspan>"""
