#!/usr/bin/bash

if [ "$#" -lt "1" ]; then
    exit 0
fi

NAME=`basename $1`
UNAME=`echo -n $NAME | tr "[a-z]" "[A-Z]"`
TARGET=$1

test -d $TARGET
if [ "$?" -eq "0" ]; then
    echo "$TARGET already exists."
    exit 1
fi

mkdir $TARGET
mkdir res/$TARGET
for FILEPATH in `ls .context/*.c`; do
    FILENAME=`basename $FILEPATH`
    cat HEADER $FILEPATH | sed "s/CONTEXT/$NAME/g" > $TARGET/$FILENAME
done

cat HEADER INCLUDE | sed "s/CONTEXT/$NAME/g" | sed "s/_$NAME_/_$UNAME_/g" > include/$TARGET.h
echo -e "#include\t\t\t\"$NAME.h\"" >> context_headers.template
echo -e "bunny_declare_context($NAME);" >> context_declaration.template
echo -e "    $UNAME," | tr "[a-z]" "[A-Z]" >> context_enumeration.template
echo -e "  t_$NAME\t\t\t$NAME;"  >> context_attribute.template
echo -e "  program.$NAME.program = &program;" >> context_pointers.template

./$0 ${@:2}

