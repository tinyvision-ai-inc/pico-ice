from pinout.core import Group, Image
from pinout.components.layout import Diagram_2Rows
from pinout.components.pinlabel import PinLabelGroup, PinLabel
from pinout.components.text import TextBlock
from pinout.components import leaderline as lline
from pinout.components.legend import Legend


# Import data for the diagram
import data

# Create a new diagram
# The Diagram_2Rows class provides 2 panels,
# 'panel_01' and 'panel_02', to insert components into.
diagram = Diagram_2Rows(1112, 1010, 880, "diagram")

# Add a stylesheet
diagram.add_stylesheet("styles.css", embed=True)

# Create a group to hold the pinout-diagram components.
graphic = diagram.panel_01.add(Group(400, 42))

# Add and embed an image
hardware = graphic.add(Image("pico_ice_front.png", x=-50, y=-70, embed=True))

# Measure and record key locations with the hardware Image instance
pin_pitch_v = 34.9
pin_start_y = 63
hardware.add_coord("left", 100, pin_start_y)
hardware.add_coord("right", 307, pin_start_y)
# Other (x,y) pairs can also be stored here
hardware.add_coord("pin_pitch_v", 0, pin_pitch_v)

graphic.add(
    PinLabel(
        content="",
        x=hardware.coord("right").x,
        y=hardware.coord("right").y,
        tag="pmod",
        body={"x": 57, "y": 227, "width": 370, "height": 210},
    )
)
graphic.add(
    PinLabel(
        content="",
        x=hardware.coord("right").x,
        y=hardware.coord("right").y,
        tag="pmod",
        body={"x": 57, "y": 541, "width": 370, "height": 210},
    )
)
graphic.add(
    PinLabel(
        content="",
        x=hardware.coord("left").x,
        y=hardware.coord("left").y,
        tag="pmod",
        body={"x": -(370 + 57), "y": 227, "width": 370, "height": 210},
    )
)
graphic.add(
    PinLabel(
        content="",
        x=hardware.coord("left").x,
        y=hardware.coord("left").y,
        tag="pmod",
        body={"x": -(370 + 57), "y": 541, "width": 370, "height": 210},
    )
)

# Create pinlabels on the left header
graphic.add(
    PinLabelGroup(
        x=hardware.coord("left").x,
        y=hardware.coord("left").y,
        pin_pitch=hardware.coord("pin_pitch_v", raw=True),
        label_start=(60, 0),
        label_pitch=(0, pin_pitch_v),
        scale=(-1, 1),
        labels=data.left_header,
    )
)

# Create pinlabels on the left header
graphic.add(
    PinLabelGroup(
        x=hardware.coord("right").x,
        y=hardware.coord("right").y,
        pin_pitch=hardware.coord("pin_pitch_v", raw=True),
        label_start=(60, 0),
        label_pitch=(0, pin_pitch_v),
        scale=(1, 1),
        labels=data.right_header,
    )
)


# Create a title and description text-blocks
title_block = diagram.panel_02.add(
    TextBlock(
        data.title,
        x=20,
        y=30,
        line_height=18,
        tag="panel title_block",
    )
)
diagram.panel_02.add(
    TextBlock(
        data.description,
        x=20,
        y=60,
        width=title_block.width,
        height=diagram.panel_02.height - title_block.height,
        line_height=18,
        tag="panel text_block",
    )
)

# Create a legend
legend = diagram.panel_02.add(
    Legend(
        data.legend,
        x=340,
        y=8,
        max_height=132,
    )
)

# Export the diagram via commandline:
# >>> py -m pinout.manager --export pinout_diagram.py diagram.svg
