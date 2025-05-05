#!/bin/bash
(crontab -l 2>/dev/null; echo "@reboot /path/to/your_program") | crontab -

