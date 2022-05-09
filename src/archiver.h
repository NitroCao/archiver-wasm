#include <archive.h>
#include <archive_entry.h>
#include <emscripten/bind.h>
#include <string>
#include <vector>

namespace archiver {
using namespace emscripten;

class Archiver {
public:
    Archiver(const std::string &filename);
    ~Archiver();
    inline const std::string check_error()
    {
        std::string msg(err_msg);
        err_msg = "";
        return msg;
    }
    std::vector<std::string> list_files();

private:
    struct archive *ptr_archive;
    std::string err_msg;
};

EMSCRIPTEN_BINDINGS(archiver)
{
    class_<Archiver>("Archiver")
        .constructor<const std::string &>()
        .function("ListFiles", &Archiver::list_files)
        .function("CheckError", &Archiver::check_error);

    register_vector<std::string>("vector<string>");
}
}; // namespace archiver
