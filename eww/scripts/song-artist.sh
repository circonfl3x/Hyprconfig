artist=`playerctl metadata --format '{{artist}}'`
length=${#artist}
if [[ "$artist" = "No player could handle this command\n" ]]; then
  echo ""
else
  if [ $length -ge 20 ]; then
    echo "${artist:0:20}..."
  else
    echo $artist
  fi
fi
