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
import fontmonkey
import fontball

scrollphathd.rotate(degrees=180)
scrollphathd.set_font( fontd3 )
font_width = fontd3.width
timeout = 0
scroll_time = 0
base_brightness = 1.0
show_ball = False

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
            scrollphathd.clear()
            x = (17/2) - (width/2)
            if x < 0:
               x = 0
    	    scrollphathd.write_string( string, x=x, y=2, brightness=1.0 )
            timeout = time.time() + 1.0
        
        if '<ball>' in msg:
            string = msg[ msg.find('>')+1 : ]
            scrollphathd.clear()
            show_ball = True
            scrollphathd.set_font( fontd3 )
            scrollphathd.write_string( string, x=10, y=1, brightness=1.0 )
            timeout = time.time() + 1.0

    perc = (timeout - time.time()) / 1.0
    if perc > 0:
        if show_ball:
           ball_i = int(14.0*(1.0-perc)) % 7
           scrollphathd.set_font( fontball )
           scrollphathd.write_string( chr(ord('0')+ball_i), x=1, y=0, brightness=1.0 )           
        b = base_brightness + ((1.0-base_brightness)*perc);
        y = 8.0*perc 
        print "%0.2f %0.2f %0.2f" % (perc,b,y)
        scrollphathd.set_brightness( b )
        #scrollphathd.scroll_to( x=0, y=int(y) )
        #scrollphathd.fill(0,0,17,1)
        scrollphathd.show()
    else:
        show_ball = False
#        #if not scroll_time or (scroll_time - time.time() > 0.2):
#        #    scroll_time = time.time()
#        scrollphathd.scroll()
#        scrollphathd.show()


