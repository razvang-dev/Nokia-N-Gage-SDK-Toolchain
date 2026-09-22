#!/usr/bin/env python3
"""Rewrite an uncompressed 24-bit BMP using a classic 40-byte BITMAPINFOHEADER.

This exists because Symbian BMCONV 110 can silently color-shift some newer BMP/DIB
header variants. It preserves the pixel array and basic geometry of a BI_RGB 24-bit
BMP while writing the conservative header format proven on the Nokia N-Gage.
"""
import argparse, struct, sys
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('input')
p.add_argument('output')
a = p.parse_args()
raw = Path(a.input).read_bytes()
if len(raw) < 54 or raw[:2] != b'BM':
    sys.exit('Not a BMP file')
pixoff = struct.unpack_from('<I', raw, 10)[0]
dib = struct.unpack_from('<I', raw, 14)[0]
if dib < 40:
    sys.exit(f'Unsupported DIB header size {dib}; expected >= 40')
width, height, planes, bpp, comp, imgsize, xppm, yppm, used, important = struct.unpack_from('<iiHHIIiiII', raw, 18)
if planes != 1 or bpp != 24 or comp != 0:
    sys.exit(f'Only uncompressed 24-bit BI_RGB BMP is supported (got planes={planes}, bpp={bpp}, compression={comp})')
rowbytes = ((abs(width) * 3 + 3) // 4) * 4
need = rowbytes * abs(height)
pixels = raw[pixoff:pixoff+need]
if len(pixels) != need:
    sys.exit('BMP pixel array is truncated')
outoff = 14 + 40
filesize = outoff + len(pixels)
fh = b'BM' + struct.pack('<IHHI', filesize, 0, 0, outoff)
ih = struct.pack('<IiiHHIIiiII', 40, width, height, 1, 24, 0, len(pixels), xppm, yppm, 0, 0)
Path(a.output).write_bytes(fh + ih + pixels)
print(f'Wrote classic BITMAPINFOHEADER BMP: {a.output} ({width}x{abs(height)}, 24-bit, {filesize} bytes)')
