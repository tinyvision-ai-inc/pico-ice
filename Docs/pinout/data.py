legend = [
    ("RP2040 pin",          "pin_rpi"),
    ("~R ~G ~B: LED",       "pin_rpi"),
    ("~0 ~1 ~2 ~3: ADC",    "pin_rpi"),
    ("CK0 CK2 CK3: clock",  "pin_rpi"),
    ("iCE40 pin",           "pin_ice"),
    ("SS SCK SI SO: SPI",   "pin_ice"),
    ("FIO2 FIO3: QSPI",     "pin_ice"),
    ("PB: Push Button",     "pin_ice"),
    ("Pmod 1: ICE Pmod",    "pmod"),
    ("Pmod 2: ICE Pmod",    "pmod"),
    ("Pmod 3: RP-ICE Pmod", "pmod"),
    ("Pmod 4: RP Pmod",     "pmod"),
    ("Ground pin",          "gnd"),
    ("Power pin",           "pwr"),
]

def double(label, type, x):
    return (label, type, {"body": {"width": 166, "x": x}})

def row_2_2(name1, type1, name2, type2):
    return [
        (name1, type1, {"body": {"width": 166, "x": 6}}),
        (name2, type2, {"body": {"width": 166, "x": 20}}),
    ]

def row_2_2_pmod(pmod, name1, type1, name2, type2):
    return [
        (name1, type1, {"body": {"width": 166, "x": 6}}),
        (name2, type2, {"body": {"width": 166, "x": 20}}),
        (pmod, "pmod", {"body": {"width": 20, "x": 0}}),
    ]

def row_1_1_1_1(name1, type1, name2, type2, name3, type3, name4, type4):
    return [
        (name1, type1),
        (name2, type2),
        (name3, type3, {"body": {"x": 20}}),
        (name4, type4),
    ]

def row_1_1_1_1_pmod(pmod, name1, type1, name2, type2, name3, type3, name4, type4):
    return [
        (name1, type1),
        (name2, type2),
        (name3, type3, {"body": {"x": 20}}),
        (name4, type4),
        (pmod, "pmod", {"body": {"width": 20, "x": 0}}),
    ]

def row_2_1_1(name1, type1, name2, type2, name3, type3):
    return [
        (name1, type1, {"body": {"width": 166, "x": 6}}),
        (name2, type2, {"body": {"x": 20}}),
        (name3, type3),
    ]

def row_1_1_2(name1, type1, name2, type2, name3, type3, name4, type4):
    return [
        (name1, type1, {"body": {"x": 6}}),
        (name2, type2, {"body": {"x": 6}}),
        (name3, type3, {"body": {"width": 166, "x": 20}}),
    ]

# The pins will appear swapped left/right
left_header = [
    row_2_2(
        "INNER ROW","l", "OUTTER ROW","l",
    ),
    row_1_1_1_1(
        "iCE40","l", "RP2040","l", "iCE40","l", "RP2040","l"
    ),
    row_1_1_1_1(
        "CRESET","pin_ice", "RP27 ~1","pin_rpi", "ICE12 FIO2","pin_ice", "","pin_rpi"
    ),
    row_2_1_1(
        "GND","gnd", "ICE13 FIO3","pin_ice", "","pin_rpi"
    ),
    row_2_2_pmod("2",
        "3V3","pwr", "3V3","pwr"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_1_1_1_1(
        "ICE31","pin_ice", "","pin_rpi", "ICE28","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE34","pin_ice", "","pin_rpi", "ICE32","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE38","pin_ice", "","pin_rpi", "ICE36","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE43","pin_ice", "","pin_rpi", "ICE42","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE35","pin_ice", "RP24 CK2","pin_rpi", "ICE37 SS","pin_ice", "RP14","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE6","pin_ice", "","pin_rpi", "ICE11","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE9","pin_ice", "","pin_rpi", "ICE10 PB","pin_ice", "","pin_rpi"
    ),
    row_2_2_pmod("1",
        "VIO2","pwr", "VIO2","pwr"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_1_1_1_1(
        "ICE45","pin_ice", "","pin_rpi", "ICE44","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE47","pin_ice", "","pin_rpi", "ICE46","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE2","pin_ice", "","pin_rpi", "ICE48","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "ICE4","pin_ice", "","pin_rpi", "ICE3","pin_ice", "","pin_rpi"
    ),
    row_1_1_1_1(
        "","pin_ice", "RESET","pin_rpi", "","pin_ice", "SWDIO","pin_rpi"
    ),
    row_2_1_1(
        "GND","gnd", "","pin_ice", "SWCLK","pin_rpi"
    ),
    row_1_1_1_1(
        "","pin_ice", "USBBOOT","pin_rpi", "","pin_ice", "RP25 CK3","pin_rpi"
    ),
]

right_header = [
    row_2_2(
        "INNER ROW","l", "OUTTER ROW","l"
    ),
    row_1_1_1_1(
        "RP2040","l", "iCE40","l", "RP2040","l", "iCE40","l"
    ),
    row_1_1_1_1(
        "RP9","pin_rpi", "ICE16 SS","pin_ice", "RP8","pin_rpi", "ICE14 SO","pin_ice"
    ),
    row_1_1_1_1(
        "RP11","pin_rpi", "ICE17 SI","pin_ice", "RP10","pin_rpi", "ICE15 SCK","pin_ice"
    ),
    row_1_1_1_1_pmod("3",
        "RP1","pin_rpi", "ICE25","pin_ice", "RP5","pin_rpi", "ICE23","pin_ice"
    ),
    row_1_1_1_1(
        "RP3","pin_rpi", "ICE19","pin_ice", "RP7","pin_rpi", "ICE18","pin_ice"
    ),
    row_1_1_1_1(
        "RP0","pin_rpi", "ICE27","pin_ice", "RP4","pin_rpi", "ICE26","pin_ice"
    ),
    row_1_1_1_1(
        "RP2","pin_rpi", "ICE21","pin_ice", "RP6","pin_rpi", "ICE20","pin_ice"
    ),
    row_2_2(
        "GND","gnd", "GND","gnd"
    ),
    row_2_2(
        "3V3","pwr", "3V3","pwr"
    ),
    row_1_1_1_1(
        "RP26 ~0","pin_rpi", "CDONE","pin_ice", "RP15 ~B","pin_rpi", "RGB1","pin_ice"
    ),
    row_1_1_1_1(
        "RP28 ~2","pin_rpi", "","pin_ice", "RP13 ~R","pin_rpi", "RGB2","pin_ice"
    ),
    row_1_1_1_1(
        "RP29 ~3","pin_rpi", "","pin_ice", "RP12 ~G","pin_rpi", "RGB0","pin_ice"
    ),
    row_1_1_1_1_pmod("4",
        "RP17","pin_rpi", "","pin_ice", "RP21","pin_rpi", "","pin_ice"
    ),
    row_1_1_1_1(
        "RP19","pin_rpi", "","pin_ice", "RP23 CK0","pin_rpi", "","pin_ice"
    ),
    row_1_1_1_1(
        "RP16","pin_rpi", "","pin_ice", "RP20","pin_rpi", "","pin_ice"
    ),
    row_1_1_1_1(
        "RP18","pin_rpi", "","pin_ice", "RP22","pin_rpi", "","pin_ice"
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
        "3V3_SBY","pin_rpi", "PWR_EN","pin_rpi", "","pin_ice"
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
