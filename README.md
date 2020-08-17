# keylogger

Primero debemos instalar el gestor de base datos Mysql en Ubuntu, ejecutando en modo administrador los siguiente comandos.

#### sudo apt-get install libmysqlclient-dev

#### mysql_config --cflags -I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -DUNIV_LINUX -DUNIV_LINUX

Una vez instalado el gestor MySql, poner en una carpeta los archivos del repositorio que se encuentra en github,  keylogger.c y keys.h.

El siguiente paso es la compilación, ejecutando este comando en la misma carpeta de los archivos
#### gcc keylogger.c $(mysql_config --libs) -o keylogger $(mysql_config --cflags)


Ejecutar
#### ./keylogger

Aqui ver el video
https://www.youtube.com/watch?v=BhbXhuOdphk 
