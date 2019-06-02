
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#include<unistd.h>
#include<string.h>

#include<stdint.h>

#define HYGRO_PATH	"/dev/hygro_dev"

#define MSG_MAX		17
#define TEMP_MAX	10	


int data[4] = {-1, -1, -1, -1};

void get_temperature(char temperature_msg[]){
	char temp[TEMP_MAX];
	
	strcpy(temperature_msg,"tempr : ");
	sprintf(temp, "%d", data[2]);
	strcat(temperature_msg, temp);
	strcat(temperature_msg, ".");
	sprintf(temp, "%d", data[3]);
	strcat(temperature_msg, temp);
	strcat(temperature_msg, " C");
}
	
void get_humidity(char humidity_msg[]){
	char temp[TEMP_MAX];
	
	strcpy(humidity_msg, "humid : ");
	sprintf(temp, "%d", data[0]);
	strcat(humidity_msg, temp);
	strcat(humidity_msg, ".");
	sprintf(temp, "%d", data[1]);
	strcat(humidity_msg, temp);
	strcat(humidity_msg, " %");
	}

int main(void)
{
	char temperature_msg[MSG_MAX];
	char humidity_msg[MSG_MAX];
	
	printf("start\n");
	
	i2c_start(); 
   
	lcd_display_init();	
	
	int fd= open(HYGRO_PATH,O_RDWR);
	
	if(fd <0)
	{
		printf("%d \n", fd);
	}
	while(1)
	{		
		read(fd, data,sizeof(int)*4);
		if(data[0]==-1)
		continue;
		
		get_temperature(temperature_msg);
		get_humidity(humidity_msg);
		
		printf("humidity = %d.%d %% tmperature = %d.%d C\n", data[0], data[1], data[2],data[3]);
		lcd_print(temperature_msg, 0, 0);
		lcd_print(humidity_msg, 1, 0);
		
		sleep(1);
	}
	
	
	sleep(1);

    i2c_stop(); 
	
	return 0;
}
