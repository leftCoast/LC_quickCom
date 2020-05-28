#ifndef commonComs_h
#define commonComs_h

// quickCom, While writing code for talking from one processor to another, there are a
// number of things that one runs into over and over. Send back a string, or an int. Just
// sent a one byte command. It seemed like a good idea to make up a set of common
// commands and code them once an for all. 
//
// Here they are.


#include "quickCom.h"

#define QCOM_SLEEP_TIME		2	// When looking for an answer, rest this long (ms) before peeking.
#define QCOM_REPLY_TIMEOUT	75	// How long (ms) they get to give back a reply.


// *****************************************************
//                    commonComs
// *****************************************************


class commonComs :  public qCMaster {

  public:
                commonComs(void);
  virtual       ~commonComs(void);

  virtual bool  getByte(byte com,byte* reply);
  virtual bool  getInt(byte com,int* reply);
  virtual bool  getFloat(byte com,float* reply);
  virtual bool  getLong(byte com,long* reply);
  virtual bool  getUnsignedLong(byte com,unsigned long* reply);
  virtual bool  getCString(byte com,char* reply);
  virtual bool  sendCommand(byte com);

  //protected:
          void  sleep(int ms);
          
          timeObj       mSleepTimer;
};


#endif