#! /bin/bash

playerctl metadata --format \
    '{"t":"{{title}}","s":"{{artist}}","a":"{{album}}","u":"{{mpris:artUrl}}"}'
