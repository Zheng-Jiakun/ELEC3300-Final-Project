import numpy as np
import PIL.Image

an_image = PIL.Image.open("pictures/grass.jpg")
an_image = an_image.rotate(270)
# an_image = an_image.resize((30, 320))

image_sequence = an_image.getdata()
image_array = np.array(image_sequence)

f = open("image.h", "w")
for i in range(len(image_array)):
    f.write("{")
    for j in range(len(image_array[i])):
        f.write(str(image_array[i][j]))
        if j != len(image_array[i]) - 1:
            f.write(str(","))
    f.write("},\n")
f.close()