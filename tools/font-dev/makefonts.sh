DEST=../../fonts/
# ./mkfont.py 5x7-font.png -m 2 2 -s 2 2 > $DEST/font5x7.txt
# ./mkfont.py 5x7-font-smoothed.png -m 2 2 -s 2 2 > $DEST/font5x7smoothed.txt
# ./mkfont.py 5x7-font-unicode.png -sz 16 16 -fz 5 7 -m 1 1 > $DEST/font5x7unicode.txt
# ./mkfont.py 3x5-font.png -sz 32 3 -fz 3 5 -c " \!\"#\$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_\`abcdefghijklmnopqrstuvwxyz{|}~" > $DEST/font3x5.txt
# ./mkfont.py 5x5-font.png -sz 3 32 -vert -fz 5 5 -c " \!\"#\$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_" > $DEST/font5x5.txt
# ./mkfont.py gauntlet.png -sz 13 3 -fz 7 7 -c 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789' > $DEST/fontgauntlet.txt
# ./mkfont.py organ.png -sz 13 3 -fz 13 7 -m 1 1 -s 1 1 -c 'ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890' > $DEST/fontorgan.txt
# ./mkfont.py hachicro.png -sz 13 4 -fz 7 7 -s 1 1 -m 0 1 -c 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789' > $DEST/fonthachicro.txt
./mkfont.py d3.png -hex -sz 13 4 -fz 6 5 -s 0 1 -c 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789' > $DEST/fontd3.txt

