./ft_nm "$1" > myoutput
nm "$1" > nmoutput
diff nmoutput myoutput