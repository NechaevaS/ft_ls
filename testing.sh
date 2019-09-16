ls $* > out/orig.out
./ft_ls $* > out/my.out
diff out/orig.out out/my.out > out/diff.out
if (($? == 0)) ; then
    echo "OK"
else
    echo "FAIL"
fi
