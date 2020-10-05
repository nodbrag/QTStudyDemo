#ifndef __DOWNLOADLISTCONFIG_H__
#define __DOWNLOADLISTCONFIG_H__
#include <string>
#include <list>

class TiXmlDocument;
class TiXmlElement;

typedef struct
{
    std::string name;
    std::string path;
    unsigned int progress;
    bool succeed;
}FileInfo;

class DownloadListConfig
{
public:
    DownloadListConfig(const char* xmlFile);
    ~DownloadListConfig();

    // 存储为文件
    bool saveFile();

    // 增加一条记录
    bool addInfo(const FileInfo& info);

    // 删除一条记录
    bool deleteInfo(const char* file);

    // 修改一条记录
    bool modifyInfo(const FileInfo& info);

    // 获取一条记录
    bool getInfo(const char* file, FileInfo* info);

    // 获得所有记录
    bool getAllInfo(std::list<FileInfo>* infoList);

    // 获得记录总条数
    int getCount();

private:
    std::string fileName;
    TiXmlDocument* pDoc;
    TiXmlElement* pRoot;
};

#endif // DOWNLOADLISTCONFIG_H
