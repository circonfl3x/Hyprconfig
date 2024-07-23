album=`playerctl metadata --format '{{album}}'`
len=${#album}
if [[ "$album" = "No player could handle this command\n" ]]; then
  echo "No playing"
else
  if [ $len -ge 15 ]; then
    echo "${album:0:15}..."
  else
    echo $album
  fi
fi
