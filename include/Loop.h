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
    void setChannelPosition(int position);
    void setInputVolume(int volume);
    void setOutputVolume(int volume);
    void setPan(int pan);
    void setIsStereo(bool isStereo);
    // Getters
    ChannelID getChannelID();
    int getChannelPosition();
    int getInputVolume();
    int getOutputVolume();
    int getPan();
    bool getIsStereo();
    int getLeftOutputVolume();
    int getRightOutputVolume();

private:
    int channelPosition = 0;
    int inputVolume = DEFAULT_VOLUME;
    int outputVolume = DEFAULT_VOLUME;
    int pan = DEFAULT_PAN;
    bool isStereo = true;
    ChannelID channelID;
    int clampVolume(int volume);
    int clampPosition(int position);
    int clampPan(int pan);
};

class Loop : public Channel
{
public:
    void setIsDelayTrail(bool isDelayTrail);
    bool getIsDelayTrail();
    void setPhase(int phase);
    int getPhase();

private:
    int phase;
    bool isDelayTrail;
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