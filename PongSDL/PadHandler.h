#ifndef USE_PADHANDLER
#define USE_PADHANDLER
struct AllButtons{
    bool up=false;
    bool down=false;
    bool left=false;
    bool right=false;
    bool cross=false;
    bool square=false;
    bool circle=false;
    bool triangle=false;
    bool select=false;
    bool start=false;
    bool l1=false;
    bool l2=false;
    bool r1=false;
    bool r2=false;
    bool l3=false;
    bool r3=false;
};
void PadInit();
AllButtons* PadGetInputs();
#endif