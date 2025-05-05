#!/bin/bash
(crontab -l 2>/dev/null; echo "@reboot /home/fvieira/famine/Famine") | crontab -
