#ifndef SOURCES_MSGCMD_H_
#define SOURCES_MSGCMD_H_
//#define MAX_DATA_SIZE 1

typedef enum Cmd_e
{
	LED_Config
} Cmds;

typedef enum payload_e {
LED_RED , // Provides a temperature Reading
LED_BLUE , // Sets speed for a motor Controller
LED_GREEN, // Configures the LEDs to some color
LED_DANCE // Sets Low Power Mode // More command IDs here
} payload;

typedef struct CI_Msg_t{
Cmds command; // Command operation
uint8_t length; // Size of message
payload data; // Generic data payload
uint16_t checksum; // Error detection checksum
} CI_Msg;

void uart_init();
void structure_init(CI_Msg *msg);
void Decode_CI_Msg(CI_Msg * msg);
void Set_red_LED();
void Set_blue_LED();
void Set_green_LED();
void Set_LED_Dance();
void delay();
//void Set_LPM(char _LPM );
//void Set_LED_config(char  _LED);

#endif /* SOURCES_MSGCMD_H_ */

