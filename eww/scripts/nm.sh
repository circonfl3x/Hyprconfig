#!/bin/bash

wget -q --spider http://google.com

if [ $? -eq 0 ]; then
    echo 0
else
    echo 1
fi
