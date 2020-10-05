#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <map>

using namespace std;

map<string, string> g_page;
mutex g_page_mutex;

void save_page(const string& url)
{
    this_thread::sleep_for(chrono::seconds(2));
    string result = "fake content";

    lock_guard<mutex> lc(g_page_mutex);

    //或者也可以写成
    //lock(g_page_mutex);// 此函数有2个参数，此处仅作演示
    //lock_guard<mutex> lc(g_page_mutex, adopt_lock);
    //或者也可以写成
    //lock_guard<mutex> lc(g_page_mutex, defer_lock);
    //lock(g_page_mutex);// 此函数有2个参数，此处仅作演示

    g_page[url] = result;
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

