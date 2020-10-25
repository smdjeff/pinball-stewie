#!/usr/bin/env python

import signal
import time

import scrollphathd
from scrollphathd.fonts import font3x5

scrollphathd.rotate(degrees=180)

scrollphathd.write_string(" VICTORY SHALL BE MINE!", y=1, font=font3x5, brightness=0.3)

while True:
    scrollphathd.show()
    scrollphathd.scroll()
    time.sleep(0.1)
