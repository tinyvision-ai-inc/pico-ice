all:
	rm -f pinout.svg pinout.png
	python3 -m pinout.manager --export pinout_diagram.py pinout.svg
	chromium --headless --screenshot --window-size=1112,1010 pinout.svg
	mv screenshot.png pinout.png
