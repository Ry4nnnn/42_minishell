# Builtin tests
cd
env
pwd
export
unset
exit
echo

# Basic tests
echo "hi"
echo hi

export A=z
echo $A
echo "$A"
echo '$A'
echo "$A$A"
echo "$DNE$A"

export Z="ho hi"
ec$Z

echo "$A'$A'"

