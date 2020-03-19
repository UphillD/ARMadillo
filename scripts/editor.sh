#!/bin/bash

# Helper script to open the entire project in the preferred editor.

EDITOR=geany

$EDITOR ./*.sh &
$EDITOR ../build/* &
$EDITOR ../include/*.h &
$EDITOR ../include/common/*.h &
$EDITOR ../include/drivers/*.h &
$EDITOR ../common/* &
$EDITOR ../drivers/* &
$EDITOR ../kernel/* &
