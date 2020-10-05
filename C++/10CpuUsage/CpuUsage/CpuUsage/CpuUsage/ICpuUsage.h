#ifndef ICPUUSAGE_H
#define ICPUUSAGE_H

class  ICpuUsage
{
public:
    virtual ~ICpuUsage() {}
    virtual int init() = 0;
    virtual int getNumberProcessors() = 0;
    virtual int getUseage(size_t processorId) = 0;
    virtual void calProcessorsUses() = 0;
    virtual float getTemperature(int socketNo) = 0;
    virtual int    getSocketCount() = 0;
};

#endif // ICPUUSAGE_H
