# Put this file

from PIL import Image
import os

FILENAME = "survivor-move_knife_" # The file name, with numbers at the end truncated
FILETYPE = ".png" # The file extension.  e.g. ".png" ".jpg"

images = []

i = 0
while True:
    try:
        im = Image.open( os.getcwd() + "\\" + FILENAME + str(i) + FILETYPE)
        images.append(im)
        i += 1
    except FileNotFoundError:
        break

(width, height) = images[0].size

final = Image.new("RGBA", (width*len(images), height) )

for i, im in enumerate(images):
    final.paste(im, (i*width, 0))

final.save(os.getcwd() + "\\" + FILENAME + FILETYPE)
