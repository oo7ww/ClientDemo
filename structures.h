#ifndef STRUCTURES
#define STRUCTURES

typedef struct{
    int roomNum;
    double roomTmp;
    double targetTmp;
    int windSpeed;
    bool power;
    bool isServed;
    int mode;
    double defRoomTmp;
    double Kwh;
    double fee;
    double highestTmp;
    double lowestTmp;
}PacketInfo;


#endif // STRUCTURES

