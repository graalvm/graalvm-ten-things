large.txt: lorem.txt
	for i in {0..2500}; do cat $< >> $@; done

small.txt: lorem.txt
	head -c 1024 $< > $@

clean:
	rm -f large.txt small.txt *.h *.class *.bc *.json unicalc topten
