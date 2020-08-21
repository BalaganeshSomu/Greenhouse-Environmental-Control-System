#include<pic.h>
__CONFIG(0x2CE2);
#define _XTAL_FREQ 10000000
#define I2C_FREQ 1000000

#define RS RE2
#define RW RE1
#define EN RE0
#define LCD PORTD


//PLANT RELATED
#define Acid RB5
#define Base RC0
#define Fertilizer RB6
#define Recircle RB7

//use 12 v relay
#define light RB0
#define cooler RB1
#define heater RB2
#define ex RB3

			
unsigned char Check, T_byte1, T_byte2,
 RH_byte1, RH_byte2, Ch ;
unsigned Temp, RH, Sum ;
float ph_val7,ph_val_f;
unsigned char s[20];
unsigned int ph_value,ph_val,f,c,count,motor,var3,var4,var5,var6,var6_w,var7,var8,var_w,var_f,var2,var9,flag2,flag3,flag4,flag5,flag6,flag7,flag8,flag9;
unsignedintrec,five_min;
const char *day[8]={"Em","SUN","MON","TUE","WED","THU","FRI","SAT"};
unsigned char sec,min,hur;
unsigned char date,month,year,days,pre_date=0;


void pulse()
{
	EN=1;
	__delay_ms(10);
	EN=0;
	__delay_ms(10);
}	
voidlcd_cmd(char a)
{
	RS=0;
	RW=0;
	LCD=((a)&0xF0);
	pulse();
	RS=0;
	RW=0;
	LCD=((a&0x0f)<<4);
	pulse();
}
voidlcd_digit(char x)
{
	RS=1;
	RW=0;
	LCD=(x&0xF0);
	pulse();
	RS=1;
	RW=0;
	LCD=((x&0x0f)<<4);
	pulse();
}

void string(const char *p)
{
	while(*p)
	{
		lcd_digit(*p);
		p++;
	}
	
}		

//PH
voidadc()
{
	ADCON0=0x83;
	ADCON1=0x80;
	GO=1;
	while(GO);
	ph_value=((ADRESH<<8)|ADRESL);
	
	if((0<ph_value)&&(ph_value<20))
	ph_val=8;
	if((20<=ph_value)&&(ph_value<=60))
	ph_val=7;
	if((80<ph_value)&&(ph_value<=130))
	ph_val=6;
	if((150<ph_value)&&(ph_value<=250))
	ph_val=5;
	if((300<ph_value)&&(ph_value<=400))
	ph_val=4;
	if((400<ph_value)&&(ph_value<=550))
	ph_val=3;
	if((550<ph_value))//&&(ph_value<=550))
	ph_val=2;

	
	
	lcd_cmd(0x8A);
	string("PH:");
	lcd_digit(ph_val+0x30);
	
	
	switch(ph_val)
	  { 
		case 2:RB5=0;Fertilizer=0;
				flag3=flag4=flag5=flag6=flag7=flag8=flag9=0;
				if(flag2==0)
				{
				var2=sec;
				flag2=1;
				}
				if(((var2>=sec)&&(sec<=var2+4))&&(flag2==1))
				{
					Base=1;
				}
				else
				{
					Base=0;
					flag2=2;
				}
				if(flag2==2)
				if(sec==(var2+10))
				{
					flag2=0;
				}
				break;  
		case 3: RB5=0;Fertilizer=0;
				flag2=flag4=flag5=flag6=flag7=flag8=flag9=0;
				if(flag3==0)
				{
				var3=sec;
				flag3=1;
				}
				if(((var3>=sec)&&(sec<=var3+4))&&(flag3==1))
				{
					Base=1;
				}
				else
				{
					Base=0;
					flag3=2;
				}
				if(flag3==2)
				if(sec==(var3+10))
				{
					flag3=0;
				}
				break;  
				
		case 4:	flag2=flag3=flag5=flag6=flag7=flag8=flag9=0;RB5=0;Fertilizer=0;
				if(flag4==0)
				{
				var4=sec;
				flag4=1;
				}
				if(((var4>=sec)&&(sec<=var4+4))&&(flag4==1))
				{
					Base=1;
				}
				else
				{
					Base=0;
					flag4=2;
				}
				if(flag4==2)
				if(sec==(var4+10))
				{
					flag4=0;
				}
				break;    
				
		case 5:	flag2=flag4=flag3=flag6=flag7=flag8=flag9=0;RB5=0;Fertilizer=0;
				if(flag5==0)
				{
				var5=sec;
				flag5=1;
				}
				if(((var5>=sec)&&(sec<=var5))&&(flag5==1))
				{
					Base=1;
				}
				else
				{
					Base=0;
					flag5=2;
				}
				if(flag5==2)
				if(sec==(var5+10))
				{
					flag5=0;
				}
				break;  
				
	case 6:flag2=flag4=flag5=flag3=flag7=flag8=flag9=0;
				Base=0;RB5=0;
				if(flag6==0)
				{
					var6=sec;
					flag6=1;
				}
				if(((var6>=sec)&&(sec<=var6+2))&&(flag6==1))
				{
					Fertilizer=1;
				}
				else
				{
					Fertilizer=0;
					flag6=2;
				}
				break;
	
	case 7:	flag2=flag4=flag5=flag6=flag3=flag8=flag9=0;
				Base=0;
				if(flag7==0)
				{
					var7=sec;
					flag7=1;
				}
				if((var7==sec)&&(flag7==1))
				{
					RB5=1;
				}
				else
				{
					RB5=0;
					flag7=2;
				}
				if(flag7==2)
				if(sec==(var7+10))
				{
					flag7=0;
				}
	break;
	
	case 8:flag2=flag4=flag5=flag6=flag7=flag3=flag9=0;Base=0;Fertilizer=0;
			if(flag8==0)
				{
					var8=sec;
					flag8=1;
				}
				if(((var8>=sec)&&(sec<=var8+4))&&(flag8==1))
				{
					RB5=1;
				}
				else
				{
					RB5=0;
					flag8=2;
				}
				if(flag8==2)
				if((sec>=(var8+10))&&(sec<=(var8+14)))
				{
					flag8=0;
				}
				break;
	case 9:flag2=flag4=flag5=flag6=flag7=flag8=flag3=0;Base=0;Fertilizer=0;
			if(flag9==0)
				{
					var9=sec;
					flag9=1;
				}
				if(((var9>=sec)&&(sec<=var9+4))&&(flag9==1))
				{
					RB5=1;
				}
				else
				{
					RB5=0;
					flag9=2;
				}
				if(flag9==2)
				if((sec>=var9+10)||(sec<=var9+14))
				{
					flag9=0;
				}
				break;
				
	  }
	
		

}




 //i2c	
void i2c_intialization(void)
{
	TRISC3=1;
	TRISC4=1;

	SSPSTAT=0X80;
	SSPCON=0X28;
	SSPCON2=0X00;
	SSPADD=(_XTAL_FREQ/I2C_FREQ);
	ACKEN=1;
}
void i2c_start()
{
	SEN=1;
	while(SEN);
}
void i2c_stop()
{
	PEN=1;
	while(PEN);
}
void i2c_restart()
{
	RSEN=1;
	while(SSPIF==0);
	SSPIF=0;
}
void i2c_wait()
{
	while((SSPCON2&0X1F)||(SSPSTAT&0X04));
}
void i2c_send(unsigned char dat)
{
	SSPBUF=dat;
	while(BF==0);
	i2c_wait();
}
unsigned char i2c_read(void)
{
	unsigned char temp;
	RCEN=1;
	while(SSPIF==0);
	SSPIF=0;
	while(!BF);
	temp=SSPBUF;
	(ACKSTAT==1);
	ACKSTAT=1;
	i2c_wait();
	return temp;	
}


voidlcd_time(unsigned char dis_addrs)
{

	sec=read_rtc(0x00);
	min=read_rtc(0x01);
	hur=read_rtc(0x02);
	lcd_cmd(dis_addrs);
	lcd_digit(((hur&0b00110000)>>4)+0X30);	//Seperate 10 Hours
	lcd_digit((hur&0X0F)+0X30);	//Seperate Hours
	lcd_digit(':');
	lcd_cmd(dis_addrs+3);
	lcd_digit(((min&0X70)>>4)+0X30);	//seperate 10 Minutes
	lcd_digit((min&0X0F)+0X30);	//seperate  Minutes
	lcd_digit(':');
	lcd_cmd(dis_addrs+6);
	lcd_digit(((sec&0X70)>>4)+0x30);	//seperate 10 Seconds
	lcd_digit((sec&0X0F)+0X30);
}

voidlcd_date()
{


	days=read_rtc(0x03);
	date=read_rtc(0x04);
	month=read_rtc(0x05);
	year=read_rtc(0x06);

}

voidStartSignal(){
 TRISA1 = 0; //Configure RD0 as output
 RA1 = 0; //RD0 sends 0 to the sensor
 __delay_ms(18);
 RA1 = 1; //RD0 sends 1 to the sensor
 __delay_us(30);
 TRISA1 = 1; //Configure RD0 as input
 }


 //////////////////////////////
charReadData(){
chari, j;
for(j = 0; j < 8; j++){
while(!RA1); //Wait until PORTD.F0 goes HIGH
 __delay_us(30);
if(RA1 == 0)
i&= ~(1<<(7 - j)); //Clear bit (7-b)
else {i|= (1 << (7 - j)); //Set bit (7-b)
while(RA1);} //Wait until PORTD.F0 goes LOW
 }
returni;
 }
 //////////////////////////////
void main() {
	TRISC0=0;
	RC0=0;
	TRISD=0X00;
	TRISE=0X00;
	TRISB=0X10;
	TRISA=0x03;
	PORTA=0x00;
	PORTD=0X0F;
	PORTE=0X00;
	PORTB=0X0F;
	ANSEL=0X00;
	ANSELH=0X00;
	OPTION_REG=0x80;
i2c_intialization();


lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0E);
lcd_cmd(0x80);
lcd_cmd(0x01);

	
while(1){
pre_date=eeprom_read(0);
adc();

CheckResponse();
if(Check == 1){
 RH_byte1 = ReadData();
 RH_byte2 = ReadData();
 T_byte1 = ReadData();
 T_byte2 = ReadData();
 Sum = ReadData();
if(Sum == ((RH_byte1+RH_byte2+T_byte1+T_byte2) & 0XFF)){
 Temp = T_byte1;
 RH = RH_byte1;
lcd_cmd(0xC0);
string("Tem:");
lcd_digit(48 + ((Temp / 10) % 10));
lcd_digit(48 + (Temp % 10));
lcd_digit('C');
lcd_cmd(0xC9);
string("Hum:");
lcd_digit(48 + ((RH / 10) % 10));
lcd_digit (48 + (RH % 10));
lcd_digit ('%');
 }
 }


lcd_time(0X80);
lcd_date();
 //light on 16 hur and off 8 hur
		if(hur==0x8)
		{
			light=0;
		}
		if(hur==0x00  )
			light=1;
//fertilizer one day 1 sec ON

		if(date>pre_date)
		{
			
			if(hur==0x08&&min==0x00&&(sec>=0x00&&sec<=0x03))
			{
				Fertilizer=1;
			}
			else if(hur==0x08&&min==0x00&&(sec>0x03&&sec<=0x06))
			{
				Fertilizer=0;
				eeprom_write(0,date);
			}
			else{Fertilizer=0;}
		}
//recircule for 5 min
		if(rec<hur)
		{
			five_min=1;
		}
		if(five_min==1)
		{
			if(min<0x05)
			{
				Recircle=1;
			}
			else
			{
				Recircle=0;
				five_min=0;
			}
		}
		
		rec=hur;
		
		if(Temp<20)
		{
			heater=0;
		}
		else
		{
			heater=1;
		}
		if(Temp>25)
		{
			cooler=0;
		}
		else
		{
			cooler=1;
		}
		if(RH>65)
		{
			ex=0;
		}
		else
		{
			ex=1;
		}
 } 
