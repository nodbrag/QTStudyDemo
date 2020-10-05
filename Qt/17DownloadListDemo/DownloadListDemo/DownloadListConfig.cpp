#include "DownloadListConfig.h"
#include "tinyXml/tinyxml.h"
#include <QFile>

// xml节点及属性信息
#define XML_ROOT                  "DownloadList"
#define XML_FILE                  "file"
#define ATTRIBUTE_NAME            "name"
#define ATTRIBUTE_PROGRESS        "progress"
#define ATTRIBUTE_SUCCEED         "succeed"
#define ATTRIBUTE_PATH            "path"

DownloadListConfig::DownloadListConfig(const char* xmlFile)
{
    fileName = xmlFile;

    // 创建document对象
    pDoc = new TiXmlDocument();
    TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "utf-8", "");
    pDoc->LinkEndChild(declaration);

    QFile file;
    if (file.exists(xmlFile)) // 存在
    {
        pDoc->LoadFile(xmlFile);
        pRoot = pDoc->FirstChildElement();
    }
    else // 不存在
    {
        // 创建根节点
        pRoot = new TiXmlElement(XML_ROOT);
        pDoc->LinkEndChild(pRoot);
    }
}

DownloadListConfig::~DownloadListConfig()
{
    if (pDoc != NULL)
    {
        pDoc->SaveFile(fileName.c_str());
        delete pDoc;
        pDoc = NULL;
        pRoot = NULL;
    }
}

bool DownloadListConfig::saveFile()
{
    return pDoc->SaveFile(fileName.c_str());
}

bool DownloadListConfig::addInfo(const FileInfo& info)
{
    TiXmlElement* node = new TiXmlElement(XML_FILE);
    pRoot->LinkEndChild(node);
    node->SetAttribute(ATTRIBUTE_NAME, info.name.c_str());
    node->SetAttribute(ATTRIBUTE_PROGRESS, info.progress);
    node->SetAttribute(ATTRIBUTE_SUCCEED, info.succeed?"true":"false");
    node->SetAttribute(ATTRIBUTE_PATH, info.path.c_str());
    return true;
}

bool DownloadListConfig::deleteInfo(const char* file)
{
    TiXmlElement* node = NULL;
    for (node = pRoot->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
    {
        if (strcmp(node->Attribute(ATTRIBUTE_NAME), file) == 0)
        {
            pRoot->RemoveChild(node);
            break;
        }
    }
    return true;
}

bool DownloadListConfig::modifyInfo(const FileInfo& info)
{
    TiXmlElement* node = NULL;
    for (node = pRoot->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
    {
        if (info.name == node->Attribute(ATTRIBUTE_NAME))
        {
            node->SetAttribute(ATTRIBUTE_NAME, info.name.c_str());
            node->SetAttribute(ATTRIBUTE_PROGRESS, info.progress);
            node->SetAttribute(ATTRIBUTE_SUCCEED, info.succeed?"true":"false");
            node->SetAttribute(ATTRIBUTE_PATH, info.path.c_str());
            return true;
        }
    }

    // 未找到，就增加
    return addInfo(info);
}

bool DownloadListConfig::getInfo(const char* file, FileInfo* info)
{
    TiXmlElement* node = NULL;
    for (node = pRoot->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
    {
        if (strcmp(node->Attribute(ATTRIBUTE_NAME), file) == 0)
        {
            info->name = node->Attribute(ATTRIBUTE_NAME);
            info->path = node->Attribute(ATTRIBUTE_PATH);
            int progress = 0;
            node->Attribute(ATTRIBUTE_PROGRESS, &progress);
            info->progress = progress;
            info->succeed = strcmp(node->Attribute(ATTRIBUTE_SUCCEED), "true") == 0;
            return true;
        }
    }
    return false;
}

bool DownloadListConfig::getAllInfo(std::list<FileInfo>* infoList)
{
    TiXmlElement* node = NULL;
    for (node = pRoot->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
    {
        FileInfo info;

        info.name = node->Attribute(ATTRIBUTE_NAME);
        info.path = node->Attribute(ATTRIBUTE_PATH);
        int progress = 0;
        node->Attribute(ATTRIBUTE_PROGRESS, &progress);
        info.progress = progress;
        info.succeed = strcmp(node->Attribute(ATTRIBUTE_SUCCEED), "true") == 0;

        infoList->push_back(info);
    }
    return true;
}

int DownloadListConfig::getCount()
{
    int count = 0;
    for (TiXmlElement* node = pRoot->FirstChildElement(); node != NULL; node = node->NextSiblingElement())
    {
        count++;
    }
    return count;
}
