#!/bin/bash

#Colors
declare -r greenColour="\e[0;32m\033[1m"
declare -r endColour="\033[0m\e[0m"
declare -r redColour="\e[0;31m\033[1m"
declare -r blueColour="\e[0;34m\033[1m"
declare -r yellowColour="\e[0;33m\033[1m"
declare -r purpleColour="\e[0;35m\033[1m"
declare -r turquoiseColour="\e[0;36m\033[1m"
declare -r grayColour="\e[0;37m\033[1m"

UNO="$(./runclnt1.sh &)"
DOS="$(./runclnt2.sh &)"
wait

echo -e "${greenColour}${UNO}${endColour}\n"
echo -e "${blueColour}${DOS}${endColour}\n"