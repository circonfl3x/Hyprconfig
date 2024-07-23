volume=$(wpctl get-volume @DEFAULT_SINK@ | awk -F ': ' '{print $2}')

if [ "${volume:5}" = "[MUTED]" ]; then
  echo 0
else 
  echo $volume
fi
