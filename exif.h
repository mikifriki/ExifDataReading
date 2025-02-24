#ifndef EXIF_H
#define EXIF_H
void show_tag(ExifData *d, ExifIfd ifd, ExifTag tag);
int get_exifData(const char *path, ExifData **data);
#endif //EXIF_H
