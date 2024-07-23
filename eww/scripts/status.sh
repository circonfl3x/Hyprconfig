status=`playerctl status`

if [ "$status" = "Stopped" ]; then
  echo "s"
else
  echo "p"
fi
