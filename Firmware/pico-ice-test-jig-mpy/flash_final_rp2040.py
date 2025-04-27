from machine import Pin
import ice
file = open("final.bit", "br")
flash = ice.flash(miso=Pin(8), mosi=Pin(11), sck=Pin(10), cs=Pin(9))
flash.write(file)
print("Done flashing")