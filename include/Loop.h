#ifndef CHANNEL
#define CHANNEL

#include <Arduino.h>
#include <DeviceConfig.h>
enum ChannelID
{
    channel_A = 1,
    channel_B = 2,
    channel_C = 3,
    channel_D = 4,
    channel_E = 5,
    channel_F = 6,
    channel_G = 7,
    channel_Master = 8
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
    int leftOutputVolume;
    int rightOutputVolume;
    int pan = DEFAULT_PAN;
    bool isStereo = true;
    ChannelID channelID;
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
};
#endif // CHANNEL