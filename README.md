# bendian
generalized little-endian to big-endian conversion function

can also be used to convert from big-endian to little-endian as the process is the same

## to test on unix
    cc -o bendian_test bendian.c bendian_test.c
    ./bendian_test
    if test $? -eq 0
    then
        echo Success!
    else
        echo Failure...
    fi
