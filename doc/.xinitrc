#!/bin/sh
# xcompmgr &
# feh --bg-scale  /usr/tmp/bg_figs/tank.png &
#display -window root repo/dwm/dwm.png 
#xsetroot -solid black
flag_box=0

wifi() {
      STATUS="X`/sbin/iwgetid`"
      if test "$STATUS" != "X" ; then
        ESSID="`/sbin/iwgetid |awk -F ":" '{print $2}'|sed -e 's/"//g'`"
        LINK="`awk '/wlan0:/ {print $3}' /proc/net/wireless |sed -e 's/\.//g'`"
		echo " $ESSID:$LINK"
      fi
} 

box_alert() {
    xdpyinfo > /dev/null
    if test "$?" == "0"; then 
        xterm -e dialog --msgbox 'Bateria Fraca' 5 40
    else
        dialog --msgbox 'Bateria Fraca' 5 40
    fi
}

batt() {
    FULL=`cat /sys/class/power_supply/BAT1/charge_full`
    PRESENT=`cat /sys/class/power_supply/BAT1/present`
    CHARGE=`cat /sys/class/power_supply/BAT1/charge_now`
    STATUS=`cat /sys/class/power_supply/BAT1/status`
    if test "$PRESENT" != "0" ; then
      # CHARGE=$((${CHARGE} * 100 / ${FULL}))
      CHARGE=100
      case $STATUS in
        Full)
          SIGN="=";;
        Charging)
          SIGN="+";;
        Discharging)
          SIGN="-";;
      esac
      echo " ${CHARGE}%${SIGN}"
      if [[ "$flag_box" -eq "0" && "$CHARGE" -lt "6" && "$SIGN" == "-" ]]; then
          flag_box = 1
          # ./box &
          box_alert &
          /usr/bin/xmp test_novo.xm &
      fi
      if (( $CHARGE == 0 )); then
          if test $SIGN == "+"; then
             sudo /sbin/shutdown -h now &
          fi
      fi
    else
      echo " AC"
    fi
}

volume() {
      STATUS="`amixer get Headphone |awk '/Front\ Left:/ {print $4}'`"
      if test "$STATUS" != "[on]" ; then 
        echo " Mute"
      else
        echo " `/usr/bin/amixer get PCM |awk '/Front\ Left:/ {print $5}' | sed -e 's/\[//g'|sed -e 's/%\]//g'`v"
      fi
}

cmusstats() {
      if test "X`pgrep cmus`" != "X" ; then 
        TIME="`cmus-remote -Q |awk '/duration/ {print $2}'`"
        CURR="`cmus-remote -Q |awk '/position/ {print $2}'`"
        ARTIST="`cmus-remote -Q |sed -ne '/artist/s/tag artist //pg'`"
        TITLE="`cmus-remote -Q |sed -ne '/title/s/tag title //pg'`"
        echo "$TITLE ($ARTIST) $CURR/$TIME"
      fi
}

if [ -x "$(which gpg-agent)" ]; then
  if test -f $HOME/.gpg-agent-info &&    kill -0 $(cut -d: -f 2 $HOME/.gpg-agent-info) 2>/dev/null; then
    GPG_AGENT_INFO=$(cat $HOME/.gpg-agent-info)
    export GPG_AGENT_INFO
  else
    eval $(gpg-agent --daemon)
    echo $GPG_AGENT_INFO >$HOME/.gpg-agent-info
  fi
fi

# Note that the new option --write-env-file may be used instead.

# You should always add the following lines to your .bashrc or whatever
# initialization file is used for all shell invocations:
 
GPG_TTY=$(tty)
export GPG_TTY

alias xterm="xterm -en UTF-8"

while true; do
#   xsetroot -name "`wifi``volume``batt` `date '+%a %d-%m-%Y %H:%M'`"
#   dwmbar
   sleep 1
done &
# feh --bg-fill --randomize  background_images/*
# conky 
# xrdb -merge ~/.Xresources &
xrdb -merge ~/.Xresources_2 &
export _JAVA_AWT_WM_NONREPARENTING=1
slstatus &
exec dwm
while true
exec xcompmgr -c 
# wmname LG3D
# exec bspwm


