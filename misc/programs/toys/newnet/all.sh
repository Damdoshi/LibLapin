#!/bin/sh

VALGRIND=1
bash test_net.sh
bash test_udp_phase1.sh
bash test_udp_phase2.sh
bash test_udp_phase3.sh
bash test_rudp_phase4.sh
bash test_rudp_phase5.sh
bash test_rudp_phase6.sh
bash test_rudp_phase7.sh
bash stress_net.sh

