make
./test
for((i=0;;i++))
do
if [[ -f $i ]]
then
	diff $i ans_$i > diff_$i.txt
	if [[ -s diff_$i.txt ]]
	then
		echo "KO_$i"
	else
		rm diff_$i.txt
		echo "OK_$i"
	fi
	rm -rf $i ans_$i #ok to remove
else
	rm test #ok to remove
	exit 0
fi
done