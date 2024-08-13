wifi=$(iwgetid -r)

if [[ wifi = "" ]]; then
    echo "Not connected"
else
    echo "${wifi:0:10}..."
fi
