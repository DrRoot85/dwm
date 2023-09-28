#!/bin/sh

function run {
  if ! pgrep $1 ;
  then
    $@&
  fi
}

#killall volumeicon &
#mixer vol 80:80 &
#mixer mic 0:0 &

#Find out your monitor name with xrandr or arandr (save and you get this line)
#xrandr --output VGA-1 --primary --mode 1360x768 --pos 0x0 --rotate normal
#xrandr --output DP2 --primary --mode 1920x1080 --rate 60.00 --output LVDS1 --off &
#xrandr --output LVDS1 --mode 1366x768 --output DP3 --mode 1920x1080 --right-of LVDS1
#xrandr --output HDMI2 --mode 1920x1080 --pos 1920x0 --rotate normal --output HDMI1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output VIRTUAL1 --off
#autorandr horizontal

# keybLayout=$(setxkbmap -v | awk -F "+" '/symbols/ {print $2}')

# if [ $keybLayout = "be" ]; then
#   run sxhkd -c ~/.config/qtil/sxhkd/sxhkdrc-azerty &
# else
# run sxhkd -c ~/.config/qtile/sxhkd/sxhkdrc &
# fi

#Some ways to set your wallpaper besides variety or nitrogen
run feh --bg-tile "$(< "${HOME}/.cache/wal/wal")"  
#wallpaper for other Arch based systems
#feh --randomize --bg-fill ~/Dropbox/Apps/Desktoppr/*

#xsetroot -cursor_name left_ptr &

#run variety &
#run nm-applet &
#run pamac-tray &
#run xfce4-power-manager &
run numlockx on &
run "dunst"
#wal -R &
#blueberry-tray &
picom -b --config $HOME/.config/picom/picom.conf &
#/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
#/usr/lib/xfce4/notifyd/xfce4-notifyd &
run "volumeicon"
#trayer &
run slstatus &
#nitrogen --restore &
#run caffeine &
clipmenud &
#run vivaldi-stable &
#run firefox &
#run thunar &
#run dropbox &
#run insync start &
#run discord &
#run spotify &
