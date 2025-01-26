#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <libexif/exif-data.h>
#include "filemethods.h"

/* Show the tag name and contents if the tag exists */
static void show_tag(ExifData *d, ExifIfd ifd, ExifTag tag) {
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


int main(int argc, char *argv[]) {
    if (!argv[1]) {
        printf("No directory given as an argument\n");
        return 0;
    }

    DIR *dir;

    if ((dir = opendir(argv[1])) == NULL) {
        perror("Cannot open directory");
        return 1;
    }

    const char *fileExtension;
    const struct dirent *dp;

    char fullPath[PATH_MAX];
    char relativePath[PATH_MAX];
    ExifData *data;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 || strlen(dp->d_name) == 0) continue;

        fileExtension = get_filename(dp->d_name);
        if (fileExtension != NULL && (strcmp(fileExtension, "jpeg") || strcmp(fileExtension, "png") || strcmp(fileExtension, "jpg"))) {
            // Construct the relative path
            snprintf(relativePath, sizeof(relativePath), "%s/%s", argv[1], dp->d_name);

            realpath(relativePath, fullPath);
            data = exif_data_new_from_file(fullPath);

            if (!data) {
                printf("No EXIF data found for file: %s\n", dp->d_name);
                continue;
            }
            printf("File: %s; ", dp->d_name);
            show_tag(data, EXIF_IFD_0, EXIF_TAG_DATE_TIME);
            exif_data_free(data);
        }
    }

    closedir(dir);
    return 1;
}
