# LC_quickCom
Library for master/slave communication. ( IE : Processor to processor over serial link )

**Depends on**  
[LC_baseTools](https://github.com/leftCoast/LC_baseTools)

**Master slave communicaton.** Master initiates **all** communication. Slave can **only respond** to a command. This is to keep everything in sync. And, this is the model that this library is based on.

**Message format.** The messages are 1..255 byte buffers of raw data. For those that are wondering, there's actually an initial byte that is not shown to the user. That is the number of bytes being transmitted. It's best not to think about that, because it tends to get one all confused about how many bytes a message is etc.

**How to use this?** There are two classes qCMaster and qCSlave. Create an instance of qCMaster on your master processor and an instance of qCSlave on your slave processor. 

There are two #define(s) in quickCom.h..
```
#define MASTER_PORT	Serial1	// For now, this is all I could come up with.
#define SLAVE_PORT	Serial1	// Change these to reflect your hardware setup.
```
As it says, you will need to set these two to match your hardware setup.

These classes are both idlers. Meaning, you must call idle() in the loop() functions for both processors. It also means **no delay() calls**. But that's going to be fine, because whatever you wanted to use delay() for, can be rewritten using sleep(). Sleep? Yes, sleep() comes as part of the LC_baseTool library that this is all based on. It will "delay()" your loop() code while letting all this other stuff run in the background. Pretty slick huh?

**Master class** standard operation.  


**1 :** Create a quickCom master class instance.  
```qCMaster ourCom;```

**2 :** Initialize the quickCom object calling its begin() method with the baud rate to use. This should be done in your setup() function.  
```ourCom.begin();```

**3 :** When you need to pass over a block of data; Set up a buffer with the data and call the sendBuff() method with the buffer, the number of bytes loaded in it and if a reply is desired. This just starts the comminication, the program can go off and do whatever it needs to do while this transaction is running.  
```sendBuff(buffPtr,numBytes,wantReply);```

**4 :** After calling sendBuff(), repeatedly call either haveBuff(), if you are looking for a reply, or isSending() if you are not. haveBuff() returns the number of bytes in the reply once it has been completely received. Meaning, the reply is ready to be handled. isSending() just returns a false when the outgoing message has been completely transmitted. Meaning, the hardwaqre is ready to send the next message.  

```if (ourCom.haveBuff()) { handleReply(); }```  

Or, if no reply has been asked for..  

```if (!ourCom.isSending()) { readdyToSend = true; }```  


**Slave class** standard operation.

**1 :** Create a quickCom slave class instance.  
```qCSlave ourCom;```

**2 :** Initialize the quickCom object calling it's begin() method with the address of the message buffer, the number of bytes that the message buffer can hold and the baud rate to use.  This is usualy done in your setup() function.  
```ourCom.begin(buffPtr,numBytes,baud);```  

**3 :** Being a slave, its main job is to listen for the commands of its master. Therefor the usual practice is to call the com object's haveBuff() method repeatedly in the main loop() function.  

```if (ourCom.haveBuff()) { handleCommand(); }```   

**4 :** When handling a command either a reply will have to be returnd by calling the replyComBuff() method with the number of bytes to send back. Or, if no reply is to be returned, slaveReset() must be called to reset to listening for commands.  

```ourCom.replyComBuff(numBytes);```  

Or if now reply is desired..  

```ourCom.slaveReset();```   

**But what about the reply buffer?** There is only one buffer used in the slave version. It must be sized to hold the maximum length of any command or reply. One reads the command data out of this buffer, then writes the reply over the top of this data before sending it back. It's written like this to keep the slave's RAM footprint minimized.


And that's about it for the slave side. Listen for commands, deal with commands. Boring life.  



# LC_commonComs

While writing code for talking from one processor to another, there are a number of things that one runs into over and over. As an example.. Send out a one byte command and expect a byte, int, float, string to be returned. Wouldn't it be nice if we could just do all this in one method? Drop in a one byte command and it returns the result. That's what commonComs is all about.

**How to use this?** commonComs is derived from qCMaster. It has all the qCMaster calls, but it also adds some easy to use methods.   

**1 :** Create your commonComs object.  
```commonComs ourCom;```  

**2 :** Call the commonComs begin() during setup() with the baud rate to use.  
```ourCom.begin(baud);```  

**3 :** Use the commonComs methods to retrieve the types of data your slave processor is setup for.  

```
bool  getByte(byte com,byte* reply);
bool  getInt(byte com,int* reply);
bool  getFloat(byte com,float* reply);
bool  getLong(byte com,long* reply);
bool  getUnsignedLong(byte com,unsigned long* reply);
bool  getCString(byte com,char* reply);
bool  sendCommand(byte com);
```  

All the methods assume your slave processor can repond to single byte commands, but that's not too uncommon. You supply the command byte and a pointer to the kind of reply expected. The methods return true for a successful action. False for an error. If there is to be no reply, the sendCommand() method is suppied for just this purpose.

These methods, if called in your loop() function, will actually block your loop() while they execute. But, they will **not** block all your idlers from running in the background. In this way much of your application will continue to function. Unlike delay(), where ***everything*** stops.

**NOTE :** Be sure both processors agree on the size and ordering of the bytes for the varibles you choose to use.


