#include <SoftwareSerial.h>

#define UCHAR unsigned char

#define rxPin 2
#define txPin 3
#define rtsPin 4
#define lcdPin 7
#define ledPin 13

int heartrate = 0;
// set up a new serial port
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
SoftwareSerial lcdSerial =  SoftwareSerial(6, lcdPin);
byte pinState = 0;

#define RETURN_ERROR   -1
#define RETURN_SUCCESS    0 
#define DEBUG       1 


#define MESG_TX_SYNC                      ((UCHAR)0xA4)
//#define MESG_RX_SYNC                      ((UCHAR)0xA5)
#define MESG_SIZE_OFFSET                  ((UCHAR)1)    
#define MESG_ID_OFFSET                    ((UCHAR)2)     
#define MESG_SYNC_SIZE                    ((UCHAR)1)
#define MESG_SIZE_SIZE                    ((UCHAR)1)
#define MESG_ID_SIZE                      ((UCHAR)1)
#define MESG_CHECKSUM_SIZE                ((UCHAR)1)
#define MESG_MAX_DATA_SIZE                ((UCHAR)17)
#define MESG_HEADER_SIZE                  (MESG_SYNC_SIZE + MESG_SIZE_SIZE + MESG_ID_SIZE)
#define MESG_DATA_OFFSET                  MESG_HEADER_SIZE  
#define MESG_FRAME_SIZE                   (MESG_HEADER_SIZE + MESG_CHECKSUM_SIZE)
#define MESG_MAX_SIZE                     (MESG_MAX_DATA_SIZE + MESG_FRAME_SIZE)

//////////////////////////////////////////////

// Message ID's

//////////////////////////////////////////////
#define MESG_INVALID_ID                   ((UCHAR)0x00)
#define MESG_EVENT_ID                     ((UCHAR)0x01)
#define MESG_VERSION_ID                   ((UCHAR)0x3E)  // protocol library version
#define MESG_RESPONSE_EVENT_ID            ((UCHAR)0x40)
#define MESG_UNASSIGN_CHANNEL_ID          ((UCHAR)0x41)
#define MESG_ASSIGN_CHANNEL_ID            ((UCHAR)0x42)
#define MESG_CHANNEL_MESG_PERIOD_ID       ((UCHAR)0x43)
#define MESG_CHANNEL_SEARCH_TIMEOUT_ID    ((UCHAR)0x44)
#define MESG_CHANNEL_RADIO_FREQ_ID        ((UCHAR)0x45)
#define MESG_NETWORK_KEY_ID               ((UCHAR)0x46)
#define MESG_RADIO_TX_POWER_ID            ((UCHAR)0x47)
#define MESG_RADIO_CW_MODE_ID             ((UCHAR)0x48)
#define MESG_SEARCH_WAVEFORM_ID           ((UCHAR)0x49)
#define MESG_SYSTEM_RESET_ID              ((UCHAR)0x4A)
#define MESG_OPEN_CHANNEL_ID              ((UCHAR)0x4B)
#define MESG_CLOSE_CHANNEL_ID             ((UCHAR)0x4C)
#define MESG_REQUEST_ID                   ((UCHAR)0x4D)
#define MESG_BROADCAST_DATA_ID            ((UCHAR)0x4E)
#define MESG_ACKNOWLEDGED_DATA_ID         ((UCHAR)0x4F)
#define MESG_BURST_DATA_ID                ((UCHAR)0x50)
#define MESG_CHANNEL_ID_ID                ((UCHAR)0x51)
#define MESG_CHANNEL_STATUS_ID            ((UCHAR)0x52)
#define MESG_RADIO_CW_INIT_ID             ((UCHAR)0x53)
#define MESG_CAPABILITIES_ID              ((UCHAR)0x54)
#define MESG_NVM_DATA_ID                  ((UCHAR)0x56)
#define MESG_NVM_CMD_ID                   ((UCHAR)0x57)
#define MESG_NVM_STRING_ID                ((UCHAR)0x58)
#define MESG_ID_LIST_ADD_ID               ((UCHAR)0x59)
#define MESG_ID_LIST_CONFIG_ID            ((UCHAR)0x5A)
#define MESG_OPEN_RX_SCAN_ID              ((UCHAR)0x5B)
#define MESG_EXT_CHANNEL_RADIO_FREQ_ID    ((UCHAR)0x5C)
#define MESG_EXT_BROADCAST_DATA_ID        ((UCHAR)0x5D)
#define MESG_EXT_ACKNOWLEDGED_DATA_ID     ((UCHAR)0x5E)
#define MESG_EXT_BURST_DATA_ID            ((UCHAR)0x5F)
#define MESG_CHANNEL_RADIO_TX_POWER_ID    ((UCHAR)0x60)
#define MESG_GET_SERIAL_NUM_ID            ((UCHAR)0x61)
#define MESG_GET_TEMP_CAL_ID              ((UCHAR)0x62)
#define MESG_SET_LP_SEARCH_TIMEOUT_ID     ((UCHAR)0x63)
#define MESG_SET_TX_SEARCH_ON_NEXT_ID     ((UCHAR)0x64)
#define MESG_SERIAL_NUM_SET_CHANNEL_ID_ID ((UCHAR)0x65)
#define MESG_RX_EXT_MESGS_ENABLE_ID       ((UCHAR)0x66)
#define MESG_RADIO_CONFIG_ALWAYS_ID       ((UCHAR)0x67)
#define MESG_ENABLE_LED_FLASH_ID          ((UCHAR)0x68)
#define MESG_AGC_CONFIG_ID                ((UCHAR)0x6A)
#define MESG_READ_SEGA_ID                 ((UCHAR)0xA0)
#define MESG_SEGA_CMD_ID                  ((UCHAR)0xA1)
#define MESG_SEGA_DATA_ID                 ((UCHAR)0xA2)
#define MESG_SEGA_ERASE_ID                ((UCHAR)0XA3)   
#define MESG_SEGA_WRITE_ID                ((UCHAR)0XA4)

//                                        ((UCHAR)0xA5) //FREE

#define MESG_SEGA_LOCK_ID                 ((UCHAR)0xA6)
#define MESG_FUSECHECK_ID                 ((UCHAR)0xA7)
#define MESG_UARTREG_ID                   ((UCHAR)0XA8)
#define MESG_MAN_TEMP_ID                  ((UCHAR)0xA9)
#define MESG_BIST_ID                      ((UCHAR)0XAA)
#define MESG_SELFERASE_ID                 ((UCHAR)0XAB)
#define MESG_SET_MFG_BITS_ID              ((UCHAR)0xAC)
#define MESG_UNLOCK_INTERFACE_ID          ((UCHAR)0xAD)
#define MESG_IO_STATE_ID                  ((UCHAR)0xB0)
#define MESG_CFG_STATE_ID                 ((UCHAR)0xB1)
#define MESG_RSSI_ID                      ((UCHAR)0xC0)
#define MESG_RSSI_BROADCAST_DATA_ID       ((UCHAR)0xC1)
#define MESG_RSSI_ACKNOWLEDGED_DATA_ID    ((UCHAR)0xC2)
#define MESG_RSSI_BURST_DATA_ID           ((UCHAR)0xC3)
#define MESG_RSSI_SEARCH_THRESHOLD_ID     ((UCHAR)0xC4)
#define MESG_BTH_BROADCAST_DATA_ID        ((UCHAR)0xD0)
#define MESG_BTH_ACKNOWLEDGED_DATA_ID     ((UCHAR)0xD1)
#define MESG_BTH_BURST_DATA_ID            ((UCHAR)0xD2)
#define MESG_BTH_EXT_BROADCAST_DATA_ID    ((UCHAR)0xD3)
#define MESG_BTH_EXT_ACKNOWLEDGED_DATA_ID ((UCHAR)0xD4)
#define MESG_BTH_EXT_BURST_DATA_ID        ((UCHAR)0xD5)

//////////////////////////////////////////////

// Message Sizes

//////////////////////////////////////////////

#define MESG_INVALID_SIZE                 ((UCHAR)0)
#define MESG_RESPONSE_EVENT_SIZE          ((UCHAR)3)
#define MESG_CHANNEL_STATUS_SIZE          ((UCHAR)2)
#define MESG_VERSION_SIZE                 ((UCHAR)9)
#define MESG_UNASSIGN_CHANNEL_SIZE        ((UCHAR)1)
#define MESG_ASSIGN_CHANNEL_SIZE          ((UCHAR)3)
#define MESG_CHANNEL_ID_SIZE              ((UCHAR)5)
#define MESG_CHANNEL_MESG_PERIOD_SIZE     ((UCHAR)3)
#define MESG_CHANNEL_SEARCH_TIMEOUT_SIZE  ((UCHAR)2)
#define MESG_CHANNEL_RADIO_FREQ_SIZE      ((UCHAR)2)
#define MESG_NETWORK_KEY_SIZE             ((UCHAR)9)
#define MESG_RADIO_TX_POWER_SIZE          ((UCHAR)2)
#define MESG_RADIO_CW_MODE_SIZE           ((UCHAR)3)
#define MESG_RADIO_CW_INIT_SIZE           ((UCHAR)1)
#define MESG_SEARCH_WAVEFORM_SIZE         ((UCHAR)3)
#define MESG_SYSTEM_RESET_SIZE            ((UCHAR)1)
#define MESG_OPEN_CHANNEL_SIZE            ((UCHAR)1)
#define MESG_CLOSE_CHANNEL_SIZE           ((UCHAR)1)
#define MESG_REQUEST_SIZE                 ((UCHAR)2)
#define MESG_CAPABILITIES_SIZE            ((UCHAR)6)
#define MESG_DATA_SIZE                    ((UCHAR)9)
#define MESG_NVM_DATA_SIZE                ((UCHAR)10)
#define MESG_NVM_CMD_SIZE                 ((UCHAR)3)
#define MESG_NVM_STRING_SIZE              ((UCHAR)9)
#define MESG_ID_LIST_ADD_SIZE             ((UCHAR)6)
#define MESG_ID_LIST_CONFIG_SIZE          ((UCHAR)3)
#define MESG_OPEN_RX_SCAN_SIZE            ((UCHAR)1)
#define MESG_EXT_CHANNEL_RADIO_FREQ_SIZE  ((UCHAR)3)
#define MESG_EXT_DATA_SIZE                ((UCHAR)13)
#define MESG_RADIO_CONFIG_ALWAYS_SIZE     ((UCHAR)2)
#define MESG_RX_EXT_MESGS_ENABLE_SIZE     ((UCHAR)2)
#define MESG_SET_TX_SEARCH_ON_NEXT_SIZE   ((UCHAR)2)
#define MESG_SET_LP_SEARCH_TIMEOUT_SIZE   ((UCHAR)2)
#define MESG_SERIAL_NUM_SET_CHANNEL_ID_SIZE ((UCHAR)3)
#define MESG_ENABLE_LED_FLASH_SIZE        ((UCHAR)2)
#define MESG_GET_SERIAL_NUM_SIZE          ((UCHAR)4)
#define MESG_GET_TEMP_CAL_SIZE            ((UCHAR)4)
#define MESG_AGC_CONFIG_SIZE              ((UCHAR)2)
#define MESG_READ_SEGA_SIZE               ((UCHAR)2)
#define MESG_SEGA_CMD_SIZE                ((UCHAR)3)
#define MESG_SEGA_DATA_SIZE               ((UCHAR)10)
#define MESG_SEGA_ERASE_SIZE              ((UCHAR)0)
#define MESG_SEGA_WRITE_SIZE              ((UCHAR)3)
#define MESG_SEGA_LOCKED_SIZE             ((UCHAR)1)
#define MESG_SEGA_LOCK_SIZE               ((UCHAR)0)
#define MESG_FUSECHECK_SIZE               ((UCHAR)1)
#define MESG_UARTREG_SIZE                 ((UCHAR)2)
#define MESG_MAN_TEMP_SIZE                ((UCHAR)2)
#define MESG_BIST_SIZE                    ((UCHAR)6)
#define MESG_SELFERASE_SIZE               ((UCHAR)2)
#define MESG_SET_MFG_BITS_SIZE            ((UCHAR)2)
#define MESG_UNLOCK_INTERFACE_SIZE        ((UCHAR)1)
#define MESG_IO_STATE_SIZE                ((UCHAR)2)
#define MESG_CFG_STATE_SIZE               ((UCHAR)2)
#define MESG_RSSI_SIZE                    ((UCHAR)3)
#define MESG_RSSI_DATA_SIZE               ((UCHAR)17)
#define MESG_RSSI_SEARCH_THRESHOLD_SIZE   ((UCHAR)2)

#define RETURN_ERROR   -1
#define RETURN_SUCCESS    0 
#define DEBUG       1 
// Ant Stuff
#define MAXMSG       14 // SYNC,LEN,MSG,data[8],CHKSUM
#define CHAN0      0
#define CHAN1      1
#define NET0      0
#define NET1      1
#define TIMEOUT   10 //mikec  30

#define BAUD   4800   // Sparkfun ANT Default Baud

//#define FREQ      0x41;   // Suunto radio frequency
#define FREQ 0x39; //  garmin radio frequency
//#define PERIOD      0x199a; // Suunto search period
#define PERIOD      0x1f86; // Garmin search period
//#define NETWORK_KEY      "B9AD3228757EC74D" // Suunto HRM
#define NETWORK_KEY      "B9A521FBBD72C345" // Garmin HRM

// Macros
#define hexval(c) ((c >= '0' && c <= '9') ? (c-'0') : ((c&0xdf)-'A'+10))

#define TRUE                           1
#define FALSE                          0

#if !defined(NULL)
   #define NULL                        ((void *) 0)
#endif

#define MAX_UCHAR                      0xFF
#define MAX_SCHAR                      0x7F
#define MIN_SCHAR                      0x80

#define MAX_SHORT                      0x7FFF
#define MIN_SHORT                      0x8000
#define MAX_USHORT                     0xFFFF
#define MAX_SSHORT                     0x7FFF
#define MIN_SSHORT                     0x8000

#define MAX_LONG                       0x7FFFFFFF
#define MIN_LONG                       0x80000000
#define MAX_ULONG                      0xFFFFFFFF
#define MAX_SLONG                      0x7FFFFFFF
#define MIN_SLONG                      0x80000000

// GLOBAL VARIABLES
///////////////////
UCHAR rxBuf[MAXMSG];

#define CHAN_TYPE 0x00

UCHAR checkSum(UCHAR *data, int length)
{
   int i;
   UCHAR chksum = data[0]; 
   
   for (i = 1; i < length; i++)
      chksum ^= data[i];  // +1 since skip prefix sync code, we already counted it
   
   return chksum;
}

 
int hstr2hex(UCHAR *hex, char *hexstr, int size)
{
   int i;
   
   if ((size % 2) != 0)
   {
      Serial.println("hstr2hex error: input hex string has to be divisible by 2");
      exit(RETURN_ERROR);
   }

   for (i=0; i < (size/2); i++)
   {
      hex[i] = hexval(hexstr[i*2])*16 + hexval(hexstr[i*2 + 1]);
   }
   
   return RETURN_SUCCESS;
}


void ANT_Reset (void) 
{
   uint8_t i;
   unsigned char buf[5];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x01; // LENGTH Byte
   buf[2] = 0x4a; //MESG_SYSTEM_RESET_ID; // ID Byte
   buf[3] = 0x00; // Data Byte N (N=LENGTH)
//   buf[4] = checkSum(buf,4);
   buf[4] = (0xa4^0x01^0x4a^0x00);
        
   Serial.print("Reset: ");
   for(i = 0 ; i < 5 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}


void ANT_AssignChannel(unsigned char chan) 
{
   uint8_t i;
   unsigned char buf[7];
   
   buf[0] = 0xa4; // SYNC Byte
   buf[1] = 0x03; // LENGTH Byte
   buf[2] = 0x42; //MESG_ASSIGN_CHANNEL_ID; // ID Byte
   buf[3] = chan; // channel number
   buf[4] = 0x00; //CHAN_TYPE; // channel type recieve channel
   buf[5] = 0x00; //NET0; // network number
   buf[6] = (0xa4^0x03^0x42^chan^0x00^0x00); //checkSum(buf,6);
   
   Serial.print("Assign Channel: ");
   for(i = 0 ; i < 7 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}


// assign channel id
void ANT_SetChannelID(unsigned char chan, unsigned char deviceType) 
{
   uint8_t i;
   unsigned char buf[9];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x05; // LENGTH Byte
   buf[2] = 0x51; //MESG_ASSIGN_CHANNEL_ID; // ID Byte
   buf[3] = chan; //channel number
   buf[4] = 0x00; // device number
   buf[5] = 0x00; // pairing bit  
   buf[6] = deviceType; // device ID
   buf[7] = 0x00; // transmisison type
//   buf[8] = (0xa4^0x05^0x51^chan^0x00^0x00^deviceType^0x00); 
   buf[8] = checkSum(buf,8); 
   
   Serial.print("Set Channel ID: ");
   for(i = 0 ; i < 9 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}



void ANT_SetNetworkKey(unsigned char chan) 
{
   uint8_t i;
   unsigned char buf[13];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x09; // LENGTH Byte
   buf[2] = 0x46; //MESG_NETWORK_KEY_ID; // ID Byte
   buf[3] = chan;
   //buf[3] = NET0;
   //hstr2hex(&buf[4], NETWORK_KEY, 16);  
   // 8 data fields
   // GARMIN KEY
   buf[4] = 0xB9;
   buf[5] = 0xA5;
   buf[6] = 0x21;
   buf[7] = 0xFB;
   buf[8] = 0xBD;
   buf[9] = 0x72;
   buf[10] = 0xC3;
   buf[11] = 0x45;
   buf[12] = (0xa4^0x09^0x46^chan^0xb9^0xa5^0x21^0xfb^0xbd^0x72^0xc3^0x45); //checkSum(buf,12);
   
   Serial.print("Set Network Key: ");
   for(i = 0 ; i < 13 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}


void ANT_SetChannelSearchTimeout(unsigned char chan) 
{
   uint8_t i;
   unsigned char buf[6];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x02; // LENGTH Byte
   buf[2] = 0x44; //MESG_CHANNEL_SEARCH_TIMEOUT_ID; // ID Byte
   buf[3] = chan;
   buf[4] = 0xff;  
   //buf[4] = 0x1e;
   buf[5] = (0xa4^0x02^0x44^chan^0xff); //checkSum(buf,5);
   
   Serial.print("Channel Search Timeout: ");
   for(i = 0 ; i < 6 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}


//ANT_send(1+2, MESG_CHANNEL_RADIO_FREQ_ID, CHAN0, FREQ);    
void ANT_SetChannelRFFreq(unsigned char chan) 
{
   uint8_t i;
   unsigned char buf[6];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x02; // LENGTH Byte
   buf[2] = 0x45; //MESG_CHANNEL_RADIO_FREQ_ID; // ID Byte
   buf[3] = chan; 
   // GARMIN FREQ
   buf[4] = 0x39;  
   buf[5] = (0xa4^0x02^0x45^chan^0x39); //checkSum(buf,5);
   
   Serial.print("Channel Freq: ");
   for(i = 0 ; i < 6 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}


void ANT_SetChannelPeriod(unsigned char chan, unsigned char device) 
{
   uint8_t i;
   unsigned char buf[7];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x03; // LENGTH Byte
   buf[2] = 0x43; //MESG_CHANNEL_MESG_PERIOD_ID; // ID Byte
   buf[3] = chan;
   buf[4] = device;
   buf[5] = 0x1f;
   //buf[6] = (0xa4^0x03^0x43^chan^device^0x1f);
   // GARMIN PERIOD 0x1f86 
   //buf[4] = ((int)0x1f86) % 256;   
   //buf[5] = ((int)0x1f86) / 256;  
   buf[6] = checkSum(buf,6);
   
   Serial.print("Channel Period: ");
   for(i = 0 ; i < 7 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}

//ANT_send(1+1, MESG_OPEN_CHANNEL_ID, CHAN0);   // MESG_OPEN_CHANNEL_ID, chan 
void ANT_OpenChannel(unsigned char chan) 
{
   uint8_t i;
   unsigned char buf[5];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x01; // LENGTH Byte
   buf[2] = 0x4B; //MESG_OPEN_CHANNEL_ID; // ID Byte
   buf[3] = chan; 
   buf[4] = (0xa4^0x01^0x4b^chan); //checkSum(buf,4);
   
   Serial.print("Open Channel: ");
   for(i = 0 ; i < 5 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}

void ANT_RequestMessage(unsigned char chan, unsigned char message) 
{
   uint8_t i;
   unsigned char buf[6];
   
   buf[0] = 0xa4; //MESG_TX_SYNC; // SYNC Byte
   buf[1] = 0x02; // LENGTH Byte
   buf[2] = 0x4d; 
   buf[3] = chan;
   buf[4] = message;
   buf[5] = checkSum(buf,4);
   
   Serial.print("Request Message: ");
   for(i = 0 ; i < 6 ; i++)
   {
     Serial.print(buf[i], HEX);
     Serial.print(" ");
     mySerial.write(buf[i]);
   }
   Serial.println("");
}

int ANT_rxHandler()
{
   int n, fd, rc, inmsg = FALSE;
   UCHAR chr, msgN;
   
   while (mySerial.available()>0) 
   {
      chr = mySerial.read();
      if (chr == -1)
      {
         Serial.println("Unknown error has occured");
      }
      else
      {
         if ((chr == MESG_TX_SYNC) && (inmsg == FALSE))
         {
            msgN = 0; // Always reset msg count if we get a sync
            inmsg = TRUE;
         
            rxBuf[msgN] = chr; // second byte will be msg size
            msgN++;            
            Serial.print("RX: [sync]");
                      
         }
         else if (msgN == 1)
         {
            rxBuf[msgN] = chr; // second byte will be msg siz
            msgN++;
//            Serial.print("..0x");
//            Serial.print(chr,HEX);
         }
         else if (msgN == 2)
         {
            rxBuf[msgN] = chr;
            msgN++;
//            Serial.print("..0x");
//            Serial.print(chr,HEX);
              Serial.print("..[0x");
              Serial.print(chr, HEX);
              Serial.println("]");
         }
         else if (msgN < rxBuf[1]+3) // sync, size, checksum x 1 byte
         {            
            rxBuf[msgN] = chr;
            msgN++;            
//            Serial.print("..0x");
//            Serial.print(chr,HEX);
         }
         else
         {
            inmsg = FALSE;
            rxBuf[msgN] = chr;
//            Serial.print("..0x");
//            Serial.println(chr,HEX);
            
            if (checkSum(rxBuf, msgN) == rxBuf[msgN]) // Check if chksum = msg chksu
            {            
//               Serial.print("RX: msg received-");
//                         Serial.println(msgN);   
                                        ANT_rxMsg();
            }
            else
            {
               Serial.println("RX: chksum mismatch");
            }
         }
      }
         
      
   }
   
}


int ANT_rxMsg()
{
   //int i;
   UCHAR msgID, msgSize;
   UCHAR *msgData;
   
   // copy args
//   memcpy(rxBuf, args, sizeof(UCHAR) * MAXMSG);

   msgID = rxBuf[2];
   msgSize = rxBuf[1];
   msgData = &rxBuf[3];
//   Serial.print("MessageID is ");
//   Serial.println(msgID, HEX);
   
   switch (msgID)
   {
      case MESG_RESPONSE_EVENT_ID :
         Serial.print("Message Response ");
         Serial.print( rxBuf[3], DEC);    
         Serial.print("..");
         Serial.print( rxBuf[4], HEX);    
         Serial.print("..");
         Serial.println(rxBuf[5], HEX);

         break;
      case MESG_CAPABILITIES_ID   :    
         break;
      case MESG_BROADCAST_DATA_ID :
         if(heartrate != msgData[msgSize-1]){
           clearLCD();
           lcdPosition(0,0);
           lcdSerial.print("Heartrate is ");
           lcdSerial.print(msgData[msgSize-1], DEC);
         }         
         Serial.print("Heartrate is ");
         Serial.println(msgData[msgSize-1], DEC);
         heartrate = msgData[msgSize-1];
         break;                              
      default :
        Serial.println("ID: Unknown msgID");
   }
}

#define DEVTYPE_HRM	0x78	/* ANT+ HRM */
#define DEVTYPE_BIKE	0x79	/* ANT+ Bike speed and cadence */
#define DEVTYPE_PWR	0x0b	/* ANT+ Power meter */

#define DEVPERIOD_HRM	0x86	/* ANT+ HRM */
#define DEVPERIOD_BIKE	0x96	/* ANT+ Bike speed and cadence */
#define DEVPERIOD_PWR	0xf6	/* ANT+ Power meter */


void config(){

  ANT_Reset();
  delay(50);
  
  ANT_AssignChannel(0x00);
  delay(50);  
  ANT_SetChannelID(0x00, DEVTYPE_HRM);
  delay(50);
  ANT_SetNetworkKey(0x00);
  delay(50);
  ANT_SetChannelSearchTimeout(0x00);
  delay(50);  
  ANT_SetChannelRFFreq(0x00);
  delay(50);  
  ANT_SetChannelPeriod(0x00, DEVPERIOD_HRM);
  delay(50);  
  ANT_OpenChannel(0x00);  
  delay(50);
  
//  delay(50);
//  ANT_AssignChannel(0x01);
//  delay(50);  
//  ANT_SetChannelID(0x01, DEVTYPE_BIKE);
//  delay(50);
//  ANT_SetNetworkKey(0x01);
//  delay(50);
//  ANT_SetChannelSearchTimeout(0x01);
//  delay(50);  
//  ANT_SetChannelRFFreq(0x01);
//  delay(50);  
//  ANT_SetChannelPeriod(0x01, DEVPERIOD_BIKE);
//  delay(50);  
//  ANT_OpenChannel(0x01);  
//  delay(50);
//
//  delay(50);
//  ANT_AssignChannel(0x02);
//  delay(50);  
//  ANT_SetChannelID(0x02, DEVTYPE_PWR);
//  delay(50);
//  ANT_SetNetworkKey(0x02);
//  delay(50);
//  ANT_SetChannelSearchTimeout(0x02);
//  delay(50);  
//  ANT_SetChannelRFFreq(0x02);
//  delay(50);  
//  ANT_SetChannelPeriod(0x02, DEVPERIOD_PWR);
//  delay(50);  
//  ANT_OpenChannel(0x02);  
//  delay(50);  
}

void clearLCD(){
   lcdSerial.write(0xFE);   //command flag
   lcdSerial.write(0x01);   //clear command.
   delay(10);
}
void backlightOn(){  //turns on the backlight
    lcdSerial.write(0x7C);   //command flag for backlight stuff
    lcdSerial.write(157);    //light level.
   delay(10);
}
void backlightOff(){  //turns off the backlight
    lcdSerial.write(0x7C);   //command flag for backlight stuff
    lcdSerial.write(128);     //light level for off.
   delay(10);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  lcdSerial.write(0xFE);
}
void lcdPosition(int row, int col) {
  lcdSerial.write(0xFE);   //command flag
  lcdSerial.write((col + row*64 + 128));    //position 
  delay(10);
}

void setup()  {
  // define pin modes for tx, rx, led pins:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(rtsPin, INPUT);
  //pinMode(ledPin, OUTPUT);
  // set the data rate for the SoftwareSerial port
  lcdSerial.begin(9600);
  mySerial.begin(4800);
  Serial.begin(9600);
  
  clearLCD();
  lcdPosition(0,0);
  lcdSerial.print("Iufer HRM");
  config();
}

void loop() {
  ANT_rxHandler();
}

