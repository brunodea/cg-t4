#ifndef _BRUNODEA_CONTROLLER_H_
#define _BRUNODEA_CONTROLLER_H_

class Controller
{
public:
    static Controller *instance();

    void run();

    void onKeyPressed(int key, int state);

private:
    Controller();

    void onUpdate();
    void onRender();
    
private:
    static Controller *m_sInstance;

    bool m_bRunning;
}; //end of class Controller

#endif
