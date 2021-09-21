#pragma once
#include "libpq-fe.h"
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <atomic>
#include <thread>
#include <list>
#include <mutex>
#include <unordered_map>

#include "mpsapi.h"



struct ConnInfo
{
    std::string Name;
    std::string Password;
    std::string DBName;
    std::string Host;
    std::string Port;
};

struct TagInfo
{
    std::string tnumber, tagid, ttype, wrenable, attrid, val, atype, aname, description;
};


class PgDataManager
{
private:
    const std::string _separator = "_";
    std::unique_ptr<PGconn, std::function<void(PGconn*)>> _conn;
    OpcMP_plugin_t* _plugin;
    std::unordered_map<std::string, OpcMP_tag_t*> _tagmap;
    std::vector<TagInfo> GetTags();
    void GetTagValue(time_t start, time_t end, const std::string& tnumber, int Type);

    void CreateTag(const TagInfo& taginfo);

    class Scheduler
    {
        struct Task
        {
            time_t start, end;
            std::shared_ptr<Task> nextTask;
        };
        std::mutex _mutex;
        std::shared_ptr<Task> _task;
        std::atomic<bool> _isworking;
        std::atomic<int> _counter;
        time_t _lastUpdate;
        const time_t _period;
        const int _threadNum;
        const std::vector<TagInfo> _updateList;
        const decltype(&GetTagValue) _fn;
        public:
        Scheduler(time_t start, time_t period, int threadNumber, const std::vector<TagInfo>& tags, decltype(&GetTagValue) function);
        void run();
        void Work();
    };

public:

    PgDataManager(const ConnInfo& info);
};