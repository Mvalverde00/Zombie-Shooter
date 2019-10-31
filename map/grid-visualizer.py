"""
A simple tool for splitting up a tileset file into a grid,
so you can easily visualize where a tile begins and ends.

Also assigns each tile an integer ID, which is useful for making maps by hand.
Eventually, a custom tile editor will make this unnecessary, but for now, it's
a great help.

"""
from PIL import Image, ImageDraw
import sys


####  PARAMETERS    ####
FILENAME = "TileSet.png"
TILE_WIDTH = 32
TILE_HEIGHT = 32


# Open the file, get some useful image, and create a context for drawing
im = Image.open(FILENAME)
(WIDTH, HEIGHT) = im.size
draw = ImageDraw.Draw(im)



# Draw Vertical lines
for x in range(WIDTH//TILE_WIDTH):
    draw.line( (x*TILE_WIDTH, 0, x*TILE_WIDTH, HEIGHT), fill="black", width=2 )

# Draw Horizontal lines
for y in range(HEIGHT//TILE_HEIGHT):
    draw.line( (0, y*TILE_HEIGHT, WIDTH, y*TILE_HEIGHT), fill="black", width=2 )

# Produce a file with just the lines
im.save("Output.png", "PNG")



# Draw in Integer IDs
for x in range(WIDTH//TILE_WIDTH):
    for y in range(HEIGHT//TILE_HEIGHT):
        draw.text([x*TILE_WIDTH, y*TILE_HEIGHT], str(x + y*(WIDTH//TILE_WIDTH)))

#Produce a file with lines and integer IDs
im.save("Output-numbered.png", "PNG")


# Memory cleanup
del draw
        
