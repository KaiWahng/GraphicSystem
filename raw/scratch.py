import PIL
rawData = open("pic000.raw", 'rb').read()
imgSize = (800,480)
# Use the PIL raw decoder to read the data.
# the 'F;16' informs the raw decoder that we are reading
# a little endian, unsigned integer 16 bit data.
img = Image.frombytes('L', imgSize, rawData)
img.save("foo.png")