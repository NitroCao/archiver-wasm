#include "archiver.h"

namespace archiver {
Archiver::Archiver(const std::string &filename)
{
    ptr_archive = archive_read_new();
    archive_read_support_filter_all(ptr_archive);
    archive_read_support_format_all(ptr_archive);

    if (archive_read_open_filename(ptr_archive, filename.c_str(), 10240) != ARCHIVE_OK)
        err_msg = "Failed to open archive file";
}

Archiver::~Archiver()
{
    if (!ptr_archive && archive_read_free(ptr_archive) != ARCHIVE_OK)
        err_msg = "Failed to close archive file";
}

std::vector<std::string> Archiver::list_files()
{
    std::vector<std::string> results;
    struct archive_entry *entry;

    while (archive_read_next_header(ptr_archive, &entry) == ARCHIVE_OK) {
        results.emplace_back(archive_entry_pathname(entry));
    }

    return results;
}

}; // namespace archiver
