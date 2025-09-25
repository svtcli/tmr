#!/bin/bash

# Pick one variable; sets pthread if needed
VAR=TIME  ;  PT=""
VAR=ENERGY;  PT=-pthread
VAR=ACTION;  PT=-pthread # Higly experimental & controversial

# define compiler
MYCXX=icpx

$MYCXX -DTMR_VAR=TMR_$VAR -o test test.cpp $PT
