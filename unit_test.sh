for file in custom_tests/dylib/* custom_tests/64/* custom_tests/32/*
do
./ft_nm $file > myoutput
nm $file > nmoutput
# echo $file
# echo "$(basename "$file")"
DIFF=$(diff myoutput nmoutput) 
if [ "$DIFF" != "" ] 
then
    echo "problem with $file";
    cat myoutput nmoutput > problemwith
    # echo "REAL NM\n"
    # cat nmoutput
fi
done









# ./ft_nm lem-in > myoutputlemin
# nm lem-in > realnmlemin
# diff realnmlemin myoutputlemin > prob
# DIFF=$(diff realnmlemin myoutputlemin) 
# if [ "$DIFF" != "" ] 
# then
#     cat prob
# fi