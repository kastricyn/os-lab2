MODULE_NAME=maks
sudo rmmod $MODULE_NAME
make clean
make
sudo insmod $MODULE_NAME.ko
