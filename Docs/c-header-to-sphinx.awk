#!/usr/bin/awk -f

FNR == 1 {
	name = FILENAME
	sub("^[^/]*/", "", name)
	ruler = name
	gsub(/./, "-", ruler)
	print ""
	print ruler
	print name
	print ruler

	INTRO = 1
}

{
	sub(/ *$/, "")
}

/^[a-z].*(.*);$/ {
	print ""
	print ".. c:function::", $0
	next
}

/^[a-z].*;$/ {
	print ""
	print ".. c:var::", $0
	next
}

/^#define/ {
	print ""
	print ".. c:macro::", $2
	next
}

/^\/\*$/ {
	print ""
	next
}

/^ \* / || /^ \*$/ {
	if (INTRO) {
		sub(/^ \* ?/, "")
	} else {
		sub(/^ \* ?/, "   ")
	}
	print
	next
}

/^ \*\/$/ {
	INTRO = 0
	next
}
