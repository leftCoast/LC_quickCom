# LC_quickCom
Library for master/slave communication. ( Processor to processor over serial link )

**Depeneds on**  
[LC_baseTools](https://github.com/leftCoast/LC_baseTools)

**Master slave communicaton.** Master initiates **all** communication. Slave can **only respond** to a command. This is to keep everything in synk. And, this is the model that this library was based on.

**Message format.** The messages are 1..255 byte buffers of raw data. For those that are wondering, there's actually an initial byte that is not shown to the user. That is the number of bytes coming for the message that's on its way. Its best not to think about that, because it tends to get one all confused about how many bytes a message is etc.

***How to use this?*** There are two classes qCMaster and qCSlave. Create an instance of qCMaster on your master processor and an instance of qCSlave on your slave processor. 

There are two #define(s) in quickCom.h..
```
#define MASTER_PORT	Serial1	// For now, this is all I could come up with.
#define SLAVE_PORT	Serial1	// Change these to reflect your hardware setup.
```
As it says, you will need to set these to match your hardware setup.

1 

