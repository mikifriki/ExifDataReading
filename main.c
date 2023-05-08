#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <libexif/exif-data.h>
#include "filemethods.h"

/* Show the tag name and contents if the tag exists */
static void show_tag(ExifData *d, ExifIfd ifd, ExifTag tag)
{
    /* See if this tag exists */
    ExifEntry *entry = exif_content_get_entry(d->ifd[ifd],tag);
    if (entry) {
        char tagEntry[1024];

        /* Get the contents of the tag in human-readable form */
        exif_entry_get_value(entry, tagEntry, sizeof(tagEntry));

        /* Don't bother printing it if it's entirely blank */
        trim_spaces(tagEntry);
        if (*tagEntry) {
            printf("%s: %s\n", exif_tag_get_name_in_ifd(tag,ifd), tagEntry);
        }
    }
}


int main(int argc, char *argv[]) {
    if (!argv[1]) {
        printf("No directory given as an argument\n");
        return 0;
    }
    const char* fileExtension;
    char filePath[PATH_MAX + 1];
    struct dirent *dp;
    ExifData* data;
    // Open the directory - dir contains a pointer to manage the dir
    DIR *dir = opendir(argv[1]); 

    while (dp=readdir(dir)) 
    {
        // Get file extension
        fileExtension = get_filename_ext(dp->d_name);
        // File extension should not be null. And only continue if they are jpeg or png.
        // This is really awful to expand and should be reworked.
        if (fileExtension != NULL && (!strcasecmp(fileExtension, "jpeg") || !strcasecmp(fileExtension, "png"))) { 
            // Ger the absolute path for the current file.
            realpath(dp->d_name, filePath);
            data = exif_data_new_from_file(filePath);
            // No exif data found so it can return here.
            if (!data) {
                return 2;
            }
            printf("File: %s; ", dp->d_name);
            show_tag(data, EXIF_IFD_0, EXIF_TAG_DATE_TIME);
        }
    }
    // Close the handle (pointer)
    closedir(dir); 
	return 1; 
}