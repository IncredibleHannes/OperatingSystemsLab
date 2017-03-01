#/bin/bash!
make
printf "sequential\n"
time ./calc_pi_sequential 150000000
printf "critical\n"
time ./calc_pi_critical 150000000
printf "atomic\n"
time ./calc_pi_atomic 150000000
printf "reduction\n"
time ./calc_pi_reduction 150000000
