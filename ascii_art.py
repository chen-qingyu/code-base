from PIL import Image, ImageDraw, ImageFont
import argparse
import numpy as np


def ascii_art(file, sample_rate=0.4):
    img = Image.open(file)

    # Compute letter aspect ratio
    font = ImageFont.load_default()
    aspect_ratio = font.getsize("x")[0] / font.getsize("x")[1]
    new_img_size = np.array([img.size[0] * sample_rate, img.size[1] * sample_rate * aspect_ratio]).astype(int)

    # Downsample the image
    img = img.resize(new_img_size)

    # Keep a copy of image for color sampling
    img_color = np.array(img)

    # Convert to gray scale image
    img = img.convert("L")

    # Convert to numpy array for image manipulation
    img = np.array(img)

    # Defines all the symbols in ascending order that will form the final ascii
    symbols = np.array(list(" .,:~=+?I7$ZO8DNM"))

    # Normalize minimum and maximum to [0, max_symbol_index)
    img = (img - img.min()) / (img.max() - img.min()) * (symbols.size - 1)

    # Generate the ascii art
    ascii = symbols[img.astype(int)]

    # Create an output image for drawing ascii text
    letter_size = font.getsize("x")
    img_out_size = new_img_size * letter_size
    img_out = Image.new("RGB", tuple(img_out_size), "black")
    draw = ImageDraw.Draw(img_out)

    # Draw text
    y = 0
    for i, line in enumerate(ascii):
        for j, ch in enumerate(line):
            color = tuple(img_color[i, j])  # sample color from original image
            draw.text((letter_size[0] * j, y), ch[0], fill=color, font=font)
        y += letter_size[1]  # increase y by letter height

    # Save image file
    img_out.save(file + ".ascii.png")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert any image to ascii art.")
    parser.add_argument("file", type=str, help="input image file",)
    args = parser.parse_args()

    ascii_art(args.file)
