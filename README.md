# bendian
generalized little-endian to big-endian and vice-versa conversion function

## to test on unix
    cc -o bendian_test bendian.c bendian_test.c
    ./bendian_test
    if test $? -eq 0
    then
        echo Success!
    else
        echo Failure...
    fi
