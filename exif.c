#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <libexif/exif-data.h>
#include "filemethods.h"
/* Show the tag name and contents if the tag exists */
void show_tag(ExifData *d, ExifIfd ifd, ExifTag tag) {
    /* See if this tag exists */
    ExifEntry *entry = exif_content_get_entry(d->ifd[ifd], tag);
    if (entry) {
        char tagEntry[1024];

        /* Get the contents of the tag in human-readable form */
        exif_entry_get_value(entry, tagEntry, sizeof(tagEntry));

        trim_spaces(tagEntry);
        if (*tagEntry) printf("%s: %s\n", exif_tag_get_name_in_ifd(tag, ifd), tagEntry);
    }
}

int get_exifData(const char *path, ExifData **data) {
    char fullPath[PATH_MAX];
    realpath(path, fullPath);
    *data = exif_data_new_from_file(fullPath);
    if (!*data) {
        return 1;
    }
    return 0;
}