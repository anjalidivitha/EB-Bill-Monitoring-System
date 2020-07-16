#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include <unistd.h>
#define CHARGE 8  

int ac_pow=25,pump_pow=20,fan_pow=10,light_pow=5,oven_pow=30,ac_flag=0,pump_flag=0,fan_flag=0,light_flag=0,oven_flag=0;
int ac_count=0,pump_count=0,light_count=0,oven_count=0,fan_count=0;
int time_count_ac=0,time_count_pump=0,time_count_fan=0,time_count_light=0,time_count_oven=0,ac_units,pump_units=0,fan_units=0,light_units=0,oven_units=0;
int ac_amount,pump_amount,fan_amount,light_amount,oven_amount,UNITS,AMOUNT;
char key,ac_status[10],pump_status[10],fan_status[10],light_status[10],oven_status[10];
time_t ac_start=0,ac_end=0,pump_start=0,pump_end=0,light_start=0,light_end=0,fan_start=0,fan_end=0,oven_start=0,oven_end=0;
FILE *fp1, *fp2;

void func_3print()  
{   
    if(key=='E') exit(1);
	fp1=fopen("E:\\HCL\\Assignment10\\record.txt","a");
    if(fp1==NULL){
    	printf("File doesn't exist\n");
    	exit(1);
	}
	if(ac_flag==1) strcpy(ac_status,"ON");
	    else strcpy(ac_status,"OFF");
	    if(pump_flag==1) strcpy(pump_status,"ON");
	    else strcpy(pump_status,"OFF");
	    if(light_flag==1) strcpy(light_status,"ON");
	    else strcpy(light_status,"OFF");
	    if(fan_flag==1) strcpy(fan_status,"ON");
	    else strcpy(fan_status,"OFF");
	    if(oven_flag==1) strcpy(oven_status,"ON");
	    else strcpy(oven_status,"OFF");
		//AC CALCULATIONS
			if(ac_start!=0 && ac_end==0){
				ac_end=clock();
				time_count_ac=(ac_end-(ac_start-3))/CLOCKS_PER_SEC;
				ac_end=0;
			}	
			ac_units=(ac_pow*60*time_count_ac)/1000;
			// PUMP CALCULATIONS
			if(pump_start!=0 && pump_end==0){
				pump_end=clock();
				time_count_pump=(pump_end-(pump_start-3))/CLOCKS_PER_SEC;
				pump_end=0;
			}
			pump_units=(pump_pow*60*time_count_pump)/1000;
			// FAN CALCULATIONS
			if(fan_start!=0 && fan_end==0){
					fan_end=clock();
				time_count_fan=(fan_end-(fan_start-3))/CLOCKS_PER_SEC;
				fan_end=0;
			}
			fan_units=(fan_pow*60*time_count_fan)/1000;
			//LIGHT CALCULATIONS
			if(light_start!=0 && light_end==0){
				light_end=clock();
				time_count_light=(light_end-(light_start-3))/CLOCKS_PER_SEC;
				light_end=0;
			}
			light_units=(light_pow*60*time_count_light)/1000;
			//OVEN CALCULATIONS
			if(oven_start!=0 && oven_end==0){
				oven_end=clock();
				time_count_oven=(oven_end-(oven_start-3))/CLOCKS_PER_SEC;
				oven_end=0;
			}
			oven_units=(oven_pow*60*time_count_oven)/1000;
			UNITS=ac_units+pump_units+fan_units+light_units+oven_units;
	fprintf(fp1,"---------------------------------------------------------------------------\n");
	fprintf(fp1,"|\t\t\t\tRECORD\t\t\t\t          |\n");
	fprintf(fp1,"---------------------------------------------------------------------------\n");
	fprintf(fp1,"|\t\t   Total units consumed: %d Units\t\t\t  |\n",UNITS);
	fprintf(fp1,"---------------------------------------------------------------------------\n");
	fprintf(fp1,"|   \t\tAppliance\t\tstatus\t\t\t\t  |\n");
	fprintf(fp1,"|   \t\t---------\t\t------\t\t\t\t  |\n");
	fprintf(fp1,"|      \t\t   AC\t\t\t %s\t\t\t\t  |\n|      \t\t  PUMP\t\t\t %s\t\t\t\t  |\n|      \t\t  FAN\t\t\t %s\t\t\t\t  |\n|      \t\t  LIGHT\t\t\t %s\t\t\t\t  |\n|      \t\t  OVEN\t\t\t %s\t\t\t\t  |\n",ac_status,pump_status,fan_status,light_status,oven_status);
	fprintf(fp1,"|                                                                         |");
	fprintf(fp1,"\n---------------------------------------------------------------------------\n\n");
	fclose(fp1);
}

void* every_3sec(void * arg){
	          while(1){
		      sleep(3);
		      func_3print();
		        
   }
}

int main(){
	
	
	pthread_t newthread;
	pthread_create(&newthread,NULL, every_3sec,NULL);
	
	while(1){
		scanf("%c",&key);
		switch(key){
			// AC SETTINGS
			case 'A': 
			ac_flag=!ac_flag;
			if(ac_flag==1) {
				strcpy(ac_status,"ON");
				printf("AC Status: %s\n",ac_status);
				ac_start=clock();
			}
			else {
				strcpy(ac_status,"OFF");
				printf("AC Status: %s\n",ac_status);
				ac_end=clock();
				time_count_ac+=(ac_end-ac_start)/CLOCKS_PER_SEC;
			}
			break;
			// PUMP SETTINGS
			case 'P': 
			pump_flag=!pump_flag;
			if(pump_flag==1) {
				strcpy(pump_status,"ON");
				printf("Pump Status: %s\n",pump_status);
				pump_start=clock();
			}
			else {
				strcpy(pump_status,"OFF");
				printf("Pump Status: %s\n",pump_status);
				pump_end=clock();
				time_count_pump+=(pump_end-pump_start)/CLOCKS_PER_SEC;
				pump_end=0; pump_start=0;
			}
			break;
			// FAN SETTINGS
			case 'F': 
			fan_flag=!fan_flag;
			if(fan_flag==1) {
				strcpy(fan_status,"ON");
				printf("Fan Status: %s\n",fan_status);
				fan_start=clock();
			}
			else {
				strcpy(fan_status,"OFF");
				printf("Fan Status: %s\n",fan_status);
				fan_end=clock();
				time_count_fan+=(fan_end-fan_start)/CLOCKS_PER_SEC;
				fan_end=0; fan_start=0;
			}
			break;
			// LIGHT SETTINGS
			case 'L': 
			light_flag=!light_flag;
			if(light_flag==1) {
				strcpy(light_status,"ON");
				printf("Light Status: %s\n",light_status);
				light_start=clock();
			}
			else {
				strcpy(light_status,"OFF");
				printf("Light Status: %s\n",light_status);
				light_end=clock();
				time_count_light+=(light_end-light_start)/CLOCKS_PER_SEC;
				light_end=0; light_start=0;
			
			}
			break;
			// OVEN SETTINGS
			case 'O': 
		    oven_flag=!oven_flag;
			if(oven_flag==1) {
				strcpy(oven_status,"ON");
				printf("Oven Status: %s\n",oven_status);
				oven_start=clock();
			}
			else {
				strcpy(oven_status,"OFF");
				printf("Oven Status: %s\n",oven_status);
				oven_end=clock();
				time_count_oven+=(oven_end-oven_start)/CLOCKS_PER_SEC;
				oven_end=0; oven_start=0;
			}
			break;
			case 'E':
			//AC CALCULATIONS
			if(ac_start!=0 && ac_end==0){
				ac_end=clock();
				time_count_ac=(ac_end-ac_start)/CLOCKS_PER_SEC;
				ac_end=0;
			}	
			ac_units=(ac_pow*60*time_count_ac)/1000;
			ac_amount=ac_units*CHARGE;
			// PUMP CALCULATIONS
			if(pump_start!=0 && pump_end==0){
				pump_end=clock();
				time_count_pump=(pump_end-pump_start)/CLOCKS_PER_SEC;
			}
			pump_units=(pump_pow*60*time_count_pump)/1000;
			pump_amount=pump_units*CHARGE;
			// FAN CALCULATIONS
			if(fan_start!=0 && fan_end==0){
					fan_end=clock();
				time_count_fan=(fan_end-fan_start)/CLOCKS_PER_SEC;
				fan_end=0;
			}
			fan_units=(fan_pow*60*time_count_fan)/1000;
			fan_amount=fan_units*CHARGE;
			//LIGHT CALCULATIONS
			if(light_start!=0 && light_end==0){
				light_end=clock();
				time_count_light=(light_end-light_start)/CLOCKS_PER_SEC;
				light_end=0;
			}
			light_units=(light_pow*60*time_count_light)/1000;
			light_amount=light_units*CHARGE;
			//OVEN CALCULATIONS
			if(oven_start!=0 && oven_end==0){
				oven_end=clock();
				time_count_oven=(oven_end-oven_start)/CLOCKS_PER_SEC;
				oven_end=0;
			}
			oven_units=(oven_pow*60*time_count_oven)/1000;
			oven_amount=oven_units*CHARGE;
			// TOTAL CALCULATION
			UNITS=ac_units+pump_units+fan_units+light_units+oven_units;
			AMOUNT=UNITS*CHARGE;
			fp2=fopen("E:\\HCL\\Assignment10\\EB BILL.txt","a");
			fprintf(fp2,"----------------------------------------------------------------------------------------------------\n");
			fprintf(fp2,"|\t\t\tAC\t\tPUMP\t\tFAN\t\tLIGHT\t\tOVEN\t   |\n");
			fprintf(fp2,"----------------------------------------------------------------------------------------------------\n");
			fprintf(fp2,"|Time Period\t\t%dsec\t\t%dsec\t\t%dsec\t\t%dsec\t\t%dsec\t   |\n",time_count_ac,time_count_pump,time_count_fan,time_count_light,time_count_oven);
			fprintf(fp2,"|Units Consumed\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t   |\n",ac_units,pump_units,fan_units,light_units,oven_units);
			fprintf(fp2,"|Amount Charged\t\tRs.%d\t\tRs.%d\t\tRs.%d\t\tRs.%d\t\tRs.%d\t   |\n",ac_amount,pump_amount,fan_amount,light_amount,oven_amount);
			fprintf(fp2,"----------------------------------------------------------------------------------------------------\n");
			fprintf(fp2,"|                                                                                                  |\n");
			fprintf(fp2,"|Total units consumed: %d units",UNITS);
			fprintf(fp2,"                                                                    |\n");
			fprintf(fp2,"|                                                                                                  |\n");
			fprintf(fp2,"|Total Amount Charged: Rs.%d\\-",AMOUNT);
			fprintf(fp2,"                                                                    |\n");           
			fprintf(fp2,"|                                                                                                  |\n");
			fprintf(fp2,"----------------------------------------------------------------------------------------------------\n\n");
			fclose(fp2);
			exit(1);
			break;
	    }   
	    
	    
	}

	}	
