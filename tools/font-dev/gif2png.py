#!/usr/bin/env python

import os
import sys
import argparse
import numpy

try:
    from PIL import Image, ImageOps, GifImagePlugin
except ImportError:
    exit("This script requires the pillow module\nInstall with: sudo pip install pillow")

parser = argparse.ArgumentParser(description='Process gif to png sprite sheet')
parser.add_argument('file', help='image file to read')

if len(sys.argv)<2:
    parser.print_usage(sys.stderr)
    sys.exit(1)
args = parser.parse_args()

im = Image.open( args.file )

def iter_frames(im):
    try:
        i= 0
        while 1:
            im.seek(i)
            imframe = im.copy()
            if i == 0: 
                palette = imframe.getpalette()
            else:
                imframe.putpalette(palette)
            yield imframe
            i += 1
    except EOFError:
        pass

for i, frame in enumerate(iter_frames(im)):
    frame.save('test%d.png' % i,**frame.info)

