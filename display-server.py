#!/usr/bin/env python

import signal
import time
import zmq
import re
import scrollphathd
from scrollphathd.fonts import font3x5
from scrollphathd.fonts import font5x5
from scrollphathd.fonts import font5x7
from scrollphathd.fonts import font5x7smoothed
import fontorgan
import fonthachicro
import fontgauntlet
import fontd3

scrollphathd.rotate(degrees=180)
scrollphathd.set_font( fontd3 )
font_width = fontd3.width
timeout = 0

print( 'starting display server' )
context = zmq.Context()
socket = context.socket(zmq.PULL)
socket.bind('tcp://127.0.0.1:5555')

while True:
    if socket.poll(10, zmq.POLLIN):
        msg = socket.recv(zmq.NOBLOCK)
        #print repr(msg)

        if '<brightness>' in msg:
            msg = msg[ msg.find('>')+1 : ]
    	    base_brightness = float( msg )
            scrollphathd.set_brightness( base_brightness )

        if '<font>' in msg:
            font = msg[ msg.find('>')+1 : ]
            if 'hachicro' in font:
                scrollphathd.set_font( fonthachicro )
                font_width = fonthachicro.width
            elif 'd3' in font:
                scrollphathd.set_font( fontd3 )
                font_width = fontd3.width
            elif '3x5' in font:
                scrollphathd.set_font( font3x5 )
                font_width = font3x5.width
            elif '5x5' in font:
                scrollphathd.set_font( font5x5 )
                font_width = font5x5.width
            elif '5x7' in font:
                if 'smoothed' in font:
		    scrollphathd.set_font( font5x7smoothed )
                    font_width = font5x7smoothed.width
                else:
		    scrollphathd.set_font( font5x7 )
                    font_width = font5x7.width

        if '<text>' in msg:
            string = msg[ msg.find('>')+1 : ]
            width = len(string) * font_width 
    	    scrollphathd.write_string( string, x=(17+width)/2, y=-7, brightness=1.0 )
            scrollphathd.show()
            timeout = time.time() + 2.0

    perc = timeout - time.time()
    if perc > 0:
        scrollphathd.set_brightness( base_brightness + (1.0*perc) )
        scrollphathd.scroll( y=(-7.0*perc) )
        scrollphathd.show()

