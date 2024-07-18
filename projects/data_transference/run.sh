echo "trying to run the virtual ttys"

socat -d -d pty,raw,echo=0 pty,raw,echo=0

