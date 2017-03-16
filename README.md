# Pixicognitive

This is toy repo for learning C++ by playing around with images.

Right now it lets you make pretty pictures of square blocks of 8 different colors.

![](./keep/first-squares.png)

## API (pixicognitive namespace)

## Class: Image 

This is the base image class for pixicognitive. It lets you create a new image, edit its pixels, get its pixels and save.

### Image(int width; int height)

By passing `width` and `height` you are able to setup an empty image.

```
Image img = Image(10, 10);
```

### Image::get(int x, int y, int c)

Get the single value you need!

...
