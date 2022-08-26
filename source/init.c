#include "init.h"
#include "debug.h"
 volatile enum state_heater State_heater;
 volatile enum state_heater State_heater_next;
  volatile enum state_ecoca State_ecoca;
  volatile enum state_ecoca State_ecoca_next;

volatile Key ok,stop,browse;
volatile int deb = 0;
volatile int count;
volatile short minute = 0;
volatile int TIM;
Food FOOD_LIST[3];

Food _FOOD; //Main food selected

const int TIMER_RICE[3]={ 50, 70, 50};
const int TIMER_WATER[3]={ 50, 70, 50};
const int TIMER_BEANS[3]={ 50, 70, 50};
volatile int curr = 0;//iterating food

unsigned short period0 = 1 / 100;
unsigned short periodservo = 1 / 50;
int pins0[6];
void initFood(Food* st, int id, char *name, const int *timers,double sp) {
	st->id = id;
	memcpy(st->name, name, 20 * sizeof(char));
	st->t1 = *timers;
	st->t2 = *++timers;
	st->t3= *++timers;
	st->sp = sp;
}


void initswitch(int pin) {

	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //Enabling clocks to Port D

	/* Settting GPIO on PCR mux*/
	PORTD->PCR[pin] |= PORT_PCR_MUX(01U);
	/* Setting Switch to be an input, forcing corresponding bit to be 0 */
	PTD->PDDR &= ~(GPIO_PDDR_PDD((pin)));
	PORTD->PCR[pin] |= PORT_PCR_IRQC(
			0x0a) | PORT_PCR_PE(1) | PORT_PCR_PS(1);
	NVIC_SetPriority(PORTD_IRQn, 128);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}

void init() {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	SP = SP_ROOM_T;
	BOARD_InitDebugConsole();
	SysTick_Config(ms100);
	TIM=0;
	Init_LCD();
	Clear_LCD();
	Set_Cursor(0U, 0U);
	Print_LCD("Ecoca- V2.0");

	pins0[0] = HEATER;
	pins0[1] = -1;
	deb = 0;
	count = 1;
	memset(&ok, 0, sizeof(Key));
	memset(&stop, 0, sizeof(Key));
	memset(&browse, 0, sizeof(Key));



	ok.pin=OK;
	stop.pin=STOP;
	browse.pin=BRWS;


	State_heater_next=rise;
	State_heater=rise;
	State_ecoca_next=Browse;
	State_ecoca=Browse;
	prop=0;
	integral=0;

	char name[20];
	memset(name, 0, 20);
	strcpy(name, "Rice");
	initFood(&FOOD_LIST[RICE], 1, name,TIMER_RICE, 60 );
	memset(name, 0, 20);
	strcpy(name, "Beans");
	initFood(&FOOD_LIST[BEANS], 2, name, TIMER_BEANS, 80 );
	memset(name, 0, 20);
	strcpy(name, "Water");

	initFood(&FOOD_LIST[WATER], 3, name, TIMER_WATER, 100 );


	memset(&_FOOD, 0, sizeof(Food)); //Selected food
	initDebug();
	clearDebug();
	initswitch(BRWS);
	initswitch(OK);
	initswitch(STOP);
	initTempIP();
	initHeaterPWM();

	__enable_irq();

}

