### call me from /etc/rc.local
### sudo bash /home/pi/startup.sh &

export STEWIE_PATH=/home/pi/git/stewie-pinball
$STEWIE_PATH/display-server.py &
sleep 1 && $STEWIE_PATH/stewie &
exit 0

