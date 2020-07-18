ANDROID_SDK=/home/chris/projects/android/adt-bundle-linux-x86_64-20130911/sdk
SDK_ROOT=$ANDROID_SDK

rm apps -rf
"${SDK_ROOT}"/platform-tools/adb backup -f mybackup.ab com.iforce2d.nrf24rangetest
dd if=mybackup.ab  bs=1 skip=24|openssl zlib -d > mybackup.tar
tar xf mybackup.tar
rm mybackup.tar
rm mybackup.ab

