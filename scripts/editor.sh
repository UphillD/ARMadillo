#!/bin/bash

# Helper script to open the entire project in the preferred editor.

EDITOR=geany

$EDITOR ./* &
$EDITOR ../build/* &
$EDITOR ../include/* &
$EDITOR ../include/common/* &
$EDITOR ../include/drivers/* &
$EDITOR ../common/* &
$EDITOR ../drivers/* &
$EDITOR ../kernel/* &
