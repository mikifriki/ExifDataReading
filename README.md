# ExifDataReading
A small C application which reads EXIF data using the [https://libexif.github.io/](https://libexif.github.io/) library. Data is read from JPG files and some PNG files which also support exif data.


## Compiling
[Libexif package is required in order to compile. ](https://libexif.github.io/)
In order to compile run.
```
gcc main.c filemethods.c -lexif 
```
## test image

Test Image gotten from the example repo
https://github.com/ianare/exif-samples
