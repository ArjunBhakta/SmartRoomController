#ifndef _IoTTimer_H_ 
#define _IoTTimer_H_

class IoTTimer {

    unsigned int  timerStart;
    unsigned int timerTarget;

  public:
    IoTTimer() {}
    
    void startTimer( unsigned int msec) {
      timerStart = millis();
      timerTarget = msec;
    }

    bool isTimerReady() {
      return (millis() - timerStart) > timerTarget;
    }
};

#endif //_IoTTImer_H_
