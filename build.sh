make
sh-elf-objcopy -R .stack -O binary buildfiles/HappyNewYearNewDecade2020.elf buildfiles/output.bin
../../utils/scramble/scramble buildfiles/output.bin built/1st_read.bin