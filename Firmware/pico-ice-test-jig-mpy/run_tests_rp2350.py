import machine, ice, time

FIRST_GPIO_PIN = 0
LAST_GPIO_PIN = 47
FPGA_BUTTON_PIN = 26 #ice 21
FPGA_HIGH_Z_PIN = 22 #ice 20
FPGA_CRESET = 31
FPGA_CDONE = 40
FPGA_CLOCK = 21
CHAIN_IN_PIN = 24 #ice 26
CHAIN_OUT_PIN = 20 #ice 27
RED_LED = 1
BLUE_LED = 9
GREEN_LED = 0
SRAM_SS = 8

#EXCLUDE_PINS_TESTING = [ 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 37, 38, 39 ]
EXCLUDE_PINS_TESTING = []

EXCLUDE_PINS = [ SRAM_SS, FPGA_CLOCK, FPGA_CRESET]
SYSTEM_PINS = [ FPGA_BUTTON_PIN, FPGA_CDONE, FPGA_HIGH_Z_PIN ]
PULLED_PINS = [ 2, 3, 4, 5, 6, 7, 47, RED_LED, BLUE_LED, GREEN_LED ]
PIN_CONNECTIONS = { (32, 36), (33, 37), (34, 38), (35, 39), (30, 25), (23, 27), (43, 44)}
PIN_CHAIN = (CHAIN_IN_PIN, CHAIN_OUT_PIN)
RIG_DETECT = { (5, 7), (4, 6) }

X_CHECKS = 5

class TestPin:
	def __init__(self, pin_nb: int, driveable: bool, pulled_externally: bool):
		self.pin = machine.Pin(pin_nb, machine.Pin.IN)
		self.pin_nb = pin_nb
		self.driveable = driveable
		self.pulled_externally = pulled_externally

	def set_1(self):
		self.pin.init(machine.Pin.OUT)
		self.pin.value(1)

	def set_0(self):
		self.pin.init(machine.Pin.OUT)
		self.pin.value(0)

	def get(self):
		self.pin.init(machine.Pin.IN)
		return bool(self.pin.value())

	def check_consistency(self):
		success = True
		if self.driveable:
			print("Checking pin consistency for " + str(self.pin_nb))
			for i in range(0, X_CHECKS):
				# Workaround for Errata E9
				self.pin.init(machine.Pin.OUT)
				self.pin.on()
				time.sleep_ms(1)
				if self.pin.value() != 1:
					success = False
				self.pin.off()
				time.sleep_ms(1)
				if self.pin.value() != 0:
					success = False
				# if self.pulled_externally:
				# 	self.pin.init(machine.Pin.OUT)
				# 	self.pin.on()
				# 	time.sleep_ms(1)
				# 	if self.pin.value() != 1:
				# 		success = False
				# 	self.pin.off()
				# 	time.sleep_ms(1)
				# 	if self.pin.value() != 0:
				# 		success = False
				# else:
				# 	self.pin.init(machine.Pin.IN, machine.Pin.PULL_UP)
				# 	time.sleep_ms(1)
				# 	if self.pin.value() != 1:
				# 		success = False
				# 	self.pin.init(machine.Pin.IN, machine.Pin.PULL_DOWN)
				# 	time.sleep_ms(1)
				# 	if self.pin.value() != 0:
				# 		success = False
			self.pin.init(machine.Pin.IN)
		return success

	def check_connected(self, pin: TestPin, log: bool = True):
		success = True
		if log:
			print("Checking connection between " + str(self.pin_nb) + " and " + str(pin.pin_nb))
		for i in range(0, X_CHECKS):
			self.set_0()
			time.sleep_ms(1)
			if pin.get():
				success = False
			self.set_1()
			time.sleep_ms(1)
			if not pin.get():
				success = False

		self.get()

		return success

	def check_not_connected(self, pin: TestPin):
		success = True
		if self.driveable and not pin.pulled_externally:
			print("Checking pin shorting for " + str(self.pin_nb) + " with " + str(pin.pin_nb))
			for i in range(0, X_CHECKS):
				pin.pin.init(machine.Pin.IN, machine.Pin.PULL_UP)
				self.set_0()
				time.sleep_ms(1)
				if not pin.get():
					success = False
				pin.pin.init(machine.Pin.IN, machine.Pin.PULL_DOWN)
				self.set_1()
				time.sleep_ms(1)
				if pin.get():
					success = False

			self.get()
			pin.get()

		return success


	def __repr__(self):
		return "TestPin(" + str(self.pin_nb) + ", " + str(self.driveable) + ", " + str(self.pulled_externally) + ")"



blink_error_do_step = True
blink_error_do_led1 = None
blink_error_do_led2 = None
def blink_error_do(timer):
	global blink_error_do_step
	global blink_error_do_led1
	global blink_error_do_led2
	if blink_error_do_step:
		blink_error_do_led1.off()
		blink_error_do_led2.on()
		blink_error_do_step = False
	else:
		blink_error_do_led1.on()
		blink_error_do_led2.off()
		blink_error_do_step = True

def blink_error(second_led):
	global blink_error_do_led1
	global blink_error_do_led2
	blink_error_do_led1 = machine.Pin(RED_LED, machine.Pin.OUT)
	blink_error_do_led2 = machine.Pin(second_led, machine.Pin.OUT)
	machine.Timer(-1, mode=machine.Timer.PERIODIC, freq=4, callback=blink_error_do)

def setup_fpga():
	fpga = ice.fpga(cdone=machine.Pin(FPGA_CDONE), clock=machine.Pin(FPGA_CLOCK), creset=machine.Pin(FPGA_CRESET), cram_cs=machine.Pin(5), cram_mosi=machine.Pin(4), cram_sck=machine.Pin(6), frequency=48)
	fpga.stop()
	if not fpga.start():
		raise Exception("\x1b[31mThere was an error setting up fpga" + "\x1b[37m")
	file = open("test.bit", "br")
	#will throw error if failed
	fpga.cram(file)
	del file
	return fpga

def test_out_jig(pins):
	print("\x1b[37mStarting out of Jig test")
	print("\x1b[37mRP2 pin self-test")
	for i, pin in pins.items():
		if not pin.check_consistency():
			raise Exception("\x1b[31mConsistency Check Failed on pin: " + str(pin.pin_nb) + "\x1b[37m")
	print("\x1b[37mRP2 pin shorting test")
	# Hits errata E9 and breaks, good job RPI!
	#for i, pin in pins.items():
	#	test_pin = pins.get(i + 1)
	#	if test_pin is not None:
	#		if not pin.check_not_connected(test_pin):
	#			raise Exception("\x1b[31mShorting Check Failed on pin: " + str(pin.pin_nb) + " with " + str(test_pin.pin_nb) + "\x1b[37m")
	#		if not test_pin.check_not_connected(pin):
	#			raise Exception("\x1b[31mShorting Check Failed on pin: " + str(test_pin.pin_nb) + " with " + str(pin.pin_nb) + "\x1b[37m")
	print("\x1b[32mRP2 pin self-test passed")

def test_in_jig(pins):
	global PIN_CONNECTIONS
	global PIN_CHAIN
	print("\x1b[37mStarting IN-Jig test")
	print("\x1b[37mPin pairs test")
	for a, b in PIN_CONNECTIONS:
		if not pins[a].check_connected(pins[b]):
			raise Exception("\x1b[31mPin pairs Check Failed on pins: " + str(pins[a].pin_nb) + " to " + str(pins[b].pin_nb) + "\x1b[37m")
	print("\x1b[37mPin chain test")
	pins[FPGA_HIGH_Z_PIN].set_0()
	pins[FPGA_HIGH_Z_PIN].set_0()

	time.sleep_ms(5)

	if not pins[PIN_CHAIN[0]].check_connected(pins[PIN_CHAIN[1]]):
			raise Exception("\x1b[31mPin chain Check Failed between " + str(PIN_CHAIN[0]) + " and " + str(PIN_CHAIN[1]) + "\x1b[37m")

	pins[FPGA_HIGH_Z_PIN].set_1()
	pins[FPGA_HIGH_Z_PIN].set_1()
	print("\x1b[32mIn-Jig self-test passed")

def in_jig(pins):
	global RIG_DETECT
	success = True
	for a, b in RIG_DETECT:
		if not pins[a].check_connected(pins[b], False):
			success = False
	return success

#setup fpga with test bitstream
fpga = setup_fpga()


time.sleep(0.1)

#initialize pins
TEST_PINS = {}
for i in range(FIRST_GPIO_PIN, LAST_GPIO_PIN + 1):
	if i in EXCLUDE_PINS or i in EXCLUDE_PINS_TESTING:
		pass
	elif i in SYSTEM_PINS:
		TEST_PINS[i] = TestPin(i, False, True)
	elif i in PULLED_PINS:
		TEST_PINS[i] = TestPin(i, True, True)
	else:
		TEST_PINS[i] = TestPin(i, True, False)

#print("list of pins: " + str(TEST_PINS))


#tell fpga to set itself to high-z
TEST_PINS[FPGA_HIGH_Z_PIN].set_1()
TEST_PINS[FPGA_HIGH_Z_PIN].set_1()

time.sleep(0.1)

try:
	test_out_jig(TEST_PINS)
except Exception as err:
	print("\x1b[31mTest Failed\x1b[37m")
	blink_error(BLUE_LED)
	raise err

print("Please Insert in test rig")
while True:
	time.sleep_ms(100)
	if in_jig(TEST_PINS):
		time.sleep_ms(250)
		if in_jig(TEST_PINS):
			break
		else:
			print("Detected temporary rig presence, please ensure proper connection")


try:
	test_in_jig(TEST_PINS)
except Exception as err:
	print("\x1b[31mTest Failed\x1b[37m")
	blink_error(GREEN_LED)
	raise err

print("\x1b[32mAll tests passed\x1b[37m")
