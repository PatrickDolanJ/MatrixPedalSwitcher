#ifndef CHANNEL
#define CHANNEL

#include <Arduino.h>
#include <DeviceConfig.h>
enum ChannelID
{
    channel_A = 0,
    channel_B = 1,
    channel_C = 2,
    channel_D = 3,
    channel_E = 4,
    channel_F = 5,
    channel_G = 6,
    channel_Master = 7
};

class Channel
{
public:
    Channel();
    // Setters
    void setChannelID(ChannelID id);
    void setInputVolume(int volume);
    void setOutputVolume(int volume);
    void setPan(int pan);
    void setIsStereo(bool isStereo);
    // Getters
    ChannelID getChannelID();
    int getInputVolume();
    int getOutputVolume();
    int getPan();
    bool getIsStereo();
    int getLeftOutputVolume();
    int getRightOutputVolume();

private:
    int inputVolume = DEFAULT_VOLUME;
    int outputVolume = DEFAULT_VOLUME;
    int pan = DEFAULT_PAN;
    bool isStereo = true;
    ChannelID channelID;
    int clampPan(int pan);
    int clampVolume(int volume);
};

class Loop : public Channel
{
public:
    void setIsDelayTrail(bool isDelayTrail);
    bool getIsDelayTrail();
    void setPhase(int phase);
    int getPhase();
    void setChannelPosition(int position);
    int getChannelPosition();

private:
    int phase;
    bool isDelayTrail;
    int channelPosition = 0;
    int clampPosition(int position);
};

class Master : public Channel
{
public:
    void setSendDry(int id);
    int getSendDry();

private:
    int sendDry;
    int clampDrySend(int drySend);
};
#endif // CHANNEL