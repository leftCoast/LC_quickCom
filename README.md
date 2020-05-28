# LC_quickCom
Library for master/slave communication. ( Processor to processor over serial link )

**Depeneds on**  
[LC_baseTools](https://github.com/leftCoast/LC_baseTools)

**Master slave communicaton.** Master initiates **all** communication. Slave can **only respond** to a command. This is to keep everything in sync. And, this is the model that this library is based on.

**Message format.** The messages are 1..255 byte buffers of raw data. For those that are wondering, there's actually an initial byte that is not shown to the user. That is the number of bytes coming for the message that's on its way. Its best not to think about that, because it tends to get one all confused about how many bytes a message is etc.

**How to use this?** There are two classes qCMaster and qCSlave. Create an instance of qCMaster on your master processor and an instance of qCSlave on your slave processor. 

There are two #define(s) in quickCom.h..
```
#define MASTER_PORT	Serial1	// For now, this is all I could come up with.
#define SLAVE_PORT	Serial1	// Change these to reflect your hardware setup.
```
As it says, you will need to set these two to match your hardware setup.

These classes are both idlers. Meaning, you must call ```idle()``` in the loop() functions for both processors. It also means no delay() calls. But that's going to be fine because whatever you wanted to use delay() for can be rewritten to use the timeObj class.

Lets take the master side to begin with.
**1 :** Initialse the quickCom object calling its begin() method with the baud rate yo are going to use. This should be done in your setup() function.

**2 :** When you need to pass over a block off data; Set up a buffer with the data and call the sendBuff() method with the buffer, the number of bytes loaded in it and if a reply is desired.

**3 :** After calling sendBuff(), repeatedly call either haveBuff() if you are looking for a reply, or isSending() if you are not. haveBuff() returns the number of bytes in the reply once it has been completely received. Meaning, the reply is ready to be handled. isSending() just returns a false when the outgoing message has been completely transmitted. Meaning, the hardwaqre is ready to send the next message.
