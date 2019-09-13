ls $* > orig.out
./ft_ls $* > my.out
diff orig.out my.out > diff.out
if (($? == 0)) ; then
    echo "OK"
else
    echo "FAIL"
fi