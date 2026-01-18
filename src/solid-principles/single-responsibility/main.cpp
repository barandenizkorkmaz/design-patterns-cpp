#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Journal{
    string title;
    vector<string> entries;

    Journal(const string& title) : title(title) {}

    void add_entry(const string& entry){
        static int count = 1;
        entries.push_back(to_string(count++) + ": " + entry);
    }
};

struct PersistenceManager{
    static void save(const Journal& j, const string& filename){
        // Code to save journal to a file would go here
    
        ofstream ofs(filename);
        for (const auto& entry : j.entries) {
            ofs << entry << endl;
        }
    }
};

int main() {
    Journal journal("My Journal");
    journal.add_entry("I cried today.");
    journal.add_entry("I ate a bug.");

    PersistenceManager::save(journal, "journal.txt");

    return 0;
}