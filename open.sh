#!/bin/bash
g++ shell.cpp -o shell -lreadline
gnome-terminal -x bash -c "./shell; exec bash";

