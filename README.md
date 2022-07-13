# bendian
generalized little-endian to big-endian and vice versa conversion function

## to test on Windows (instructions vary by compiler; the example here uses PellesC's "cc" driver)
    # PellesC, a freeware C compiler for Windows, can be downloaded from <http://www.smorgasbordet.com/pellesc/>
    cc /obendian_test.exe bendian.c bendian_test.c
    bendian_test
    if ERRORLEVEL 0 (
        echo Success!
    ) else (
        echo Failure...
    )


## to test on unix
    cc -o bendian_test bendian.c bendian_test.c
    ./bendian_test
    if test $? -eq 0
    then
        echo Success!
    else
        echo Failure...
    fi
