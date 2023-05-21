all:
	rm -f diagram.svg diagram.png
	python3 -m pinout.manager --export pinout_diagram.py diagram.svg
	chromium --headless --screenshot --window-size=1112,1010 diagram.svg
	mv screenshot.png diagram.png
