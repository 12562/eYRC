/*******************************************************

Algorithm assumes 2 box placing in the sorting zones.
If can't be implemented then changes will be required.
Ain't Nobody got time fo' that.
                                   - Deepanshu Bhatia

********************************************************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <unistd.h>
using namespace std;

int T[4][2];


int C[4]; // Correct color for T1 , T2 , T3 and T4
/*
 0      -  Black
 1      -  Red
 2      -  Green
 3      -  Blue
*/

int S[2][2]={-1,-1,-1,-1};
int dist=0,c=-1;
string path;

//////////////////////////////////////////////////////////////////////////////PIN CONFIGURATION
//Configure PORTB 6 pin for servo motor 2 operation
void servo2_pin_config (void)
{
	DDRB  = DDRB | 0x40;  //making PORTB 6 pin output
	PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1
}

//Function to initialize Buzzer 
void buzzer_pin_config (void)
{
 DDRC = DDRC | 0x08;		//Setting PORTC 3 as output
 PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
}

//Function to configure LCD port
void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; //all the LCD pin's direction set as output
	PORTC = PORTC & 0x80; // all the LCD pins are set to logic 0 except PORTC 7
}

//ADC pin configuration
void adc_pin_config (void)
{
	DDRF = 0x00;
	PORTF = 0x00;
	DDRK = 0x00;
	PORTK = 0x00;
}

void color_sensor_pin_config(void)
{
	DDRD  = DDRD | 0xFE; //set PD0 as input for color sensor output
	PORTD = PORTD | 0x01;//Enable internal pull-up for PORTD 0 pin
}

//Function to configure ports to enable robot's motion
void motion_pin_config (void)
{
	DDRA = DDRA | 0x0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
	PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM.
}

//Function to configure INT4 (PORTE 4) pin as input for the left position encoder
void left_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xEF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x10; //Enable internal pull-up for PORTE 4 pin
}

//Function to configure INT5 (PORTE 5) pin as input for the right position encoder
void right_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 4 pin
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////INITIALIZATION
//Initialize the ports
void port_init(void)
{
        buzzer_pin_config();
	servo2_pin_config();        //Configure PORTB 6 pin for servo motor 2 operation
	lcd_port_config();          //LCD pin configuration
	adc_pin_config();
	color_sensor_pin_config();  //Color sensor pin cofiguration
	motion_pin_config();
	left_encoder_pin_config(); //left encoder pin config
	right_encoder_pin_config(); //right encoder pin config
}

//TIMER1 initialization in 10 bit fast PWM mode  
//prescale:256
// WGM: 7) PWM 10bit fast, TOP=0x03FF
// actual value: 52.25Hz 
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
 TCNT1L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
 OCR1AH = 0x03;	//Output compare Register high value for servo 1
 OCR1AL = 0xFF;	//Output Compare Register low Value For servo 1
 OCR1BH = 0x03;	//Output compare Register high value for servo 2
 OCR1BL = 0xFF;	//Output Compare Register low Value For servo 2
 OCR1CH = 0x03;	//Output compare Register high value for servo 3
 OCR1CL = 0xFF;	//Output Compare Register low Value For servo 3
 ICR1H  = 0x03;	
 ICR1L  = 0xFF;
 TCCR1A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
 					For Overriding normal port functionality to OCRnA outputs.
				  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
 TCCR1C = 0x00;
 TCCR1B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}

// Timer 5 initialized in PWM mode for velocity control
// Prescale:256
// PWM 8bit fast, TOP=0x00FF
// Timer Frequency:225.000Hz
void timer5_init()
{
	TCCR5B = 0x00;	//Stop
	TCNT5H = 0xFF;	//Counter higher 8-bit value to which OCR5xH value is compared with
	TCNT5L = 0x01;	//Counter lower 8-bit value to which OCR5xH value is compared with
	OCR5AH = 0x00;	//Output compare register high value for Left Motor
	OCR5AL = 0xFF;	//Output compare register low value for Left Motor
	OCR5BH = 0x00;	//Output compare register high value for Right Motor
	OCR5BL = 0xFF;	//Output compare register low value for Right Motor
	OCR5CH = 0x00;	//Output compare register high value for Motor C1
	OCR5CL = 0xFF;	//Output compare register low value for Motor C1
	TCCR5A = 0xA9;	/*{COM5A1=1, COM5A0=0; COM5B1=1, COM5B0=0; COM5C1=1 COM5C0=0}
 					  For Overriding normal port functionality to OCRnA outputs.
				  	  {WGM51=0, WGM50=1} Along With WGM52 in TCCR5B for Selecting FAST PWM 8-bit Mode*/
	
	TCCR5B = 0x0B;	//WGM12=1; CS12=0, CS11=1, CS10=1 (Prescaler=64)
}

void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;		//MUX5 = 0
	ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
	ACSR = 0x80;
	ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}


void left_position_encoder_interrupt_init (void) //Interrupt 4 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x02; // INT4 is set to trigger with falling edge
	EIMSK = EIMSK | 0x10; // Enable Interrupt INT4 for left position encoder
	sei();   // Enables the global interrupt
}

void right_position_encoder_interrupt_init (void) //Interrupt 5 enable
{
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x08; // INT5 is set to trigger with falling edge
	EIMSK = EIMSK | 0x20; // Enable Interrupt INT5 for right position encoder
	sei();   // Enables the global interrupt
}

void color_sensor_pin_interrupt_init(void) //Interrupt 0 enable
{
	cli(); //Clears the global interrupt
	EICRA = EICRA | 0x02; // INT0 is set to trigger with falling edge
	EIMSK = EIMSK | 0x01; // Enable Interrupt INT0 for color sensor
	sei(); // Enables the global interrupt
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////INITIALISING FUNCTION
//Function to initialize all the peripherals
void init_devices(void)
{
	cli(); //disable all interrupts
	port_init();
	timer1_init();
	timer5_init();
	adc_init();
	left_position_encoder_interrupt_init();
	right_position_encoder_interrupt_init();
	color_sensor_pin_interrupt_init();
	sei(); //re-enable interrupts
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////ACTUATING FUNCTIONS

void buzzer_on (void)
{
 unsigned char port_restore = 0;
 port_restore = PINC;
 port_restore = port_restore | 0x08;
 PORTC = port_restore;
}

void buzzer_off (void)
{
 unsigned char port_restore = 0;
 port_restore = PINC;
 port_restore = port_restore & 0xF7;
 PORTC = port_restore;
}

//Function For ADC Conversion
unsigned char ADC_Conversion(unsigned char Ch) 
{
	unsigned char a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;  			
	ADMUX= 0x20| Ch;	   		
	ADCSRA = ADCSRA | 0x40;		//Set start conversion bit
	while((ADCSRA&0x10)==0);	//Wait for conversion to complete
	a=ADCH;
	ADCSRA = ADCSRA|0x10; //clear ADIF (ADC Interrupt Flag) by writing 1 to it
	ADCSRB = 0x00;
	return a;
}

// This Function calculates the actual distance in millimeters(mm) from the input
// analog value of Sharp Sensor.
unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
{
	float distance;
	unsigned int distanceInt;
	distance = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	distanceInt = (int)distance;
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}

//Function To Print Sesor Values At Desired Row And Coloumn Location on LCD
void print_sensor(char row, char coloumn,unsigned char channel)
{
	
	ADC_Value = ADC_Conversion(channel);
	lcd_print(row, coloumn, ADC_Value, 3);
}

//Function for velocity control
void velocity (unsigned char left_motor, unsigned char right_motor)
{
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}

//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
 unsigned char PortARestore = 0;

 Direction &= 0x0F; 		// removing upper nibbel for the protection
 PortARestore = PORTA; 		// reading the PORTA original status
 PortARestore &= 0xF0; 		// making lower direction nibbel to 0
 PortARestore |= Direction; // adding lower nibbel for forward command and restoring the PORTA status
 PORTA = PortARestore; 		// executing the command
}

void forward (void) 
{
  motion_set (0x06);
}

void back (void) //both wheels backward
{
	motion_set(0x09);
}

void left (void) //Left wheel backward, Right wheel forward
{
	motion_set(0x05);
}

void right (void) //Left wheel forward, Right wheel backward
{
	motion_set(0x0A);
}

void stop (void)
{
  motion_set (0x00);
}

//ISR for color sensor
ISR(INT0_vect)
{
	pulse++; //increment on receiving pulse from the color sensor
}

//ISR for right position encoder
ISR(INT5_vect)
{
	ShaftCountRight++;  //increment right shaft position count
}


//ISR for left position encoder
ISR(INT4_vect)
{
	ShaftCountLeft++;  //increment left shaft position count
}

//Function used for turning robot by specified degrees
void angle_rotate(unsigned int Degrees)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
	ShaftCountRight = 0;
	ShaftCountLeft = 0;

	while (1)
	{
		if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt))
		break;
	}
	stop(); //Stop robot
}

void linear_distance_mm(unsigned int DistanceInMM)
{
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;

	ReqdShaftCount = DistanceInMM / 5.338; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
	
	ShaftCountRight = 0;
	while(1)
	{
		if(ShaftCountRight > ReqdShaftCountInt)
		{
			break;
		}
	}
	stop(); //Stop robot
}

void forward_mm(unsigned int DistanceInMM)
{
	forward();
	linear_distance_mm(DistanceInMM);
}

void back_mm(unsigned int DistanceInMM)
{
	back();
	linear_distance_mm(DistanceInMM);
}

void left_degrees(unsigned int Degrees)
{
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	left(); //Turn left
	angle_rotate(Degrees);
}


void right_degrees(unsigned int Degrees)
{
	// 88 pulses for 360 degrees rotation 4.090 degrees per count
	right(); //Turn right
	angle_rotate(Degrees);
}

//Function to rotate Servo 1 by a specified angle in the multiples of 1.86 degrees
void servo_2(unsigned char degrees)
{
	float PositionPanServo = 0;
	PositionPanServo = ((float)degrees / 1.86) + 35.0;
	OCR1AH = 0x00;
	OCR1AL = (unsigned char) PositionPanServo;
}

//Filter Selection
void filter_red(void)    //Used to select red filter
{
	//Filter Select - red filter
	PORTD = PORTD & 0xBF; //set S2 low
	PORTD = PORTD & 0x7F; //set S3 low
}

void filter_green(void)	//Used to select green filter
{
	//Filter Select - green filter
	PORTD = PORTD | 0x40; //set S2 High
	PORTD = PORTD | 0x80; //set S3 High
}

void filter_blue(void)	//Used to select blue filter
{
	//Filter Select - blue filter
	PORTD = PORTD & 0xBF; //set S2 low
	PORTD = PORTD | 0x80; //set S3 High
}

void filter_clear(void)	//select no filter
{
	//Filter Select - no filter
	PORTD = PORTD | 0x40; //set S2 High
	PORTD = PORTD & 0x7F; //set S3 Low
}

//Color Sensing Scaling
void color_sensor_scaling()		//This function is used to select the scaled down version of the original frequency of the output generated by the color sensor, generally 20% scaling is preferable, though you can change the values as per your application by referring datasheet
{
	//Output Scaling 20% from datasheet
	//PORTD = PORTD & 0xEF;
	PORTD = PORTD | 0x10; //set S0 high
	//PORTD = PORTD & 0xDF; //set S1 low
	PORTD = PORTD | 0x20; //set S1 high
}

void red_read(void) // function to select red filter and display the count generated by the sensor on LCD. The count will be more if the color is red. The count will be very less if its blue or green.
{
	//Red
	filter_red(); //select red filter
	pulse=0; //reset the count to 0
	_delay_ms(100); //capture the pulses for 100 ms or 0.1 second
	red = pulse;  //store the count in variable called red
	
	lcd_wr_command(0x01);
	lcd_cursor(1,1);  //set the cursor on row 1, column 1
	lcd_string("Red Pulses"); // Display "Red Pulses" on LCD
	lcd_print(2,1,red,5);  //Print the count on second row
	_delay_ms(1000);	// Display for 1000ms or 1 second
	lcd_wr_command(0x01); //Clear the LCDlcd_cursor(1,1);  //set the cursor on row 1, column 1
}

void green_read(void) // function to select green filter and display the count generated by the sensor on LCD. The count will be more if the color is green. The count will be very less if its blue or red.
{
	//Green
	filter_green(); //select green filter
	pulse=0; //reset the count to 0
	_delay_ms(100); //capture the pulses for 100 ms or 0.1 second
	green = pulse;  //store the count in variable called green
	
	lcd_cursor(1,1);  //set the cursor on row 1, column 1
	lcd_string("Green Pulses"); // Display "Green Pulses" on LCD
	lcd_print(2,1,green,5);  //Print the count on second row
	_delay_ms(1000);	// Display for 1000ms or 1 second
	lcd_wr_command(0x01); //Clear the LCD
}

void blue_read(void) // function to select blue filter and display the count generated by the sensor on LCD. The count will be more if the color is blue. The count will be very less if its red or green.
{
	//Blue
	filter_blue(); //select blue filter
	pulse=0; //reset the count to 0
	_delay_ms(100); //capture the pulses for 100 ms or 0.1 second
	blue = pulse;  //store the count in variable called blue

    lcd_cursor(1,1);  //set the cursor on row 1, column 1
    lcd_string("Blue Pulses"); // Display "Blue Pulses" on LCD
    lcd_print(2,1,blue,5);  //Print the count on second row
    _delay_ms(1000);	// Display for 1000ms or 1 second
    lcd_wr_command(0x01); //Clear the LCD
}

int decide_color()
{       int color = 4;
    // 0 => Terminal color is black
	// 1 => Terminal color is red
	// 2 => Terminal color is blue
	// 3 => Terminal color is green
	color_sensor_scaling();
	red_read();
	_delay_ms(500);
	blue_read();
	_delay_ms(500);
	green_read();
	_delay_ms(500);
	if(red<2000 && blue<2000 && green<2000)
	  { color = 0;
		lcd_wr_command(0x01);
		lcd_cursor(1,1);
		lcd_string("Black");
		_delay_ms(1000);
		lcd_wr_command(0x01);
	  }
	else if (red>blue && red>green)
	  { color = 1;
		lcd_wr_command(0x01);
		lcd_cursor(1,1);
		lcd_string("Red");
		_delay_ms(1000);
		lcd_wr_command(0x01);
	  }
	else if (blue>red && blue>green)
	  { color = 2;
		lcd_wr_command(0x01);
		lcd_cursor(1,1);
		lcd_string("Blue");
		_delay_ms(1000);
		lcd_wr_command(0x01);
	  }
	else if (green>red && green>blue)
	  { color = 3;
	    lcd_wr_command(0x01);
	    lcd_cursor(1,1);
	    lcd_string("Green");
	    _delay_ms(1000);
	    lcd_wr_command(0x01);
	  }
	return color;
}

int goStraight()
{
    //until obstruction or diversion or rotations
    //code
     while(1)
       {
         Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
	 Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
	 Right_white_line = ADC_Conversion(1);	//Getting data of Right WL Sensor 

         flag = 0;

         sharp = ADC_Conversion(11);						//Stores the Analog value of front sharp connected to ADC channel 11 into variable "sharp"
	 value = Sharp_GP2D12_estimation(sharp);            //Stores Distance calculated in a variable "value".

         if(value < 90)				
	   {
		 stop();
                 break;
	   } 
         if(Center_white_line>0x10)
	   {
		 flag=1;
		 forward();
		 velocity(210,210);
	   }
        if((Left_white_line<0x10) && (flag==0))
           {
		 flag=1;
		 forward();
		 velocity(190,160);
	   }
        if((Right_white_line<0x10) && (flag==0))
	   {
		 flag=1;
		 forward();
		 velocity(160,190);
	   }
        if((Center_white_line>30 && Left_white_line>30 && Right_white_line>30)
        || (Center_white_line>30 && Left_white_line>30)
        || (Center_white_line>30 && Right_white_line>30)
          )
           {   
                 stop();
                 delay_ms(200);
                 forward_mm(35);
                 stop();
                 break;
           }
       }
    path.append("S");
    return 0;
}
int turnLeft()
{
    //code
    left_degrees(90);
    path.append("L");
    return 0;
}
int turnRight()
{
    //code
    right_degrees(90);
    path.append("R");
    return 0;
}

int aboutTurn()
{   
    back();
    _delay_ms(500);
    turnLeft();
    turnLeft();
    //or a separate code for it with double delay
    return 0;
}

int goLeft()
{
    turnLeft();
    goStraight();
    return 0;
}

int goRight()
{
    turnRight();
    goStraight();
    return 0;
}

int SS()
{
    goStraight();
    goStraight();
    return 0;
}
int SLS()
{
    goStraight();
    goLeft();
    return 0;
}
int SRS()
{
    goStraight();
    goRight();
    return 0;
}

int T1C()
{
    SLS();
    return 0;
}
int T2C()
{
    SRS();
    return 0;
}
int T3C()
{
    SRS();
    return 0;
}
int T4C()
{
    SLS();
    return 0;
}

int CT1()
{
    //bot facing towards t1 and t3 side
    SRS();
    return 0;
}
int CT2()
{
    //bot facing towards t2 and t4 side
    SLS();
    return 0;
}
int CT3()
{
    //bot facing towards t1 and t3 side
    SLS();
    return 0;
}
int CT4()
{
    //bot facing towards t2 and t4 side
    SRS();
    return 0;
}

int T1T2()
{
    T1C();
    CT2();
    return 0;
}
int T1T3()
{
    SS();
    return 0;
}
int T1T4()
{
    T1C();
    CT4();
    return 0;
}
int T2T1()
{
    T2C();
    CT1();
    return 0;
}
int T2T3()
{
    T2C();
    CT3();
    return 0;
}
int T2T4()
{
    SS();
    return 0;
}
int T3T1()
{
    SS();
    return 0;
}
int T3T2()
{
    T3C();
    CT2();
    return 0;
}
int T3T4()
{
    T3C();
    CT4();
    return 0;
}
int T4T1()
{
    T4C();
    CT1();
    return 0;
}
int T4T2()
{
    SS();
    return 0;    
}
int T4T3()
{
    T4C();
    CT3();
    return 0;
}

//sorting zones
int T1S1()
{
    SRS();
    return 0;
}
int T1S2()
{
    SLS();
    SS();
    return 0;
}
int S1T1()
{
    SLS();
    return 0;
}
int S2T1()
{
    SS();
    SRS();
    return 0;
}

int T2S1()
{
    SRS();
    SS();
    return 0;
}
int T2S2()
{
    SLS();
    return 0;
}
int S1T2()
{
    SS();
    SLS();
    return 0;
}
int S2T2()
{
    SRS();
    return 0;
}

int T3S1()
{
    SLS();
    return 0;
}
int T3S2()
{
    SRS();
    SS();
    return 0;
}
int S1T3()
{
    SRS();
    return 0;
}
int S2T3()
{
    SS();
    SLS();
    return 0;
}

int T4S1()
{
    SLS();
    SS();
    return 0;
}
int T4S2()
{
    SRS();
    return 0;
}
int S1T4()
{
    SS();
    SRS();
    return 0;
}
int S2T4()
{
    SLS();
    return 0;
}

int S1S2()
{
    SS();
    SS();
    return 0;
}

int S2S1()
{
    SS();
    SS();
    return 0;
}

int TL()
{
    goLeft();
    return 0;
}
int TR()
{
    goRight();
    return 0;
}
int LT()
{
    goStraight();
    turnRight();
    return 0;
}
int RT()
{
    goStraight();
    turnLeft();
    return 0;
}

int LR()
{
    SS();
    return 0;
}

int RL()
{
    SS();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int readColor()
{
    unsigned char color=-1;
    path.append("rU");
    aboutTurn();
    //Color reading code goes here
    color = decide_color();
    return color;
}

int readColorInd(int j)
{
    C[j]=readColor();
    return 0;
}

int readColorT(int i,int j)
{
    T[i][j]=readColor();
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pick()
{
    //code
    int i = 135;
    for (i = 135; i > 85; i--)
        { servo_2(i);
          _delay_ms(30);
         }
    aboutTurn();
    path.append("pU");
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int drop()
{
    //code
    int i = 84;
    for (; i<=135; i++)
       { servo_2(i);
	 _delay_ms(30);
        } 
    aboutTurn();
    path.append("dU");
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int buzzOn()
{
    buzzer_on();
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int buzzOff()
{
    buzzer_off();
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
int buzz(int delay)
{
    buzzOn();
    _delay_ms(delay);
    buzzOff();
}


int readInd()
{
    goStraight();
    
    //Read Indicator 3
    goLeft();
    readColorInd(2);
    aboutTurn();
    SS();
    
    //Read Indicator 4
    readColorInd(3);
    aboutTurn();
    goStraight();
    goRight();
    
    //Read Indicator 1
    goLeft();
    readColorInd(0);
    aboutTurn();
    SS();
    
    //Read Indicator 2
    readColorInd(1);
    aboutTurn();
    goStraight();
    goRight();
    //now in the mid point of the arena
    
    return 0;
}


int solveNear13()
{
    int f1=0,f2=0,s1=0,s2=0;
    
    CT1();
    TL();
    readColorT(0,0);
    if(T[0][0]==C[0])
    {
        f1+=1;
        buzz(500);
    }
    else if(T[0][0]==C[2])
    {
         s1+=1;
    }
    LR();
    readColorT(0,1);
    if(T[0][1]==C[0])
    {
        f1+=2;
        buzz(500);
    }
    else if(T[0][1]==C[2])
    {
         s1+=2;
    }
    switch(f1)
    {
             case 3:
                  RT();
                  T1T3();
                  break;
                  
             case 2:
                  RL();
                  pick();
                  c=T[0][0];
                  T[0][0]=-1;
                  LT();
                  T1S1();
                  drop();
                  S[0][0]=c;
                  c=-1;
                  S1T3();
                  break;
                  
             case 1:
                  pick();
                  c=T[0][1];
                  T[0][1]=-1;
                  RT();
                  T1S1();
                  drop();
                  S[0][0]=c;
                  c=-1;
                  S1T3();
                  break;
                  
             case 0:
                  if(s1==1)
                  {
                      RL();
                      pick();
                      c=T[0][0];
                      T[0][0]=-1;
                      LT();
                  }
                  else
                  {
                      pick();
                      c=T[0][1];
                      T[0][1]=-1;
                      RT();
                  }
                  T1S1();
                  drop();
                  S[0][0]=c;
                  c=-1;
                  S1T3();
                  break;
    }
    
    //Reading T3
    TL();
    readColorT(2,0);
    if(T[2][0]==C[2])
    {
        f2+=1;
        buzz(500);
    }
    else if(T[2][0]==C[0])
    {
         s2+=1;
    }
    LR();
    readColorT(2,1);
    if(T[2][1]==C[2])
    {
        f2+=2;
        buzz(500);
    }
    else if(T[2][1]==C[0])
    {
         s1+=2;
    }
    
    switch(f2)
    {
             case 3:
                  RT();
                  if(f1!=3)
                  {
                      T3S1();
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;
                      S1T2();
                  }
                  else
                      T3T2();
                  break;
                  
             case 2:
                  RL();
                  pick();
                  c=T[2][0];
                  T[2][0]=-1;
                  LT();
                  if(c==C[0])
                  {
                      T3T1();
                      if(f1==2)
                      {
                          TL();
                          drop();
                          T[0][0]=c;
                          c=-1;
                          LT();
                      }
                      else
                      {
                          TR();
                          drop();
                          T[0][1]=c;
                          c=-1;
                          if(f1==1)
                              RT();
                          else
                          {
                              RL();
                              pick();
                              c=T[0][0];
                              T[0][0]=-1;
                              LT();
                          }
                          
                      }
                      
                      if(S[0][0]==C[2])
                      {
                          T1S1();
                          if(c!=-1)
                          {
                              drop();
                              S[0][1]=c;
                              c=-1;
                          }
                          pick();
                          c=S[0][0];
                          S[0][0]=-1;
                          if(s1>=1)
                          {
                              S1T3();
                              TL();
                              drop();
                              T[2][0]=c;
                              c=-1;
                              LT();
                              if(S[0][1]!=-1)
                              {
                                  T3S1();
                                  pick();
                                  c=S[0][1];
                                  S[0][1]=-1;
                                  S1S2();
                                  drop();
                                  S[1][0]=c;
                                  c=-1;
                                  S2T2();
                              }
                              else
                                  T3T2();
                              
                          }
                          else
                          {
                              S1S2();
                              drop();
                              S[1][0]=c;
                              c=-1;
                              S2T2();
                          }
                      }
                      else
                      {
                          T1S2();
                          drop();
                          S[1][0]=c;
                          c=-1;
                          S2T2();
                      }
                  }
                  else if(S[0][0]==C[2])
                  {
                      T3S1();
                      drop();
                      S[0][1]=c;
                      c=-1;
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1T3();
                      TL();
                      drop();
                      T[2][0]=c;
                      c=-1;
                      LT();
                      T3S1();
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1S2();
                      drop();
                      S[1][0]=c;
                      c=-1;
                      S2T2();
                  }
                  else
                      T3T2();
                  }
                  break;
                  
             case 1:
                  pick();
                  c=T[2][1];
                  T[2][1]=-1;
                  RT();
                  if(c==C[0])
                  {
                      T3T1();
                      if(f1==2)
                      {
                          TL();
                          drop();
                          T[0][0]=c;
                          c=-1;
                          LT();
                      }
                      else
                      {
                          TR();
                          drop();
                          T[0][1]=c;
                          c=-1;
                          if(f1==1)
                              RT();
                          else
                          {
                              RL();
                              pick();
                              c=T[0][0];
                              T[0][0]=-1;
                              LT();
                          }
                          
                      }
                      
                      if(S[0][0]==C[2])
                      {
                          T1S1();
                          if(c!=-1)
                          {
                              drop();
                              S[0][1]=c;
                              c=-1;
                          }
                          pick();
                          c=S[0][0];
                          S[0][0]=-1;
                          if(s1>=1)
                          {
                              S1T3();
                              TR();
                              drop();
                              T[2][1]=c;
                              c=-1;
                              RT();
                              if(S[0][1]!=-1)
                              {
                                  T3S1();
                                  pick();
                                  c=S[0][1];
                                  S[0][1]=-1;
                                  S1S2();
                                  drop();
                                  S[1][0]=c;
                                  c=-1;
                                  S2T2();
                              }
                              else
                                  T3T2();
                              
                          }
                          else
                          {
                              S1S2();
                              drop();
                              S[1][0]=c;
                              c=-1;
                              S2T2();
                          }
                      }
                      else
                      {
                          T1S2();
                          drop();
                          S[1][0]=c;
                          c=-1;
                          S2T2();
                      }
                  }
                  else if(S[0][0]==C[2])
                  {
                      T3S1();
                      drop();
                      S[0][1]=c;
                      c=-1;
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1T3();
                      TR();
                      drop();
                      T[2][1]=c;
                      c=-1;
                      RT();
                      T3S1();
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1S2();
                      drop();
                      S[1][0]=c;
                      c=-1;
                      S2T2();
                  }
                  else
                      T3T2();
                  }
                  break;
                  
             case 0:
                  if(f1==3)
                  {
                      pick();
                      RT();
                      T3T2();
                  }
                  else if(s2!=0)
                  {
                  }
                  break;
    }
    return 0;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    
    return 0;
}
