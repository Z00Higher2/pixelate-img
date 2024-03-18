import numpy as np

def read_image(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()

    idx = 0
    while lines[idx][0] == '#':
        idx += 1

    width, height = map(int, lines[idx].split())
    idx += 1

    max_val = int(lines[idx])
    idx += 1

    image = []
    for line in lines[idx:]:
        image.extend(list(map(int, line.split())))

    image = np.array(image).reshape(height, width)
    return image, height, width

def write_image(image, filename):
    height, width = image.shape
    with open(filename, 'w') as f:
        f.write("P2\n")
        f.write(f"{width} {height}\n")
        f.write("255\n")
        for row in image:
            for val in row:
                f.write(f"{val} ")
            f.write("\n")

def interpolate_image(img):
    h, w = img.shape
    out = np.zeros((h, w))

    for row in range(h):
        for col in range(w):
            if row % 2 == 0:
                if col % 2 == 0:
                    out[row, col] = (img[row, col] + img[row + 1, col] + img[row, col + 1] + img[row + 1, col + 1]) // 4
                else:
                    out[row, col] = (img[row, col] + img[row + 1, col] + img[row, col - 1] + img[row + 1, col - 1]) // 4
            else:
                if col % 2 == 0:
                    out[row, col] = (img[row, col] + img[row - 1, col] + img[row - 1, col + 1] + img[row, col + 1]) // 4
                else:
                    out[row, col] = (img[row, col] + img[row - 1, col] + img[row, col - 1] + img[row - 1, col - 1]) // 4

    return out

def main():
    img, h, w = read_image("inImage.pgm")
    out_img = interpolate_image(img)
    write_image(out_img, "outImage.pgm")

if __name__ == "__main__":
    main()
