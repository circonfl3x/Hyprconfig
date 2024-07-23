
cc=$(eww active-windows | grep control_center)

if [[ $cc = "control_center: control_center" ]] ;then
  echo 1
else
  echo 0
fi
