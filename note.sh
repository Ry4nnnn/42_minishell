# Builtins
cd
env
pwd
export
unset
exit
echo

# env tests
env

# echo tests
export A=z
echo $A
echo "$A"
echo '$A'
echo "$A$A"
echo "$DNE$A"
echo -n hello


export Z="ho hi"
ec$Z

echo "$A'$A'"
echo "$A_$A"
echo "$A1$A"
echo $?


# cd test
cd
cd ~
cd ..
cd -
cd abc
cd cd
echo hi | cd      # cd in pipes

# env test
env

# pwd test
pwd
pwd abc

# unset test
unset
unset A
echo hi | unset USER    # unset in pipes

# export test
export
export Z
export Z=
export Z=abc
export Z=$A
export Z="$A"
export Z='$A'
echo hi | export A=abc    # export in pipes

# exit test
exit
exit 1
exit | echo hi        # exit in pipes


