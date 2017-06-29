# Pixicog

![](./keep/first-squares.png)

This project aims to provide a set of C++ modules for working with images and it aims to do this with no external dependencies.

These modules will be shipped in two ways, C++ and Node.js. In the future, it would be nice to support other langauges such as Python.

All Node.js modules, when depending on each other, should be interoperable without moving memory from C++ land to Javascript land.

## Modules

* @pixicog/image: the base data layer. Getting and setting in different color spaces.
* [@pixicog/png](http://lodev.org/lodepng/): open and save pngs
* [@pixicog/spatial-highpass-filter](https://diffractionlimited.com/help/maximdl/High-Pass_Filtering.htm)
* [@pixicog/unsharp-mask](https://diffractionlimited.com/help/maximdl/Unsharp_Mask_Basics.htm)
* [@pixicog/spatial-lowpass-filter](https://diffractionlimited.com/help/maximdl/Low-Pass_Filtering.htm)
* @pixicog/restore: probs not called this, but something in the image restoration space
* [@pixicog/gaussian-blur](https://en.wikipedia.org/wiki/Gaussian_blur)
* [@pixicog/posterization](https://en.wikipedia.org/wiki/Posterization)

## Links for reading

- [Linear filter](http://luthuli.cs.uiuc.edu/~daf/courses/cs5432009/week%203/simplefilters.pdf)
- [Wavelet trasnform](https://en.wikipedia.org/wiki/Wavelet_transform)
