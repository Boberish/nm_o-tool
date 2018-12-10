./ft_nm lem-in > myoutputlemin
nm lem-in > realnmlemin
diff realnmlemin myoutputlemin > prob
DIFF=$(diff realnmlemin myoutputlemin) 
if [ "$DIFF" != "" ] 
then
    cat prob
fi