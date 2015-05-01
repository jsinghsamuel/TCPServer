# TCPServer
Linux daemon Program (c,c++) that listens on TCP/IP.

TCP Server:

The TCP Server Application is build on Eclipse IDE, Ubuntu 14.04 LTS. 

1) TCP Server : Build using Poco libraries.

Library Dependenacy : 

ldd TCPSmartServer

     linux-vdso.so.1 =>  (0x00007ffd509de000)
     libPocoUtil.so.30 => /usr/local/lib/libPocoUtil.so.30 (0x00007fc895afa000)
     libPocoFoundation.so.30 => /usr/local/lib/libPocoFoundation.so.30 (0x00007fc895716000)
     libPocoNet.so.30 => /usr/local/lib/libPocoNet.so.30 (0x00007fc8953f1000)
     libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fc8950ed000)
     libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fc894ed7000)
     libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc894b11000)
     libPocoXML.so.30 => /usr/local/lib/libPocoXML.so.30 (0x00007fc894880000)
     libPocoJSON.so.30 => /usr/local/lib/libPocoJSON.so.30 (0x00007fc894633000)
     libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fc894414000)
     libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fc894210000)
     librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007fc894008000)
     libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fc893d01000)
     /lib64/ld-linux-x86-64.so.2 (0x00007fc895d93000)
	
Server Main Path:
   /var/opt/TCPSmartServer/

Logs : Server Logs are generated here. 
   /var/opt/TCPSmartServer/logs

scripts : Scripts for Auto Restart of Server on Run-Level. 
   /var/opt/TCPSmartServer/scripts

bin : Server Application Binary.
   /var/opt/TCPSmartServer/bin
   
2) Auto Start Script
  
  Pwd: /var/opt/TCPSmartServer/scripts
  tcpserver : Supporting script for starting/stoping Server. 
  startupscript.sh : Script to auto start server on Machine Startup.
  
  Run startupscript.sh to create a service enabled server.
  
  Usage: 
    
     service tcpserver start
     service tcpserver stop
     service tcpserver restart
  
  3) Client Tool for testing server. 
     Script for simulating the server functionality. 
     
     Usage: 
     --> ./tcpClient.pl -h
     ./tcpClient.pl -h [Help] -s [Server Ip Address] -p [Port Number] -n [Number of Request]
     ./tcpClient.pl will run with providing -s, -p and -n options.
     
     Edit the $message variable to pass different commands. 
     Example:
     $message = "GETMESSAGE\n";
     #$message = "BYE\n";
     #$message = "ahcekllkjer\n";
