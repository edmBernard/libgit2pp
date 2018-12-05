#include <git2pp.h>


void git_log(std::string path) {
    std::cout << "\nGIT LOG" << std::endl;

    git2pp::Session git2;
    auto repo = git2[git_repository_open](path.c_str());  // Exception on failure.

    auto walker = repo[git_revwalk_new]();
    walker[git_revwalk_sorting](GIT_SORT_NONE);
    walker[git_revwalk_push_head]();

    git_oid oid;
    while(!git_revwalk_next(&oid, &*walker))
    {
        auto commit = repo[git_commit_lookup](&oid).as<git_commit>();
        std::cout << commit[git_commit_id]() << "  " << commit[git_commit_summary]() << "\n";
    }

}

void usage() {
    std::cout << "USAGE: log-cpp <path>" << std::endl;
}

int main (int argc, char** argv)
{
    if (argc <= 1) {
        usage();
        return 1;
    }

    git_log(argv[1]);

	return 0;
}
