#!/bin/bash

sudo cp tcpserver /etc/init.d/
sudo chmod a+x /etc/init.d/tcpserver

update-rc.d tcpserver defaults
