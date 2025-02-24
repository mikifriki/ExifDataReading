#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#include <libexif/exif-data.h>
#include "filemethods.h"
#include "exif.h"

int find_Directory_Files_Exif(const char *filePath) {
    DIR *dir;
    const struct dirent *dp;
    char relativePath[PATH_MAX];

    if (!(dir = opendir(filePath))) {
        perror("");
        return 1;
    }
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 || strlen(dp->d_name) == 0) continue;

        const char *fileExtension = get_filename(dp->d_name);
        if (fileExtension != NULL && (strcmp(fileExtension, "jpeg") || strcmp(fileExtension, "png") || strcmp(
                                          fileExtension, "jpg"))) {
            // Construct the relative path
            snprintf(relativePath, sizeof(relativePath), "%s/%s", filePath, dp->d_name);

            ExifData *data;
            if (get_exifData(relativePath, &data)) {
                printf("No EXIF data found for file: %s\n", dp->d_name);
                continue;
            }
            printf("File: %s; ", dp->d_name);
            show_tag(data, EXIF_IFD_0, EXIF_TAG_DATE_TIME);
            exif_data_free(data);
                                          }
    }

    closedir(dir);
    return 0;
}

int find_File_Exif(const char *filePath) {
    if (is_directory(filePath) == 0) {
        ExifData *data;

        if (get_exifData(filePath, &data)) {
            printf("No EXIF data found for file: %s\n", filePath);
            return 1;
        }
        show_tag(data, EXIF_IFD_0, EXIF_TAG_DATE_TIME);
        exif_data_free(data);
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        printf("No directory or file given as an argument\n");
        return 0;
    }
    const char *filePath = argv[1];

    if (find_File_Exif(filePath) == 0) {
        return 0;
    }

    if (find_Directory_Files_Exif(filePath) == 0) {
        return 0;
    }

    return 1;
}
