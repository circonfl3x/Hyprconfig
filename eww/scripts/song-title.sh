title=`playerctl metadata --format '{{title}}'`
length=${#title}
if [[ "${title:0:35}" == "No player could handle this command" ]]; then
  echo "Nothing is playing..."
else
  if [ $length -ge 20 ]; then
    echo "${title:0:17}..."
  else
    echo $title
  fi
  
fi
