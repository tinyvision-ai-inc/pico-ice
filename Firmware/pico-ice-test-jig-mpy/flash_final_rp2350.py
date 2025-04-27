from machine import Pin
import ice
file = open("final.bit", "br")
flash = ice.flash(miso=Pin(4), mosi=Pin(7), sck=Pin(6), cs=Pin(5))
flash.write(file)
print("Done flashing")