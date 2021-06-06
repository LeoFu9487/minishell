make


for((i=0;;i++))
do
if [[ -f test_case/$i ]]
then
	bash test_case/$i > trace/ans_$i.txt
	cat test_case/$i | xargs ./test > trace/$i.txt
	diff trace/$i.txt trace/ans_$i.txt > trace/diff_$i.txt
	if [[ -s trace/diff_$i.txt ]]
	then
		echo "KO_$i"
	else
		rm trace/diff_$i.txt
		rm -rf $i trace/ans_$i #ok to remove
		echo "OK_$i"
	fi
else
	rm test #ok to remove
	exit 0
fi
done
