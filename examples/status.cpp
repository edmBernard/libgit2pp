#include <git2pp.h>

void git_status(std::string path) {

    git2pp::Session git2;
    auto repo = git2[git_repository_open](path.c_str());  // Exception on failure.
    auto master = repo[git_reference_dwim]("master");
    auto commit = master[git_reference_peel](GIT_OBJ_COMMIT).as<git_commit>();
    std::cout << "master = " << commit[git_commit_id]() << "\n";
    std::cout << "author = " << commit[git_commit_author]()->name << "\n";
    std::cout << "message = " << commit[git_commit_message]() << "\n";
}

void usage() {
    std::cout << "USAGE: status-cpp <path>" << std::endl;
}

int main (int argc, char** argv)
{
    if (argc <= 1) {
        usage();
        return 1;
    }

    git_status(argv[1]);

	return 0;
}
