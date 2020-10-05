#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <map>

using namespace std;
/*
map<string, string> g_page;
mutex g_page_mutex;

void save_page(const string& url)
{
    this_thread::sleep_for(chrono::seconds(2));
    string result = "fake content";

    g_page_mutex.lock();
    g_page[url] = result;
    g_page_mutex.unlock();
}

int main(int argc, char *argv[])
{
    thread t1(save_page, "http://foo");
    thread t2(save_page, "http://bar");
    t1.join();
    t2.join();

    for (const auto &pair : g_page)
    {
        cout << pair.first << "=>" << pair.second << endl;
    }

    return 0;
}
*/
