#ifndef CHANNEL
#define CHANNEL

#include <Arduino.h>
enum ChannelID
{
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    F = 6,
    G = 7,
    Master = 8
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
    int channelPosition;
    int inputVolume;
    int outputVolume;
    int leftOutputVolume;
    int rightOutputVolume;
    int pan;
    bool isStereo;
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